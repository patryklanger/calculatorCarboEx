#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QTableWidget>
#include <QHeaderView>
#include "../../global_obj.hpp"

class CustomTable : public QTableWidget
{
public:
    CustomTable(QWidget* parent);
    virtual void formatTable();
    virtual void addProductsToTable();
};

#endif // CUSTOMTABLE_H
