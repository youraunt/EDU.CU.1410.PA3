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
using namespace std;

Dealer::Dealer() {
    dealerName = "";
    dealerNumber = -1;
    numberOfCars = 0;

}
Dealer::Dealer(string _name, int _number, int _numcars) {
    dealerName = std::move(_name);
    dealerNumber = _number;
    numberOfCars = _numcars;
}

void Dealer::setCarArrayPtr(Car* carAr) {
    int numCars = getNumberOfCars();
    carArrayPtr = new Car[numCars];
}



Car::Car() {
    //This is so if the use does want to add a car to dealer but doesnt input anything, it defaults.
    VIN = -1;
    make = "";
    model = "";
    year = -1;
    price = -1.0;
}

Car::Car(int _v, string _ma, string _mo, int _yr, double _pr) {
    VIN = _v;
    make = _ma;
    model = _mo;
    year = _yr;
    price = _pr;
}

ostream & operator << (ostream &out, const Dealer& dr){
    out << "Name: " << dr.dealerName << "\nNumber: " << dr.dealerNumber << endl;
    return out;
}

ostream& operator<<(ostream& os, const Car& car){
    os << "VIN: " << car.VIN << "\nMake: " << car.make << "\nModel: " << car.model << "\nYear: " << car.year << "\nPrice: " << car.price;
    return os;
}

