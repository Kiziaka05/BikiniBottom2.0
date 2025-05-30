#include "HexWidget.h"
#include "Fight.h"
#include <QPainterPath>

HexWidget::HexWidget(int NRadius, QWidget* parent) :
    QWidget(parent), Map(NRadius > 0 ? NRadius : 10), Hero(QPoint(0,0))
{
    setMinimumSize(800,600);
    setMouseTracking(true);
    InitializeTextures();
    Initialized = false;
}

void HexWidget::InitializeTextures()
{
    QPixmap HeroOriginalPixmap("NPC5Texture.png");
    if(!HeroOriginalPixmap.isNull())
    {
        this->HeroPixmap = HeroOriginalPixmap.scaled(
            QSizeF(2 * Hex::HexSize, 2 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap FogOriginalPixmap("FogTexture.png");
    if(!FogOriginalPixmap.isNull())
    {
        this->FogTexture = FogOriginalPixmap.scaled(
            QSizeF(2 * Hex::HexSize, 2 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap EnemyOriginalPixmap("NPC1Texture.png");
    if(!EnemyOriginalPixmap.isNull())
    {
        this->EnemyTexture = EnemyOriginalPixmap.scaled(
            QSizeF(1.7 * Hex::HexSize, 1.7 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap FriendOriginalPixmap("NPC2Texture.png");
    if(!FriendOriginalPixmap.isNull())
    {
        this->FriendTexture = FriendOriginalPixmap.scaled(
            QSizeF(1.7 * Hex::HexSize, 1.7 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap StructBreakOriginalPixmap("NPC3Texture.png");
    if(!StructBreakOriginalPixmap.isNull())
    {
        this->StructBreakTexture = StructBreakOriginalPixmap.scaled(
            QSizeF(1.7 * Hex::HexSize, 1.7 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap StructUnBreakOriginalPixmap("NPC4Texture.png");
    if(!StructUnBreakOriginalPixmap.isNull())
    {
        this->StructUnBreakTexture = StructUnBreakOriginalPixmap.scaled(
            QSizeF(1.7 * Hex::HexSize, 1.7 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap StandartHexOriginalPixmap("StandartHex.jpg");
    if(!StandartHexOriginalPixmap.isNull())
    {
        this->StandartVisibleHexTexture = StandartHexOriginalPixmap.scaled(
            QSizeF(2 * Hex::HexSize, 2 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);

        this->StandartExploredHexTexture = TintPixmap(this->StandartVisibleHexTexture, 0.4);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap HeroWithEnemyOriginalPixmap("FogTestTexture.png");
    if(!HeroWithEnemyOriginalPixmap.isNull())
    {
        this->HeroWithEnemyTexture = HeroWithEnemyOriginalPixmap.scaled(
            QSizeF(1.7 * Hex::HexSize, 1.7 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);



    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap HeroWithFriendOriginalPixmap("FogTestTexture.png");
    if(!HeroWithFriendOriginalPixmap.isNull())
    {
        this->HeroWithFriendTexture = HeroWithFriendOriginalPixmap.scaled(
            QSizeF(1.7 * Hex::HexSize, 1.7 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }

    QPixmap HeroWithStructOriginalPixmap("FogTestTexture.png");
    if(!HeroWithStructOriginalPixmap.isNull())
    {
        this->HeroWithStructTexture = HeroWithStructOriginalPixmap.scaled(
            QSizeF(1.7 * Hex::HexSize, 1.7 * Hex::HexSize).toSize(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        qWarning("Failed to load texture");
    }
}

QPixmap HexWidget::TintPixmap(const QPixmap& Source, qreal Strength)
{
    if(Source.isNull())
        return Source;

    QPixmap TintedPixmap = Source;
    QPainter p(&TintedPixmap);
    QColor OverlayColor = Qt::black;
    OverlayColor.setAlphaF(Strength);
    p.fillRect(TintedPixmap.rect(), OverlayColor);
    p.end();
    return TintedPixmap;
}

void HexWidget::paintEvent(QPaintEvent*)
{
    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.translate(OffsetX, OffsetY);
    Painter.scale(Scale, Scale);

    const auto& Grid = Map.GetMap();
    const Hex& HeroCurrHex = Map.GetQPointLoc(Hero.GetPosition());

    QHash<QPoint, QPen> HexOutlines;
    QHash<QPoint, QPolygonF> HexPolygons;

    for(const auto& Col : Grid)
    {
        for(const auto& Hex_ : Col)
        {
            QPoint CurrHexQPoint(Hex_.GetQR().first, Hex_.GetQR().second);
            auto Corners = Hex_.GetCorners();

            QPolygonF Polygon;
            for(const auto& c : Corners)
                Polygon << c;

            HexPolygons[CurrHexQPoint] = Polygon;

            QPainterPath HexClipPath;
            HexClipPath.addPolygon(Polygon);

            QPixmap BaseHexTexture;
            bool IsHexVisible = Hex_.VisibilityState();
            bool IsHexExplored = Hex_.ExplorationState();

            if(IsHexVisible)
                BaseHexTexture = StandartVisibleHexTexture;
            else if(IsHexExplored)
                BaseHexTexture = StandartExploredHexTexture;
            else
                BaseHexTexture = FogTexture;

            if(!BaseHexTexture.isNull())
            {
                QPointF center = Hex_.GetCenter();
                QPointF topLeft = center - QPointF(BaseHexTexture.width() / 2.0, BaseHexTexture.height() / 2.0);

                Painter.save();
                Painter.setClipPath(HexClipPath);
                Painter.drawPixmap(topLeft, BaseHexTexture);
                Painter.restore();
            }
            else
            {
                QBrush Brush;
                if(IsHexVisible)
                    Brush = Qt::white;
                else if(IsHexExplored)
                    Brush = Qt::darkGray;
                else
                    Brush = Qt::black;

                Painter.save();
                Painter.setClipPath(HexClipPath);
                Painter.fillPath(HexClipPath, Brush);
                Painter.restore();
            }

            if(IsHexVisible || IsHexExplored)
            {
                QPixmap UnitTexture;
                bool IsHeroOnHex = (QPoint(Hex_.GetQR().first, Hex_.GetQR().second) == Hero.GetPosition());

                if(IsHeroOnHex)
                {
                    if(Hex_.HaveUnit() && Hex_.GetUnit() != nullptr)
                    {
                        Unit* Unit_ = Hex_.GetUnit();
                        std::string UnitType = Unit_->GetSaveType();

                        if(UnitType == "Enemy")
                            UnitTexture = HeroWithEnemyTexture;
                        else if(UnitType == "Friend")
                            UnitTexture = HeroWithFriendTexture;
                        else if(UnitType == "StructBreak")
                            UnitTexture = HeroWithStructTexture;
                    }
                    else
                    {
                        UnitTexture = HeroPixmap;
                    }
                }
                else if(Hex_.HaveUnit())
                {
                    Unit* Unit_ = Hex_.GetUnit();
                    std::string UnitType = Unit_->GetSaveType();

                    if(UnitType == "Enemy")
                        UnitTexture = EnemyTexture;
                    else if(UnitType == "Friend")
                        UnitTexture = FriendTexture;
                    else if(UnitType == "StructBreak")
                        UnitTexture = StructBreakTexture;
                    else
                        UnitTexture = StructUnBreakTexture;
                }

                if(!UnitTexture.isNull())
                {
                    QPixmap FinalUnitTexture = UnitTexture;

                    if(!IsHexVisible && IsHexExplored)
                        FinalUnitTexture = TintPixmap(UnitTexture, 0.4);

                    QPointF center = Hex_.GetCenter();
                    QPointF topLeft = center - QPointF(FinalUnitTexture.width() / 2.0, FinalUnitTexture.height() / 2.0);

                    Painter.save();
                    Painter.setClipPath(HexClipPath);
                    Painter.drawPixmap(topLeft, FinalUnitTexture);
                    Painter.restore();
                }
            }

            QPen OutlinePen(Qt::black, 1);

            if(CurrHexQPoint != Hero.GetPosition())
            {
                bool IsNeighborToHero = HeroCurrHex.IsNeighbor(Hex_);

                if(IsNeighborToHero)
                {
                    bool IsBlocked = false;
                    if(Hex_.HaveUnit())
                    {
                        Unit* Unit_ = Hex_.GetUnit();
                        if(Unit_ && Unit_->GetSaveType() == "StructUnBreak")
                        {
                            IsBlocked = true;
                        }
                    }

                    if(IsBlocked)
                    {
                        OutlinePen.setColor(Qt::red);
                        OutlinePen.setWidthF(2.0);
                    }
                    else
                    {
                        OutlinePen.setColor(QColor(255, 215, 0));
                        OutlinePen.setWidthF(2.0);
                    }
                }
            }
            HexOutlines[CurrHexQPoint] = OutlinePen;
        }
    }

    QHashIterator<QPoint, QPolygonF> IterPolygons(HexPolygons);
    while(IterPolygons.hasNext())
    {
        IterPolygons.next();
        const QPoint& CurrHexQPoint = IterPolygons.key();
        const QPolygonF& Polygon = IterPolygons.value();

        if(HexOutlines.contains(CurrHexQPoint))
        {
            const QPen& CurrPen = HexOutlines[CurrHexQPoint];
            if(CurrPen.color() == Qt::black)
            {
                Painter.setBrush(Qt::NoBrush);
                Painter.setPen(CurrPen);
                Painter.drawPolygon(Polygon);
            }
        }
    }

    QHashIterator<QPoint, QPolygonF> IterPolygonsGold(HexPolygons);
    while(IterPolygonsGold.hasNext())
    {
        IterPolygonsGold.next();
        const QPoint& CurrHexQPoint = IterPolygonsGold.key();
        const QPolygonF& Polygon = IterPolygonsGold.value();

        if(HexOutlines.contains(CurrHexQPoint))
        {
            const QPen& CurrPen = HexOutlines[CurrHexQPoint];
            if(CurrPen.color() == QColor(255, 215, 0))
            {
                Painter.setBrush(Qt::NoBrush);
                Painter.setPen(CurrPen);
                Painter.drawPolygon(Polygon);
            }
        }
    }

    QHashIterator<QPoint, QPolygonF> IterPolygonsRed(HexPolygons);
    while(IterPolygonsRed.hasNext())
    {
        IterPolygonsRed.next();
        const QPoint& CurrHexQPoint = IterPolygonsRed.key();
        const QPolygonF& Polygon = IterPolygonsRed.value();

        if(HexOutlines.contains(CurrHexQPoint))
        {
            const QPen& CurrPen = HexOutlines[CurrHexQPoint];
            if(CurrPen.color() == Qt::red)
            {
                Painter.setBrush(Qt::NoBrush);
                Painter.setPen(CurrPen);
                Painter.drawPolygon(Polygon);
            }
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

            //непробивні
            if(TargetHex.HaveUnit())
            {
                Unit* Unit_ = TargetHex.GetUnit();
                if(Unit_ && Unit_->GetSaveType() == "StructUnBreak")
                    return;
            }

            if(CurrHex.IsNeighbor(TargetHex))
            {
                Hero.MoveTo(HexCord); // Герой перемістився на HexCord
                Map.UpdateVisibility(Hero.GetPosition());
                update(); // Оновлюємо карту, щоб показати героя на новій клітинці (можливо, з ворогом)

                // 2. Тепер перевіряємо, чи є ворог на клітинці, КУДИ ПЕРЕМІСТИВСЯ герой
                const Hex& heroIsOnThisHex = Map.GetQPointLoc(Hero.GetPosition()); // Клітинка, де зараз герой

                if(heroIsOnThisHex.HaveUnit())
                {
                    Unit* unitOnCurrentHex = heroIsOnThisHex.GetUnit();
                    if(unitOnCurrentHex && unitOnCurrentHex->GetSaveType() == "Enemy")
                    {
                        qWarning("Hero moved onto an enemy hex! Starting fight.");

                        QPixmap enemyDisplayTexture = this->EnemyTexture;
                        if(enemyDisplayTexture.isNull())
                        {
                            qWarning("HexWidget: EnemyTexture is null! Using placeholder for Fight window.");
                            enemyDisplayTexture = QPixmap(200,150);
                            enemyDisplayTexture.fill(Qt::red);
                        }


                        MainHero* heroUnit = &(this->Hero);
                        Unit* enemyUnit = unitOnCurrentHex;


                        Fight* fightDialog = new Fight(enemyDisplayTexture, heroUnit, enemyUnit, this);
                        fightDialog->setAttribute(Qt::WA_DeleteOnClose);
                        int fightResultCode = fightDialog->exec();

                        if (fightResultCode == QDialog::Accepted)
                        {
                            qDebug("Fight won! Enemy removed from hero's current hex.");
                            Map.ClearUnitAt(Hero.GetPosition());

                            update();
                        }
                        else
                            if (heroUnit->GetHP() <= 0) { // Якщо HP героя <= 0, то це програш
                                qDebug("Fight lost (Hero HP <= 0). Emitting gameOver signal.");
                                emit gameOver();
                                return;
                            } else {
                                // Якщо HP героя > 0, це була втеча
                                qDebug("Fight ended (fled or closed without win/loss). Hero remains on hex.");
                                Map.ClearUnitAt(Hero.GetPosition());
                                update();
                            }
                    }
                }
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

bool HexWidget::LoadMapFromFile(const QString& filePath)
{
    QPoint heroPos;
    bool Success = Map.LoadFromFile(filePath, heroPos);

    if(Success)
    {
        Hero.MoveTo(heroPos);
        Map.UpdateVisibility(Hero.GetPosition());
        Initialized = false;
        update();
    }
    return Success;
}
