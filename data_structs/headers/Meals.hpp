//
//  Meals.hpp
//  projekt pk41
//
//  Created by Patryk Langer on 22/03/2021.
//  Copyright © 2021 Patryk Langer. All rights reserved.
//

#ifndef Meals_hpp
#define Meals_hpp

#include <stdio.h>
#include "Meal.hpp"
#include <set>
#include <QMessageBox>
#include "../../networking/headers/Fetcher.hpp"

class Meals
{
private:
    std::set <Meal> mealsSet;
    Fetcher fetcher;
public:
    Meals();
    void start();
    void fetchMealsFromJson(Json::Value jsonData);
    void pushBackMeal(Meal meal);
    Meal getMealByTimestamp(std::string timestamp);
    std::set <Meal> getMealsSet(void);
};

#endif /* Meals_hpp */
