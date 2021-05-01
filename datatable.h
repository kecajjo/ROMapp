#ifndef DATATABLE_H
#define DATATABLE_H

#include <QFrame>
#include "datafordatatable.h"

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
    explicit DataTable(QWidget *parent = nullptr);
    /*!
      * \brief ~DataTable
      * frees memory allocated for ui and data
      */
    ~DataTable();

    /*!
     * \brief UpdateDisplay
     * Displays in a table currently stored data
     */
    void UpdateDisplay();

    /*!
     * \brief UpdateDisplay
     * \param Dat - data to be displayed
     * Displays in a table data Dat
     * Updates data stored in a class
     */
    void UpdateDisplay(DataForDataTable const Dat);

    /*!
     * \brief UpdateData
     * \param dat - data sample which can be displayed in a table
     * Updates data stored in a class
     *
     * NOTE: doesnt refresh display
     */
    void UpdateData(DataForDataTable const Dat);

private:
    Ui::DataTable *ui;
    DataForDataTable *Data;
};

#endif // DATATABLE_H
