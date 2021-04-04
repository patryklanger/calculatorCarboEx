#ifndef START_H
#define START_H


#include "data_structs/headers/Dishes.hpp"
#include "data_structs/headers/Meals.hpp"
#include "data_structs/headers/Products.hpp"

class Start
{
public:
    Products globalProductsObj;
    Dishes globalDishesObj;
    Meals globalMealsObj;

    Start();
    void init();
};

#endif // START_H
