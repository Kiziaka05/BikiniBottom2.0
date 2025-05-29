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

public:
    HexMap Map;
    float Scale = 1.0;
    float OffsetX = 0.0;
    float OffsetY = 0.0;
    QPoint SelectedHex = {-1, -1};
    bool IsDragging = false;
    QPoint LastMousePos;
    bool Initialized = false;
    QPoint CenterHex = QPoint(0, 0);
    QPoint HoveredHex = QPoint(INT_MAX, INT_MAX);
    MainHero Hero;
    QPixmap HeroPixmap;
    QPointF HeroTopLeft;
    void SaveMapToFile(const QString& filePath);
    void LoadMapFromFile(const QString& filePath);
    QPixmap texture1= QPixmap("hero1.jpg").scaled(QSizeF(2 * HexSize, 2 * HexSize).toSize(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    HexWidget(QWidget* parent = nullptr) : QWidget(parent), Map(15), Hero(QPoint(0,0))
    {
        setMinimumSize(800,600);
        setMouseTracking(true);
    }

protected:
    void paintEvent(QPaintEvent*) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    QPoint PixelToHex(QPointF p);
    QPoint CubeToAxial(float qc, float rc);
    QRectF GetMapBoundingRect();
    void resizeEvent(QResizeEvent* event) override;
    void leaveEvent(QEvent*) override;
};

#endif // HEXWIDGET_H
