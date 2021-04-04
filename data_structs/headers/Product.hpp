//
//  Product.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef Product_hpp
#define Product_hpp

#include <stdio.h>
#include <json/json.h>
#include <math.h>
#include <iterator>
#include <set>
#include "Food.hpp"
#include "../../networking/headers/Poster.hpp"
//#include "../../global_obj.hpp"

class Product : public Food {
private:
    std::string productName;
    Poster poster;
public:
    
    /*------constructors------*/

    Product(
            float protein,
            float fat,
            float carbo,
            float dietFiber,
            std::string productName = "Product",
            bool update = true,
            float weight = 100);
    
    Product(
            float protein,
            float fat,
            float carbo,
            float dietFiber,
            std::string productName,
            std::string url);
    
    
    /*------overloaded opeators------*/
    
    bool operator==(const Product& element) const;
    bool operator<(const Product& element) const;
    bool operator>(const Product& element) const;
    
   /*------methods------*/

    void deleteProduct ();
    
    float getCarboExPer(float grams);
    float getFatProtExPer(float grams);
    bool checkIfIsPresentInSet(std::set <Product> productsSet);
    std::string getProductName(void) const;
    Poster getPoster();
    Json::Value productToJson();
};

#endif /* Product_hpp */
