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
 * Qframe displaying data from sensors in a table
 */
class DataTable : public QFrame
{
    Q_OBJECT

public:
    /*!
     * \brief DataTable
     * \param parent - parent QFrame
     * Sets display parameters
     */
    explicit DataTable(QWidget *parent = nullptr);
    ~DataTable();

    /*!
     * \brief UpdateDisplay
     * Displays in a table currently stored data
     */
    void UpdateDisplay();

    /*!
     * \brief UpdateDisplay
     * \param[in] Dat - data to be displayed
     * Displays in a table data Dat
     * Updates data stored in a class
     */
    void UpdateDisplay(DataForDataTable const Dat);

    /*!
     * \brief UpdateData
     * \param[in] dat - data sample which can be displayed in a table
     * Updates data stored in a class
     *
     * NOTE: doesnt refresh display
     */
    void UpdateData(DataForDataTable const Dat);

    void UpdateGraphics();

private:

    void InitPlots();

    /*!
     * \brief ui
     * Stores information about Ui
     */
    Ui::DataTable *ui;
    /*!
     * \brief Data
     * Displayed data
     */
    DataForDataTable *Data;

    QPixmap WindRoseImg;
    QPixmap Arrow;
    QCPBars *EncodersBarOverZero;
    QCPBars *EncodersBarBelowZero;
    QCPBars *PWMBar;

    void RotateWindRose();
};

#endif // DATATABLE_H
