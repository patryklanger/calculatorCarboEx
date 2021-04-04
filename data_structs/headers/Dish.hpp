//
//  Dish.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef Dish_hpp
#define Dish_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <json/json.h>
#include "Product.hpp"
#include "../../networking/headers/Poster.hpp"
//#include "../../global_obj.hpp"

class Dish : public Product {
private:
    std::set <Product> products;
    using Product::getProductName;

    void deleteFromSetIfExist(Product product);
public:
    
    /*------constructors------*/
    
    Dish(std::string productName="Dish");
    
    /*------overloaded opeators------*/
    
    bool operator==(const Dish& element) const;
    bool operator<(const Dish& element) const;
    bool operator>(const Dish& element) const;
    
    
    /*------methods------*/
    
    std::set<Product> getProductsSet() const;
    
    Product dishToProduct();
    
    bool checkIfIsPresentInSet(std::set<Dish> dishesSet);
    
    std::string getDishName(void) const;
    std::set<Product> getProducts(void);
    
    void addProduct(std::string name, float protein, float fat, float carbo, float dietFiber, bool updateProduct = true);
    
    void post();
    void deleteDish();
    Json::Value dishToJson(void);
};

#endif /* Dish_hpp */
