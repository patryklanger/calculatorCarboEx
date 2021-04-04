#include "headers/MealsTable.h"

MealsTable::MealsTable(QWidget* parent) : CustomTable(parent)
{
}



void MealsTable::formatTable()
{

    QStringList headersList;
    headersList << "Data posiłku" << "WW" << "WBT" << "Węglowodany" << "Tłuszcz" << "Białko" << "Błonnik" << "Timestamp";
    setColumnCount(8);
    setColumnHidden(7, true);
    setRowCount(0);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setHorizontalHeaderLabels(headersList);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MealsTable::addProductsToTable(void)
{

    formatTable();
    auto set = starterGlobalObj.globalMealsObj.getMealsSet();

    for(auto product : set)
    {
        insertRow(rowCount());
        setItem(rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(product.getDate())));
        setItem(rowCount()-1, 1, new QTableWidgetItem(QString::number( product.getCarboEx() )));
        setItem(rowCount()-1, 2, new QTableWidgetItem(QString::number( product.getFatProtEx() )));
        setItem(rowCount()-1, 3, new QTableWidgetItem(QString::number( product.getCarbo() )  + "g"));
        setItem(rowCount()-1, 4, new QTableWidgetItem(QString::number( product.getFat() )  + "g"));
        setItem(rowCount()-1, 5, new QTableWidgetItem(QString::number( product.getProtein() )  + "g"));
        setItem(rowCount()-1, 6, new QTableWidgetItem(QString::number( product.getFiber() )  + "g"));
        setItem(rowCount()-1, 7, new QTableWidgetItem(QString::fromStdString( product.getTimestamp() )));
    }
}
