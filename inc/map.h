#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QPen>
#include <QTimer>
#include <QPalette>

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
    /*!
     * \brief ui
     * Contains information about UI
     */
    Ui::Map *ui;
    /*!
     * \brief Path
     * Path robot made while riding
     */
    QPainterPath Path;
    /*!
     * \brief LastPoint
     * Robot's current position
     */
    QPoint LastPoint;
    /*!
     * \brief LastXPos
     * Robot's current X coordinates
     */
    double LastXPos;
    /*!
     * \brief LastYPos
     * Robot's current Y coordinates
     */
    double LastYPos;
    /*!
     * \brief XOffset
     * X axis offset calculated to start from center of the map
     */
    double XOffset;
    /*!
     * \brief YOffset
     * Y axis offset calculated to start from center of the map
     */
    double YOffset;
    /*!
     * \brief Tim
     * Timer responsible for repainting path
     */
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
