//
//  Dealer.cpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#include "Dealer.h"
#include <iostream>
#include <utility>

/// @brief
Dealer::Dealer() {
    dealerName = "";
    dealerNumber = -1;
    numberOfCars = 0;

}
/// @brief Constructor
/// @param _name name of dealer
/// @param _number Dealer identification number
/// @param _numcars Number of cars dealer has in inventory
Dealer::Dealer(std::string _name, int _number, int _numcars) {
    dealerName = std::move(_name);
    dealerNumber = _number;
    numberOfCars = _numcars;
}
/// @brief
/// @param carAr
void Dealer::setCarArrayPtr(Car *carAr) {
    int numCars = getNumberOfCars();
    carArrayPtr = new Car[numCars];
}
/// @brief Car constructor
Car::Car() {
    //This is so if the use does want to add a car to dealer but doesnt input anything, it defaults.
    VIN = std::to_string(-1);
    make = "";
    model = "";
    year = -1;
    price = -1.0;
}

/// @brief Overloaded operator
/// @param out
/// @param dealer
/// @return @param out
std::ostream &operator<<(std::ostream &out, const Dealer &dealer) {
    out << "Name: " << dealer.dealerName << "\nNumber: " << dealer.dealerNumber << std::endl;
    return out;
}
/// @brief destructor
Dealer::~Dealer() = default;
/// @brief Overloaded operator
/// @param basicOstream
/// @param car
/// @return @param basicOstream
std::ostream &operator<<(std::ostream &basicOstream, const Car &car) {
    basicOstream << "VIN: " << car.VIN << "\nMake: " << car.make << "\nModel: " << car.model << "\nYear: " << car.year
                 << "\nPrice: " << car.price;
    return basicOstream;
}
/// @brief
Car::~Car() = default;

