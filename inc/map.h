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

/*!
 * \brief The Map class
 * Widget drawing current position of robot and its path
 */
class Map : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Map
     * \param[in] parent
     * Sets signal-slot connections and robot starting point to center
     */
    explicit Map(QWidget *parent = nullptr);
    ~Map();
    /*!
     * \brief AddPoint
     * \param[in] X - new X coordinats of the robot
     * \param[in] Y - new Y coordinates of the robot
     * Changes robot current position and adds path to this point
     */
    void AddPoint(double X, double Y);
    /*!
     * \brief paintEvent
     * Draws robot position and path
     * Reimplemented function
     */
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

private slots:
    /*!
     * \brief CallRepaint
     * Refreshes widget
     */
    void CallRepaint();
    /*!
     * \brief ClearMap
     * Clears path, sets robot position to center and calculates new drawing offset
     */
    void ClearMap();
};

#endif // MAP_H
