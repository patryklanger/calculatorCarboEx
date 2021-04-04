//
//  Dish.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#include "headers/Dish.hpp"
#include "../global_obj.hpp"


/*------constructors------*/

Dish::Dish(std::string productName) : Product(0,0,0,0 ,productName, std::string("https://carbonex-46f1e-default-rtdb.firebaseio.com/dishes.json")){}




std::string Dish::getDishName(void) const
{
    return getProductName();
}


std::set<Product> Dish::getProducts(void)
{
    return products;
}

/*------methods------*/

Product Dish::dishToProduct()
{
    Product product(this->getProtein(),this->getFat(),this->getCarbo(), this->getFiber(),this->getDishName(),this->getPoster().getUrl());
    return product;
}


bool Dish::operator==(const Dish& element) const
{
    auto vec1 = this->getProductsSet();
    auto vec2 = element.getProductsSet();
    if(this->getDishName().compare(element.getDishName())!=0) return false;
    if(vec1.size() != vec2.size()) return false;
    auto vec2it = vec2.begin();
    
    for(auto& product : vec1)
    {
        if (!(product == *vec2it)) return false;
        vec2it++;
    }
    return true;
}

bool Dish::operator<(const Dish& element) const
{
    if (this->getDishName().compare(element.getDishName()) > 0) return true;
    return false;
}

bool Dish::operator>(const Dish& element) const
{
    if(this->getDishName().compare(element.getDishName()) < 0) return true;
    return false;
}

bool Dish::checkIfIsPresentInSet(std::set <Dish> dishesSet)
{
    for (auto el : dishesSet) if (el == (*this)) return true;
    return false;
}

std::set<Product> Dish::getProductsSet(void) const
{
    return products;
}

void Dish::addProduct(
                      std::string name,
                      float protein,
                      float fat,
                      float carbo,
                      float dietFiber,
                      bool updateProduct)
{


    nutritions["protein"] += protein;
    nutritions["fat"] += fat;
    nutritions["carbo"] += carbo;
    nutritions["fiber"] += dietFiber;


    for(auto product : products)
    {
        if(!product.getProductName().compare(name))
        {
            auto newFat = product.getFat() + fat;
            auto newProtein = product.getProtein() + protein;
            auto newCarbo = product.getCarbo() + carbo;
            auto newFiber = product.getFiber() + dietFiber;
            auto temp = Product(newProtein,newFat,newCarbo,newFiber,name,false);
            deleteFromSetIfExist(product);
            products.insert(temp);
            return;
        }
    }
    auto temp = Product(protein, fat, carbo, dietFiber, name, updateProduct);
    products.insert(temp);
}

void Dish::deleteFromSetIfExist(Product product)
{
    for (auto prod : products)
    {
        if(!prod.getProductName().compare(product.getProductName()))
        {
            products.erase(prod);
            return;
        }
    }
}

void Dish::post()
{
    auto dishesSet = starterGlobalObj.globalDishesObj.getDishesSet();
    if(checkIfIsPresentInSet(dishesSet)) return;
    this->getPoster().setJsonData(this->dishToJson()).post();
    
    starterGlobalObj.globalDishesObj.deleteIfExist(*this);
    
    starterGlobalObj.globalDishesObj.pushBackDish(*this);
}


void Dish::deleteDish()
{
    std::stringstream url;
    url << "https://carbonex-46f1e-default-rtdb.firebaseio.com/dishes/" << getPoster().encodeUrl(getDishName()) << ".json";
    Poster *tempPoster = new Poster(url.str(), "DELETE");
    tempPoster->post();
    starterGlobalObj.globalDishesObj.deleteIfExist(*this);
    delete tempPoster;
}

Json::Value Dish::dishToJson()
{
    Json::Value returningJsonFile;
    Json::Value tempJsonFile;
    
    for (auto product : products)
    {
        returningJsonFile["carbo"] = product.getCarbo();
        returningJsonFile["fat"] = product.getFat();
        returningJsonFile["protein"] = product.getProtein();
        returningJsonFile["fiber"] = product.getFiber();
        tempJsonFile[product.getProductName()] = returningJsonFile;
    }
    
    returningJsonFile = tempJsonFile;
    tempJsonFile = Json::Value();
    tempJsonFile[this->getDishName()] = returningJsonFile;
    returningJsonFile = tempJsonFile;

    return returningJsonFile;
}





