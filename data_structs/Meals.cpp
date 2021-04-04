//
//  Meals.cpp
//  projekt pk41
//
//  Created by Patryk Langer on 22/03/2021.
//  Copyright © 2021 Patryk Langer. All rights reserved.
//

#include "headers/Meal.hpp"
#include "../global_obj.hpp"

Meals::Meals() :
    fetcher("https://carbonex-46f1e-default-rtdb.firebaseio.com/.json")
{
}
void Meals::start()
{
    fetcher.fetch();
    this->fetchMealsFromJson(fetcher.getJsonData());
}

void Meals::fetchMealsFromJson(Json::Value jsonData)
{
    try {
        {
            if (jsonData.isBool()) throw std::runtime_error("Empty JSON Data");
            
            Json::Value& meals = jsonData["meals"];
            
            for(auto const& type : meals.getMemberNames())
            {
                Meal temp(type);
                Json::Value& meals1 = meals[type];
                Json::Value& dishes = meals1["dishes"];
                for (auto const& dish : dishes.getMemberNames())
                {
                    Dish tempDish(dish);
                    Json::Value& dishes1 = dishes[dish];
                    for(auto const& dish2 : dishes1.getMemberNames()) {
                        Json::Value& dishes2 = dishes1[dish2];
                        tempDish.addProduct(
                                        dish2,
                                        dishes2["protein"].asFloat(),
                                        dishes2["fat"].asFloat(),
                                        dishes2["carbo"].asFloat(),
                                        dishes2["fiber"].asFloat(),
                                            false);
                    }
                    temp.addToMap(tempDish);
                    
                }
                Json::Value& products = meals1["products"];
                for (auto const& name : products.getMemberNames()) {
                    
                    Json::Value& product = products[name];
                        Product tempProduct(
                                        product["protein"].asFloat(),
                                        product["fat"].asFloat(),
                                        product["carbo"].asFloat(),
                                        product["fiber"].asFloat(),
                                     name,
                                     false);
                    temp.addToMap(tempProduct);
                }
                mealsSet.insert(temp);
            }
            
        }
    } catch (std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
    }
}

Meal Meals::getMealByTimestamp(std::string timestamp)
{
    for(auto meal : mealsSet) if(!timestamp.compare(meal.getTimestamp())) return meal;
    return Meal();
}

void Meals::pushBackMeal(Meal meal)
{
    mealsSet.insert(meal);
}

std::set <Meal> Meals::getMealsSet(void)
{
    return mealsSet;
}
