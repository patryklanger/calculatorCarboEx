#include "Start.h"


    Start::Start()
    {
    }
    void Start::init()
    {
        globalProductsObj.start();
        globalDishesObj.start();
        globalMealsObj.start();
    }
