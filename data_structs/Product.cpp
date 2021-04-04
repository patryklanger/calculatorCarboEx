//
//  Product.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#include "headers/Product.hpp"
#include "../global_obj.hpp"


/*------constructors------*/


Product::Product(
                 float protein,
                 float fat,
                 float carbo,
                 float dietFiber,
                 std::string productName,
                 bool update,
                 float weight) : Food(
                                      floorf(protein*100)/weight,
                                      floorf(fat*100)/weight,
                                      floorf(carbo*100)/weight,
                                          floorf(dietFiber*100)/weight), poster("https://carbonex-46f1e-default-rtdb.firebaseio.com/products.json")
{
    try
    {
        auto nutritions = this->getNutritionsMap();
        this->productName = productName;
        if(!update) return;
        if(nutritions["protein"] < 0 ||
           nutritions["fat"] < 0 ||
           nutritions["carbo"] < 0 ||
           nutritions["fiber"] < 0 ) throw std::runtime_error("Unable to create Product object corectlly");
        auto productsSet = starterGlobalObj.globalProductsObj.getProductsSet();
        if(checkIfIsPresentInSet(productsSet)) return;
        poster.setJsonData(this->productToJson()).post();
        starterGlobalObj.globalProductsObj.deleteIfExist(*this);
        starterGlobalObj.globalProductsObj.pushBackProduct(*this);
    } catch (std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
    }
}

Product::Product(
                 float protein,
                 float fat,
                 float carbo,
                 float dietFiber,
                 std::string productName,
                 std::string url) : Food(
                                         floorf(protein*100)/100,
                                         floorf(fat*100)/100,
                                         floorf(carbo*100)/100,
                                         floorf(dietFiber*100)/100), poster(url)
{
    this->productName = productName;
}


/*------methods------*/

void Product::deleteProduct ()
{
    std::stringstream url;
    url << "https://carbonex-46f1e-default-rtdb.firebaseio.com/products/" << getPoster().encodeUrl(getProductName()) << ".json";
    Poster *tempPoster = new Poster(url.str(), "DELETE");
    tempPoster->post();
    starterGlobalObj.globalProductsObj.deleteIfExist(*this);
    delete tempPoster;
}

float Product::getCarboExPer(float grams)
{
    return getCarboEx()/100*grams;
}
float Product::getFatProtExPer(float grams)
{
    return getFatProtEx()/100*grams;
}
std::string Product::getProductName(void) const
{
    return productName;
}

bool Product::operator==(const Product& element) const
{
    auto pred = [] (
                    decltype(*this->getNutritionsMap().begin()) a, decltype(*this->getNutritionsMap().begin()) b)
    {
        return a.first == b.first && a.second == b.second;
    };
    auto nutritionMap1 = this->getNutritionsMap();
    auto nutritionMap2 = element.getNutritionsMap();
    
    
    return this->getProductName() == element.getProductName() && this->getNutritionsMap().size() == element.getNutritionsMap().size()
          && std::equal(nutritionMap1.begin(), nutritionMap1.end(), nutritionMap2.begin(), pred);
    
}
bool Product::operator > (const Product& element) const
{
    if (this->productName.compare(element.productName) < 0) return true;
    return false;
}
bool Product::operator < (const Product& element) const
{
    if (this->productName.compare(element.productName) > 0) return true;
    return false;
}

bool Product::checkIfIsPresentInSet(std::set<Product> productsSet)
{
    for (auto product : productsSet)
    {
        if (product == (*this)) return true;
    }
    return false;
}

Poster Product::getPoster()
{
    return poster;
}

Json::Value Product::productToJson() {
    Json::Value returningJsonFile;
    Json::Value tempJsonFile;
    
    returningJsonFile["carbo"] = this->getCarbo();
    returningJsonFile["fat"] = this->getFat();
    returningJsonFile["protein"] = this->getProtein();
    returningJsonFile["fiber"] = this->getFiber();


    tempJsonFile[this->getProductName()] = returningJsonFile;

    
    returningJsonFile = tempJsonFile;
    
    return returningJsonFile;
}



