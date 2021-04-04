//
//  Food.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef Food_hpp
#define Food_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <iterator>
#include <string>
#include <QMessageBox>

class Food {
private:
    std::map<std::string, float> nutritions;
    friend class Dish;
    friend class Meal;
public:
    
    /*------constructors------*/
    
    Food(float protein, float fat, float carbo, float dietFiber);
    
    /*------methods------*/
    
    float getCarboEx(void);
    float getFatProtEx(void);
    float getProtein(void);
    float getFat(void);
    float getCarbo(void);
    float getFiber(void);
    const std::map<std::string, float> getNutritionsMap() const;
};

#endif /* Food_hpp */
