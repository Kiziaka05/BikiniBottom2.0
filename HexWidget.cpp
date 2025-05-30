#include "HexWidget.h"
#include <QPainterPath>

HexWidget::HexWidget(QWidget* parent) :
    QWidget(parent), Map(15), Hero(QPoint(0,0))
{
    setMinimumSize(800,600);
    setMouseTracking(true);
    InitializeTextures();
}

void HexWidget::InitializeTextures()
{
    QPixmap HeroOriginalPixmap("hero1.jpg");
    if(!HeroOriginalPixmap.isNull())
    {
        this->HeroPixmap = HeroOriginalPixmap.scaled(
            QSizeF(2 * Hex::HexSize, 2 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Faild to load texture");
    }

    QPixmap FogOriginalPixmap("hero1.jpg");
    if(!FogOriginalPixmap.isNull())
    {
        this->FogTexture = FogOriginalPixmap.scaled(
            QSizeF(2 * Hex::HexSize, 2 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Faild to load texture");
    }
}

void HexWidget::paintEvent(QPaintEvent*)
{
    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.translate(OffsetX, OffsetY);
    Painter.scale(Scale, Scale);

    const auto& Grid = Map.GetMap();
    for(const auto& Col : Grid)
    {
        for(const auto& Hex_ : Col)
        {
            auto Corners = Hex_.GetCorners();

            QPolygonF Polygon;
            for(const auto& c : Corners)
                Polygon << c;


            QBrush Brush;
            std::pair<int, int> CurrCoords = Hex_.GetQR();

            if (QPoint(CurrCoords.first, CurrCoords.second) == Hero.GetPosition())
            {
                if(!HeroPixmap.isNull())
                {
                    QPointF center = Hex_.GetCenter();
                    QPointF topLeft = center - QPointF(HeroPixmap.width() / 2.0, HeroPixmap.height() / 2.0);

                    QPolygonF hexPolygon;
                    for(const auto& pt : Corners)
                    {
                        hexPolygon << pt;
                    }

                    QPainterPath hexPath;
                    hexPath.addPolygon(hexPolygon);

                    Painter.save();
                    Painter.setClipPath(hexPath);
                    Painter.drawPixmap(topLeft, HeroPixmap);
                    Painter.restore();
                }
            }
            else if(Hex_.VisibilityState())
                Brush = Qt::white;
            else if(Hex_.ExplorationState())
                Brush = Qt::darkGray;
            else{
                if(!FogTexture.isNull())
                {
                    QPointF center = Hex_.GetCenter();
                    QPointF topLeft = center - QPointF(FogTexture.width() / 2.0, FogTexture.height() / 2.0);

                    QPolygonF hexPolygon;
                    for(const auto& pt : Corners)
                    {
                        hexPolygon << pt;
                    }

                    QPainterPath hexPath;
                    hexPath.addPolygon(hexPolygon);

                    Painter.save();
                    Painter.setClipPath(hexPath);
                    Painter.drawPixmap(topLeft, FogTexture);
                    Painter.restore();
                }
            }
            Painter.setBrush(Brush);
            Painter.setPen(QPen(Qt::black, 1));
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
            QPoint HeroCurrPos = Hero.GetPosition();
            const Hex& CurrHex = Map.GetQPointLoc(HeroCurrPos);
            const Hex& TargetHex = Map.GetQPointLoc(HexCord);

            if(CurrHex.IsNeighbor(TargetHex))
            {
                Hero.MoveTo(HexCord);
                Map.UpdateVisibility(Hero.GetPosition());
                update();
            }
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

        if(Map.ContainsHex(HexCord.x(),HexCord.y()))
        {
            if(HexCord != HoveredHex)
            {
                HoveredHex = HexCord;
                update();
            }
        }
        else if(HoveredHex != QPoint(INT_MAX,INT_MAX))
        {
            HoveredHex = QPoint(INT_MAX,INT_MAX);
            update();
        }
    }
}

void HexWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
        IsDragging = false;
}

void HexWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    if(!Initialized)
    {
        QRectF MapRect = GetMapBoundingRect();
        if(!MapRect.isNull() && MapRect.isValid())
        {
            QPointF MapCenter = MapRect.center();
            QPointF WidgetCenter = QPointF(width(), height()) / 2.0;

            OffsetX = WidgetCenter.x() - MapCenter.x() * Scale;
            OffsetY = WidgetCenter.y() - MapCenter.y() * Scale;

            Initialized = true;
            update();
        }
    }
}

void HexWidget::leaveEvent(QEvent*)
{
    if(HoveredHex != QPoint(INT_MAX,INT_MAX))
    {
        HoveredHex = QPoint(INT_MAX,INT_MAX);
        update();
    }
}

QPoint HexWidget::PixelToHex(QPointF p) const
{
    float q = (2.0 / 3.0 * p.x()) / Hex::HexSize;
    float r = (-1.0 / 3.0 * p.x() + std::sqrt(3.0) / 3.0 * p.y()) / Hex::HexSize;
    return CubeToAxial(q,r);
}

QPoint HexWidget::CubeToAxial(float qc, float rc) const
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

QRectF HexWidget::GetMapBoundingRect() const
{
    const auto& Grid = Map.GetMap();
    if(Grid.empty()) return QRectF();

    qreal MinX = std::numeric_limits<float>::max();
    qreal MaxX = std::numeric_limits<float>::lowest();
    qreal MinY = std::numeric_limits<float>::max();
    qreal MaxY = std::numeric_limits<float>::lowest();

    for(const auto& Col : Grid)
    {
        for(const auto& Hex_ : Col)
        {
            QPointF Center = Hex_.GetCenter();
            MinX = std::min(MinX, Center.x());
            MaxX = std::max(MaxX, Center.x());
            MinY = std::min(MinY, Center.y());
            MaxY = std::max(MaxY, Center.y());
        }
    }

    return QRectF(MinX - Hex::HexSize,
                  MinY - Hex::HexSize,
                  (MaxX - MinX) + 2 * Hex::HexSize,
                  (MaxY - MinY) + 2 * Hex::HexSize);
}

void HexWidget::SaveMapToFile(const QString& filePath)
{
    Map.SaveToFile(filePath, Hero.GetPosition());
}

void HexWidget::LoadMapFromFile(const QString& filePath)
{
    QPoint heroPos;
    Map.LoadFromFile(filePath, heroPos);
    Hero.MoveTo(heroPos);
}
