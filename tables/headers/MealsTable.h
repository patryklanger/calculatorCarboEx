#ifndef MEALSTABLE_H
#define MEALSTABLE_H

#include "CustomTable.h"

class MealsTable : public CustomTable
{
public:
    MealsTable(QWidget* parent=0);
    void addProductsToTable(void);
    void formatTable();
};

#endif // MEALSTABLE_H
