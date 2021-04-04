//
//  Products.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef Products_hpp
#define Products_hpp

#include <stdio.h>
#include "Product.hpp"
#include <set>
#include <QMessageBox>
#include "../../networking/headers/Fetcher.hpp"

class Products
{
private:
    std::set <Product> productsSet;
    Fetcher fetcher;
public:
    Products();
    void start();
    void fetchProductsFromJson(Json::Value jsonData);
    void pushBackProduct(Product prod);
    void deleteIfExist(Product& product);
    Product getProductByName(std::string name);
    std::set <Product> getProductsSet(void);
};

#endif /* Products_hpp */
