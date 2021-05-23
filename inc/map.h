#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QPen>
#include <QTimer>

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();
    void AddPoint(double X, double Y);
    void paintEvent(QPaintEvent *);

private:
    Ui::Map *ui;
    QPainterPath Path;
    QPoint LastPoint;
    double LastXPos;
    double LastYPos;
    double XOffset;
    double YOffset;
    QTimer *Tim;

    void Draw(QPainter *Painter);

private slots:
    void CallRepaint();
    void ClearMap();
};

#endif // MAP_H
