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


/// @brief default constructor with default values
Dealer::Dealer()  {
    dealerName = "";
    dealerNumber = -1;
    numberOfCars = 0;

}
/// @brief Constructor
/// @param _name name of dealer
/// @param _dealerNumber Dealer identification number
/// @param _numberOfCars Number of cars dealer has in inventory
Dealer::Dealer(std::string _name, int _dealerNumber, int _numberOfCars) {
    dealerName = std::move(_name);
    dealerNumber = _dealerNumber;
    numberOfCars = _numberOfCars;
}
/// @brief
/// @param carAr
void Dealer::setCarArrayPtr(Car*) {
    int numCars = getNumberOfCars();
    /// @brief Implicit conversion changes signed-ness: int to unsigned long
    /// No affect on program.
    carArrayPtr = new Car[numCars];
}
/// @brief Car constructor
/// Default values in case user does not input all fields.
/// Prevents from returning garbage.
Car::Car() {
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
std::ostream &operator<<(std::ostream &out, const Car &car) {
    out << "VIN: " << car.VIN << std::endl
        << "Make: " << car.make << std::endl
        << "Model: " << car.model << std::endl
        << "Year: " << car.year << std::endl
        << "Price: " << car.price << std::endl;
    return out;
}

/// @brief destructor
Car::~Car() = default;

