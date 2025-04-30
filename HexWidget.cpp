#include "HexWidget.h"

void HexWidget::paintEvent(QPaintEvent*)
{
    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.translate(OffsetX, OffsetY);
    Painter.scale(Scale, Scale);

    auto& Grid = Map.GetMap();
    for(auto& Col : Grid)
    {
        for(auto& Hex_ : Col)
        {
            auto Corners = Hex_.GetCorners();

            QPolygonF Polygon;
            for(const auto& c : Corners)
                Polygon << c;

            if(QPoint(Hex_.q,Hex_.r) == SelectedHex)
                Painter.setBrush(Qt::yellow);
            else if(QPoint(Hex_.q,Hex_.r) == CenterHex)
                Painter.setBrush(Qt::red);
            else if(QPoint(Hex_.q,Hex_.r) == HoveredHex)
                Painter.setBrush(QColor(200,200,200));
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

        if(Map.ContainsHex(HexCord.x(), HexCord.y()))
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
    else
    {
        QPointF Pos = event->pos();
        QPointF Cord = (Pos - QPointF(OffsetX, OffsetY)) / Scale;
        QPoint HexCord = PixelToHex(Cord);

        if(HexCord != HoveredHex)
        {
            HoveredHex = HexCord;
            update();
        }
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

QRectF HexWidget::GetMapBoundingRect()
{
    auto& Grid = Map.GetMap();
    if(Grid.empty()) return QRectF();

    qreal MinX = std::numeric_limits<float>::max();
    qreal MaxX = std::numeric_limits<float>::lowest();
    qreal MinY = std::numeric_limits<float>::max();
    qreal MaxY = std::numeric_limits<float>::lowest();

    for(auto& Col : Grid)
    {
        for(auto& Hex_ : Col)
        {
            QPointF Center = Hex_.GetCenter();
            MinX = std::min(MinX, Center.x());
            MaxX = std::max(MaxX, Center.x());
            MinY = std::min(MinY, Center.y());
            MaxY = std::max(MaxY, Center.y());
        }
    }

    return QRectF(MinX - HexSize, MinY - HexSize, (MaxX - MinX) + 2 * HexSize, (MaxY - MinY) + 2 * HexSize);
}

void HexWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    if(!Initialized)
    {
        QRectF MapRect = GetMapBoundingRect();
        QPointF MapCenter = MapRect.center();
        QPointF WidgetCenter = QPointF(width(), height()) / 2.0;

        OffsetX = WidgetCenter.x() - MapCenter.x() * Scale;
        OffsetY = WidgetCenter.y() - MapCenter.y() * Scale;

        Initialized = true;
        update();
    }
}

void HexWidget::leaveEvent(QEvent*)
{
    HoveredHex = QPoint(-999,-999);
    update();
}
