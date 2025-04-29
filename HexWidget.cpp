#include "HexWidget.h"

void HexWidget::paintEvent(QPaintEvent*)
{
    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.translate(OffsetX, OffsetY);
    Painter.scale(Scale, Scale);

    for(int q = 0; q < Map.Width; q++)
    {
        for(int r = 0; r < Map.Height; r++)
        {
            Hex& Hex_ = Map.GetLocation(q, r);
            auto Corners = Hex_.GetCorners();

            QPolygonF Polygon;
            for(const auto& c : Corners)
                Polygon << c;

            if(QPoint(q,r) == SelectedHex)
                Painter.setBrush(Qt::yellow);
            else
                Painter.setBrush(Qt::white);

            Painter.setPen(QPen(Qt::black,1));
            Painter.drawPolygon(Polygon);
        }
    }
}

void HexWidget::wheelEvent(QWheelEvent* event)
{
    float Factor = 1.1;
    float Zoom = (event->angleDelta().y() > 0) ? Factor : 1.0 / Factor;

    QPointF CursorPos = event->position();
    QPointF BeforeScale = (CursorPos - QPointF(OffsetX, OffsetY)) / Scale;

    Scale *= Zoom;

    QPointF AfterScale = (CursorPos - QPointF(OffsetX, OffsetY)) / Scale;

    QPointF OffsetDiff = (AfterScale - BeforeScale) * Scale;
    OffsetX += OffsetDiff.x();
    OffsetY += OffsetDiff.y();

    update();
}

void HexWidget::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
    {
        IsDragging = true;
        LastMousePos = event->pos();
    }
    else if(event->button() == Qt::LeftButton)
    {
        QPointF Pos = event->pos();

        QPointF Cord = (Pos - QPointF(OffsetX, OffsetY)) / Scale;
        QPoint HexCord = PixelToHex(Cord);

        if(HexCord.x() >= 0 && HexCord.x() < Map.Width &&
            HexCord.y() >= 0 && HexCord.y() < Map.Height)
        {
            SelectedHex = HexCord;
            update();
        }
    }
}

void HexWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(IsDragging)
    {
        QPointF Delta = event->pos() - LastMousePos;
        OffsetX += Delta.x();
        OffsetY += Delta.y();
        LastMousePos = event->pos();
        update();
    }
}

void HexWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
        IsDragging = false;
}

QPoint HexWidget::PixelToHex(QPointF p)
{
    float q = (2.0 / 3.0 * p.x()) / HexSize;
    float r = (-1.0 / 3.0 * p.x() + std::sqrt(3.0) / 3.0 * p.y()) / HexSize;
    return CubeToAxial(q,r);
}

QPoint HexWidget::CubeToAxial(float qc, float rc)
{
    float xc = qc;
    float zc = rc;
    float yc = -xc - zc;

    int xa = std::round(xc);
    int ya = std::round(yc);
    int za = std::round(zc);

    float dx = std::abs(xc - xa);
    float dy = std::abs(yc - ya);
    float dz = std::abs(zc - za);

    if(dx > dy && dx > dz)
        xa = -ya - za;
    else if(dy > dz)
        ya = -xa - za;
    else
        za = -xa - ya;

    return QPoint(xa,za);
}
