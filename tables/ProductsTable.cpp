#include "headers/ProductsTable.h"

ProductsTable::ProductsTable(QWidget* parent) : CustomTable(parent)
{
}

void ProductsTable::formatTable()
{

    QStringList headersList;
    headersList << "Nazwa produktu" << "Węglowodany" << "Tłuszcz" << "Białko" << "Błonnik";
    setColumnCount(5);
    setRowCount(0);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setHorizontalHeaderLabels(headersList);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ProductsTable::addProductsToTable(void)
{

    formatTable();
    auto set = starterGlobalObj.globalProductsObj.getProductsSet();
    setToTable(set);
}

void ProductsTable::addDishesProductsToTable(std::string dishName)
{
    formatTable();

    auto set = starterGlobalObj.globalDishesObj.getDishByName(dishName).getProductsSet();
    setToTable(set);

}

void ProductsTable::setToTable(std::set <Product> set)
{
    for(auto product : set)
    {
        insertRow(rowCount());
        auto nutMap = product.getNutritionsMap();
        setItem(rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(product.getProductName())));
        setItem(rowCount()-1, 1, new QTableWidgetItem(QString::number( nutMap["carbo"] )  + "g"));
        setItem(rowCount()-1, 2, new QTableWidgetItem(QString::number( nutMap["fat"] )  + "g"));
        setItem(rowCount()-1, 3, new QTableWidgetItem(QString::number( nutMap["protein"] )  + "g"));
        setItem(rowCount()-1, 4, new QTableWidgetItem(QString::number( nutMap["fiber"] )  + "g"));
    }
}

void ProductsTable::addMealProductsToTable(std::string timestamp)
{
    formatTable();

    auto productsSet = starterGlobalObj.globalMealsObj.getMealByTimestamp(timestamp).getProductsSet();
    setToTable(productsSet);

}


void ProductsTable::insertProduct(Product product)
{
    auto nutMap = product.getNutritionsMap();

    if(nutMap["carbo"] < 0 || nutMap["fat"] < 0 || nutMap["protein"] < 0 || nutMap["fiber"] < 0) return;


    insertRow(rowCount());
    setCellWidget(rowCount()-1, 0, new QCheckBox());
    setItem(rowCount()-1, 1, new QTableWidgetItem(QString::fromStdString(product.getProductName())));
    setItem(rowCount()-1, 2, new QTableWidgetItem(QString::number( nutMap["carbo"] )  + "g"));
    setItem(rowCount()-1, 3, new QTableWidgetItem(QString::number( nutMap["fat"] )  + "g"));
    setItem(rowCount()-1, 4, new QTableWidgetItem(QString::number( nutMap["protein"] )  + "g"));
    setItem(rowCount()-1, 5, new QTableWidgetItem(QString::number( nutMap["fiber"] )  + "g"));
}


void ProductsTable::addProductsToTableWithCheckbox()
{
    formatTable();

    QStringList headersList;
    headersList << " " << "Nazwa produktu" << "Węglowodany" << "Tłuszcz" << "Białko" << "Błonnik";
    setColumnCount(6);
    setHorizontalHeaderLabels(headersList);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    setColumnWidth(0, 25);
    setColumnWidth(1, 195);
    setColumnWidth(2, 195);
    setColumnWidth(3, 195);
    setColumnWidth(4, 195);
    setColumnWidth(5, 195);


    auto set = starterGlobalObj.globalProductsObj.getProductsSet();
    for(auto product : set)
    {
        insertRow(rowCount());

        auto nutMap = product.getNutritionsMap();
        setCellWidget(rowCount()-1, 0, new QCheckBox());
        setItem(rowCount()-1, 1, new QTableWidgetItem(QString::fromStdString(product.getProductName())));
        setItem(rowCount()-1, 2, new QTableWidgetItem(QString::number( nutMap["carbo"] )  + "g"));
        setItem(rowCount()-1, 3, new QTableWidgetItem(QString::number( nutMap["fat"] )  + "g"));
        setItem(rowCount()-1, 4, new QTableWidgetItem(QString::number( nutMap["protein"] )  + "g"));
        setItem(rowCount()-1, 5, new QTableWidgetItem(QString::number( nutMap["fiber"] )  + "g"));
    }
}
