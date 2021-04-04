//
//  Dishes.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#include "headers/Dishes.hpp"

Dishes::Dishes() : fetcher("https://carbonex-46f1e-default-rtdb.firebaseio.com/.json")
{
}
void Dishes::start()
{
    fetcher.fetch();
    this->fetchDishesFromJson(fetcher.getJsonData());
}

void Dishes::fetchDishesFromJson(Json::Value jsonData)
{
    try
    {
        if (jsonData.isBool()) throw std::runtime_error("Empty JSON Data");
        
        Json::Value& dishes = jsonData["dishes"];
    
        for (auto const& type : dishes.getMemberNames())
        {
            Dish temp(type);
            Json::Value& dishes1 = dishes[type];
            for(auto const& type1 : dishes1.getMemberNames()) {
                Json::Value& dishes2 = dishes1[type1];
                temp.addProduct(
                                type1,
                                dishes2["protein"].asFloat(),
                                dishes2["fat"].asFloat(),
                                dishes2["carbo"].asFloat(),
                                dishes2["fiber"].asFloat(),
                                false);
            }
            dishesSet.insert(temp);
        }
        
    } catch (std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
    }
}

Dish Dishes::getDishByName(std::string dishName)
{
    for(auto dish : dishesSet) if(!dishName.compare(dish.getDishName())) return dish;
    return Dish();
}

void Dishes::showDishes(void) {
    for(auto it : dishesSet) {
        std::cout <<
        "Nazwa potrawy: " << it.getDishName() <<
        "\nSkładniki: \n";
        for (auto it1 : it.getProducts()) {
            std::cout <<
            "Nazwa: " << it1.getProductName() <<
            "\nWęglowodany: " << it1.getCarbo() <<
            "\nTłuszcz: " << it1.getFat() <<
            "\nBiałko: " << it1.getProtein() <<
            "\nBłonnik: " << it1.getFiber() <<
            std::endl;
            
        }
        std::cout <<
        "WW: " << it.getCarboEx() <<
        "\nWBT: " << it.getFatProtEx() <<
        "\n\n";
    }
}

std::set<Dish> Dishes::getDishesSet(void)
{
    return dishesSet;
}

void Dishes::pushBackDish(Dish dish)
{
    dishesSet.insert(dish);
}


void Dishes::deleteIfExist(Dish& dish)
{
    for(auto el : dishesSet)
    {
        if(el.getDishName() == dish.getDishName())
        {
            dishesSet.erase(el);
            return;
        }
    }
}
