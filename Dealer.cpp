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


Dealer::Dealer() {
    dealerName = "";
    dealerNumber = -1;
    numberOfCars = 0;

}

Dealer::Dealer(std::string _name, int _number, int _numcars) {
    dealerName = std::move(_name);
    dealerNumber = _number;
    numberOfCars = _numcars;
}

void Dealer::setCarArrayPtr(Car *carAr) {
    int numCars = getNumberOfCars();
    carArrayPtr = new Car[numCars];
}



Car::Car() {
    //This is so if the use does want to add a car to dealer but doesnt input anything, it defaults.
    VIN = std::to_string(-1);
    make = "";
    model = "";
    year = -1;
    price = -1.0;
}

/*Car::Car(int _v, string _ma, string _mo, int _yr, double _pr) {
    VIN = _v;
    make = _ma;
    model = _mo;
    year = _yr;
    price = _pr;
}*/

std::ostream &operator<<(std::ostream &out, const Dealer &dealer) {
    out << "Name: " << dealer.dealerName << "\nNumber: " << dealer.dealerNumber << std::endl;
    return out;
}

Dealer::~Dealer() = default;

std::ostream& operator<<(std::ostream& basicOstream, const Car& car){
    basicOstream << "VIN: " << car.VIN << "\nMake: " << car.make << "\nModel: " << car.model << "\nYear: " << car.year << "\nPrice: " << car.price;
    return basicOstream;
}

Car::~Car() = default;

