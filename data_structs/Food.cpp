//
//  Food.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#include "headers/Food.hpp"

/*------constructors------*/

Food::Food(
           float protein,
           float fat,
           float carbo,
           float dietFiber)
{
    try
    {
        if (dietFiber > carbo) throw std::invalid_argument(std::string("Fiber cannot be bigger than carbo"));
        nutritions.insert(std::pair<std::string, float> ("protein", protein));
        nutritions.insert(std::pair<std::string, float> ("fat", fat));
        nutritions.insert(std::pair<std::string, float> ("carbo", carbo));
        nutritions.insert(std::pair<std::string, float> ("fiber", dietFiber));
    } catch (std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
        nutritions.insert(std::pair<std::string, float> ("protein", -99));
    }
}

/*------methods------*/

float Food::getCarboEx(void)
{
    return (nutritions["carbo"] - nutritions["fiber"])/10;
}

float Food::getFatProtEx(void)
{
    return (nutritions["fat"]*9 + nutritions["protein"]*4)/100;
}

float Food::getFat(void)
{
    return nutritions["fat"];
}
float Food::getCarbo(void)
{
    return nutritions["carbo"];
}
float Food::getProtein(void)
{
    return nutritions["protein"];
}
float Food::getFiber(void)
{
    return nutritions["fiber"];
}
const std::map <std::string, float> Food::getNutritionsMap() const
{
    return nutritions;
}
