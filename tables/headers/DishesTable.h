#ifndef DISHESTABLE_H
#define DISHESTABLE_H

#include "CustomTable.h"

class DishesTable : public CustomTable
{
public:
    DishesTable(QWidget* parent);
    void formatTable();
    void addProductsToTable();
};

#endif // DISHESTABLE_H
