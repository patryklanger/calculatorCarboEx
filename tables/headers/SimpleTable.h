#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include "CustomTable.h"

class SimpleTable : public CustomTable
{
public:
    SimpleTable(QWidget* parent);
    void formatTable();
    void addProductsToTable();
    void addProductToTable(std::string name);
};
#endif // SIMPLETABLE_H
