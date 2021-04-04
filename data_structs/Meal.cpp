//
//  Meal.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#include "headers/Meal.hpp"
#include "../global_obj.hpp"

/*------constructors------*/

Meal::Meal(std::string timestamp) : Food(0, 0, 0, 0), poster(std::string("https://carbonex-46f1e-default-rtdb.firebaseio.com/meals.json"))
{
    if(timestamp != "")
    {
        this->timestamp = timestamp;
        return;
    }
    std::cout << "New meal register" << std::endl;
    auto ms = std::chrono::duration_cast< std::chrono::seconds >
    (std::chrono::system_clock::now().time_since_epoch());
    this->timestamp = std::to_string(ms.count());
}



bool Meal::operator<(const Meal& element) const
{
    if (this->timestamp.compare(element.timestamp) > 0) return true;
    return false;
}
bool Meal::operator>(const Meal& element) const
{
    if(this->timestamp.compare(element.timestamp) < 0) return true;
    return false;
}
bool Meal::operator==(const Meal& element) const
{
    if(this->getTimestamp().compare(element.getTimestamp())!=0) return false;
    return true;
}

/*------methods------*/

std::string Meal::getTimestamp(void) const
{
    return timestamp;
}

void Meal::addToMap(Product prod)
{
    productsSet.insert(prod);
    
    this->nutritions["carbo"] += prod.getCarbo();
    this->nutritions["fat"] += prod.getFat();
    this->nutritions["protein"] += prod.getProtein();
    this->nutritions["fiber"] += prod.getFiber();
}


std::set<Product> Meal::getProductsSet(void) const
{
    return productsSet;
}

void Meal::addToMap(Dish dish)
{
    productsSet.insert(dish);
    
    this->nutritions["carbo"] += dish.getCarbo();
    this->nutritions["fat"] += dish.getFat();
    this->nutritions["protein"] += dish.getProtein();
    this->nutritions["fiber"] += dish.getFiber();
    
}

void Meal::post()
{
    this->getPoster().setJsonData(this->mealToJson()).post();
    starterGlobalObj.globalMealsObj.pushBackMeal(*this);
}

Json::Value Meal::mealToJson(void)
{
    Json::Value dishJson;
    Json::Value productJson;
    Json::Value returningJson;
    Json::Value tempJson;
    try
    {
        for (auto mapEl : productsSet)
        {
                tempJson["fat"] = mapEl.getFat();
                tempJson["carbo"] = mapEl.getCarbo();
                tempJson["protein"] = mapEl.getProtein();
                tempJson["fiber"] = mapEl.getFiber();
                productJson[mapEl.getProductName()] = tempJson;
                tempJson = Json::Value();
        }
        
        tempJson["dishes"] = dishJson;
        tempJson["products"] = productJson;
        returningJson[this->getTimestamp()] = tempJson;
        return returningJson;
    } catch (std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
        return Json::Value();
    }
}

Poster Meal::getPoster()
{
    return poster;
}

std::string Meal::getDate()
{
    auto timeVar = std::chrono::seconds(stoi(timestamp));
    auto timePoint = std::chrono::system_clock::time_point(timeVar);
    auto t_c = std::chrono::system_clock::to_time_t(timePoint);
    
    std::stringstream stream;
    stream << std::put_time(std::localtime(&t_c), "%e.%m.%Y %H:%M");
    auto date = stream.str();
    
    stream.str(std::string());
    stream << std::put_time(std::localtime(&t_c), "%H");
    auto hour = stream.str();
    int hourInt = stoi(hour);
    
    if((hourInt >= 0 && hourInt <= 5) || hourInt > 20) timeOfDay = std::string("W NOCY");
    else if (hourInt >= 6 && hourInt <= 12) timeOfDay = std::string("RANO");
    else if (hourInt > 12 && hourInt <= 18) timeOfDay = std::string("PO POPŁUDNIU");
    else if (hourInt > 18 && hourInt <= 20) timeOfDay = std::string("WIECZOREM");
    
    return date;
}

std::string Meal::getTimeOfDay()
{
    if(timeOfDay == std::string()) this->getDate();
    return timeOfDay;
}
