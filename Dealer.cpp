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

/// @brief Dealer constructor
/// @param _name Name of dealer
/// @param _number Dealer number identifier
/// @param _numberOfCars Number of cars the dealer has in inventory
Dealer::Dealer(string _name, int _number, int _numberOfCars) {
    dealerName = std::move(_name);
    dealerNumber = _number;
    numberOfCars = _numberOfCars;
}


/// @brief defualt if user enters no data
Car::Car() {

    VIN = -1;
    make = "";
    model = "";
    year = -1;
    price = -1.0;
}

/// @brief  Currently unused car constructor
/// @param _vin Cars Vehicle Identification Number (VIN)
/// @param _make Cars Make
/// @param _model Cars Model
/// @param _year  Cars year
/// @param _price Cars Pric
Car::Car(int _vin, string _make, string _model, int _year, double _price) {
    VIN = std::to_string(_vin);
    make = std::move(_make);
    model = std::move(_model);
    year = _year;
    price = _price;
}

/// @brief overloaded operator
/// @param out ostream
/// @param dealer Dealer Vector
/// @return @param out
ostream &operator<<(ostream &out, const Dealer &dealer) {
    out << "Name: " << dealer.dealerName << "\nNumber: " << dealer.dealerNumber << endl;
    return out;
}

/// @brief Function to set Dealer name
/// @param name dealers name
void Dealer::setDealerName(string name) {
    { dealerName = std::move(name); }
}

void Dealer::setDealerNumber(int number) {
    { dealerNumber = number; }
}

void Dealer::setCarArrayPtr(Car *carAr) {
    int numCars = getNumberOfCars();
    carArrayPtr = new Car[numCars];
}

void Dealer::setNumberOfCars(int cars) {
    { numberOfCars = cars; }
}

string Dealer::getDealerName() {
    { return dealerName; }
}

int Dealer::getDealerNumber() {
    { return dealerNumber; }
}

Car *Dealer::getCarArrayPtr() {
    { return carArrayPtr; }
}

int Dealer::getNumberOfCars() {
    { return numberOfCars; }
}

Dealer::Dealer() = default;

ostream& operator<<(ostream& os, const Car& car){
    os << "VIN: " << car.VIN << "\nMake: " << car.make << "\nModel: " << car.model << "\nYear: " << car.year << "\nPrice: " << car.price;
    return os;
}

void Car::setVIN(string _VIN) {
    { VIN = std::move(_VIN); }
}

void Car::setMake(string _make) {
    { make = std::move(_make); }
}

void Car::setModel(string _model) {
    { model = std::move(_model); }
}

void Car::setYear(int _year) {
    { year = _year; }
}

void Car::setPrice(double _price) {
    { price = _price; }
}

string Car::getVIN() {
    { return VIN; }
}

string Car::getMake() {
    { return make; }
}

string Car::getModel() {
    { return model; }
}

int Car::getYear() {
    { return year; }
}

double Car::getPrice() {
    { return price; }
}

