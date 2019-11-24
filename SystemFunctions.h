//
//  SystemFunctions.hpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#ifndef SystemFunctions_hpp
#define SystemFunctions_hpp

#include "Car.h"
#include <vector>

#define WHAT_IS(x) std::cerr << #x << " is " << x << std::endl;

bool displayUserInterface(std::vector<Car>& inventory, Car *carArrayPtr);

void readInDealer(std::vector<Car>& inventory, Car *carArrayPtr);
std::string exitProgram();
/// @brief helper
void unknownInput();


#endif /* SystemFunctions_hpp */
