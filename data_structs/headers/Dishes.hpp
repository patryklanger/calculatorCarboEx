//
//  Dishes.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef Dishes_hpp
#define Dishes_hpp

#include <stdio.h>
#include <set>
#include "Dish.hpp"
#include <QMessageBox>
#include <string>
#include "../../networking/headers/Fetcher.hpp"

class Dishes {
private:
    std::set <Dish> dishesSet;
    Fetcher fetcher;
    
public:
    Dishes();
    void start();
    void fetchDishesFromJson(Json::Value jsonData);
    void showDishes(void);
    Dish getDishByName(std::string dishName);
    void pushBackDish(Dish dish);
    void deleteIfExist(Dish& dish);
    std::set <Dish> getDishesSet(void);
    
};


#endif /* Dishes_hpp */
