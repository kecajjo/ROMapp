#ifndef DATATABLE_H
#define DATATABLE_H

#include <QFrame>
#include <QDir>
#include <QTimer>
#include "datafordatatable.h"
#include "qcustomplot.h"

namespace Ui {
class DataTable;
}

/*!
 * \brief The DataTable class
 * Qframe displaying data from the robot.
 */
class DataTable : public QFrame
{
    Q_OBJECT

public:
    /*!
     * \brief DataTable
     * \param parent - parent QFrame
     * Sets display parameters.
     */
    explicit DataTable(QWidget *parent = nullptr);
    ~DataTable();

    /*!
     * \brief UpdateDisplay
     * Displays in a table currently stored data and updates graphs.
     */
    void UpdateDisplay();

    /*!
     * \brief UpdateDisplay
     * \param[in] Dat - data to be displayed
     * Displays in a table currently stored data and updates graphs.
     * Updates data stored in the class.
     */
    void UpdateDisplay(DataForDataTable const Dat);

    /*!
     * \brief UpdateData
     * \param[in] dat - data sample which can be displayed in a table
     * Updates data stored in the class.
     *
     * NOTE: Doesn't refresh display.
     */
    void UpdateData(DataForDataTable const Dat);

    /*!
     * \brief UpdateGraphics
     * Updates the wind rose graphics rotation so its top is the heading direction.
     */
    void UpdateGraphics();

private:

    /*!
     * \brief InitPlots
     * Initializes graphs showing current PWM and wheel speed values.
     */
    void InitPlots();

    /*!
     * \brief ui
     * Stores information about the Ui.
     */
    Ui::DataTable *ui;
    /*!
     * \brief Data
     * Displayed data.
     */
    DataForDataTable *Data;
    /*!
     * \brief WindRoseImg
     * Image of the wind rose.
     */
    QPixmap WindRoseImg;
    /*!
     * \brief Arrow
     * Image of the arrow shown next to the wind rose.
     */
    QPixmap Arrow;
    /*!
     * \brief EncodersBarOverZero
     * Bar in the graph showing wheel speed if its over 0.
     */
    QCPBars *EncodersBarOverZero;
    /*!
     * \brief EncodersBarBelowZero
     * Bar in the graph showing wheel speed if its below 0.
     */
    QCPBars *EncodersBarBelowZero;
    /*!
     * \brief PWMBar
     * Bar in the graph showing PWM values.
     */
    QCPBars *PWMBar;

    /*!
     * \brief RotateWindRose
     * Rotates the wind rose by some angle so the top of the image points to the heading direction.
     */
    void RotateWindRose();
};

#endif // DATATABLE_H
