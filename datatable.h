#ifndef DATATABLE_H
#define DATATABLE_H

#include <QFrame>
#include "datafordatatable.h"

namespace Ui {
class DataTable;
}

class DataTable : public QFrame
{
    Q_OBJECT

public:
    explicit DataTable(QWidget *parent = nullptr);
    ~DataTable();

    /*
     * Displays in a table currently stored data
    */
    void UpdateDisplay();

    /*
     * Displays in a table data Dat
    */
    void UpdateDisplay(DataForDataTable const Dat);

    /*
     * Updates data which can be displayed
    */
    void UpdateData(DataForDataTable const dat);

private:
    Ui::DataTable *ui;
    DataForDataTable *data;
};

#endif // DATATABLE_H
