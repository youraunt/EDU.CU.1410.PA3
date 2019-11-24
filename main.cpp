//
//  main.cpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//
#include "SystemFunctions.h"
#include <iostream>


int main() {
    //Declare a vector to hold our inventory
    std::vector<Car> inventory;
    Car *carArrayPtr = nullptr;
    while (true){
        if(!displayUserInterface(inventory, carArrayPtr)) break;
    }
    exitProgram();
}/// main


