//
//  Products.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#include "headers/Products.hpp"
#include "../global_obj.hpp"
#include <QFile>

Products::Products() : fetcher("https://carbonex-46f1e-default-rtdb.firebaseio.com/.json")
{
    
}
void Products::start()
{
    fetcher.fetch();
    this->fetchProductsFromJson(fetcher.getJsonData());

}

void Products::fetchProductsFromJson(Json::Value jsonData)
{
    try
    {

        if (jsonData.isBool()) throw std::runtime_error("Empty JSON Data");
        
        Json::Value& products = jsonData["products"];

    
        
        for (auto const& name : products.getMemberNames()) {
            
            Json::Value& product = products[name];
                Product temp(
                                product["protein"].asFloat(),
                                product["fat"].asFloat(),
                                product["carbo"].asFloat(),
                                product["fiber"].asFloat(),
                             name,
                             false);
            productsSet.insert(temp);
        }
        
    } catch (std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
    }



}

std::set<Product> Products::getProductsSet ()
{
    return productsSet;
}


void Products::pushBackProduct(Product prod)
{
    productsSet.insert(prod);
}

void Products::deleteIfExist(Product& product)
{
    for(auto el : productsSet)
    {
        if(el.getProductName() == product.getProductName())
        {
            productsSet.erase(el);
            return;
        }
    }
}

Product Products::getProductByName(std::string name)
{
    for(auto product : productsSet)if(!name.compare(product.getProductName())) return product;
    return Product(0,0,0,0);
}
