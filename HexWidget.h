#ifndef HEXWIDGET_H
#define HEXWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include <algorithm>
#include "Map.h"
#include "Unit.h"

class HexWidget : public QWidget{
    Q_OBJECT

private:
    HexMap Map;
    MainHero Hero;

    float Scale = 1.0;
    float OffsetX = 0.0;
    float OffsetY = 0.0;
    QPoint SelectedHex = {-1, -1};
    bool IsDragging = false;
    QPoint LastMousePos;
    bool Initialized = false;
    QPoint CenterHex = QPoint(0, 0);
    QPoint HoveredHex = QPoint(INT_MAX, INT_MAX);
    QPixmap HeroPixmap;
    QPixmap StandartVisibleHexTexture;
    QPixmap StandartExploredHexTexture;
    QPixmap FogTexture;
    QPixmap EnemyTexture;
    QPixmap FriendTexture;
    QPixmap StructBreakTexture;
    QPixmap StructUnBreakTexture;
    QPixmap HeroWithEnemyTexture;
    QPixmap HeroWithFriendTexture;
    QPixmap HeroWithStructTexture;

    QPoint PixelToHex(QPointF p) const;
    QPoint CubeToAxial(float qc, float rc) const;
    QRectF GetMapBoundingRect() const;
    void InitializeTextures();
    QPixmap TintPixmap(const QPixmap& Source, qreal Strength = 0.4);


public:
    HexWidget(int NRadius, QWidget* parent = nullptr);
    void SaveMapToFile(const QString& filePath);
    bool LoadMapFromFile(const QString& filePath);


protected:
    void paintEvent(QPaintEvent*) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void leaveEvent(QEvent*) override;
};

#endif // HEXWIDGET_H
