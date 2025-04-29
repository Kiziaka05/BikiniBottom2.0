#ifndef HEXWIDGET_H
#define HEXWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include "Map.h"

class HexWidget : public QWidget{
    Q_OBJECT

public:
    HexMap Map;
    float Scale = 1.0;
    float OffsetX = 0.0;
    float OffsetY = 0.0;

    QPoint SelectedHex = {-1, -1};

    HexWidget(QWidget* parent = nullptr) : QWidget(parent), Map(20,20)
    {
        setMinimumSize(800,600);
    }

protected:
    void paintEvent(QPaintEvent*) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    QPoint PixelToHex(QPointF p);
    QPoint CubeToAxial(float qc, float rc);
};

#endif // HEXWIDGET_H
