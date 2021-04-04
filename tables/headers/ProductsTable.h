#ifndef PRODUCTSTABLE_H
#define PRODUCTSTABLE_H

#include "CustomTable.h"
#include <QCheckBox>

class ProductsTable : public CustomTable
{
public:
    ProductsTable(QWidget* parent=0);
    void addProductsToTable(void);
    void addDishesProductsToTable(std::string dishName);
    void addMealProductsToTable(std::string timestamp);
    void formatTable();
    void addProductsToTableWithCheckbox();
    void insertProduct(Product product);
private:
    void setToTable(std::set <Product> set);

};

#endif // PRODUCTSTABLE_H
