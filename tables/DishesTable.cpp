#include "headers/DishesTable.h"

DishesTable::DishesTable(QWidget* parent) : CustomTable(parent)
{

}

void DishesTable::formatTable()
{

    QStringList headersList;
    headersList << "Nazwa dania" << "WW" << "WBT";
    setColumnCount(3);
    setRowCount(0);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setHorizontalHeaderLabels(headersList);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DishesTable::addProductsToTable(void)
{

    formatTable();
    auto set = starterGlobalObj.globalDishesObj.getDishesSet();

    for(auto product : set)
    {
        insertRow(rowCount());
        setItem(rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(product.getDishName())));
        setItem(rowCount()-1, 1, new QTableWidgetItem(QString::number( product.getCarboEx() )));
        setItem(rowCount()-1, 2, new QTableWidgetItem(QString::number( product.getFatProtEx() )));
    }
}
