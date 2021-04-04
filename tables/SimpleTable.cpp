#include "headers/SimpleTable.h"

SimpleTable::SimpleTable(QWidget* parent) : CustomTable(parent){}

void SimpleTable::formatTable()
{
    QStringList headersList;
    headersList << "Nazwa";
    setColumnCount(1);
    setRowCount(0);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setHorizontalHeaderLabels(headersList);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void SimpleTable::addProductsToTable(){}
void SimpleTable::addProductToTable(std::string name)
{
    formatTable();
    insertRow(rowCount());
    setItem(rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(name)));
}

