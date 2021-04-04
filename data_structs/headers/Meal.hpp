//
//  Meal.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef Meal_hpp
#define Meal_hpp

#include <stdio.h>
#include <chrono>
#include <ctime>
#include <typeinfo>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>

#include "Food.hpp"
#include "Dishes.hpp"
#include "Products.hpp"
#include "Product.hpp"
#include "../../networking/headers/Poster.hpp"


class Meal : public Food {
private:
    Poster poster;
    std::string timeOfDay = std::string();
    std::string timestamp;
    std::set<Product> productsSet;
public:
    
    /*------constructors------*/
    
    Meal(std::string timestamp = "");
    
    /*------methods------*/
    
    std::string getTimestamp (void) const;
    std::set<Product> getProductsSet(void) const;
    
    bool operator<(const Meal& element) const;
    bool operator>(const Meal& element) const;
    bool operator==(const Meal& element) const;
    
    void addToMap(Product prod);
    void addToMap(Dish dish);
    void post(void);
    std::string getDate(void);
    std::string getTimeOfDay(void);
    
    Poster getPoster(void);
    
    Json::Value mealToJson(void);
    
    
};

#endif /* Meal_hpp */
