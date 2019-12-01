//
//  Dealer.h
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#ifndef Dealer_h
#define Dealer_h

#include <string>
#include <iostream>
#include <utility>

using namespace std;

class Car{
private:
    string VIN;
    string make;
    string model;
    int year;
    double price;

public:
    //default constructor
    Car();
    //custom constructor
    Car(int, string, string, int, double);
    //setters
    void setVIN(string _VIN) { VIN = std::move(_VIN); }

    void setMake(string _make) { make = std::move(_make); }

    void setModel(string _model) { model = std::move(_model); }

    void setYear(int _year) { year = _year; }

    void setPrice(double _price) { price = _price; }
    //getters
    string getVIN() { return VIN; }

    string getMake() { return make; }

    string getModel() { return model; }

    int getYear() { return year; }

    double getPrice() { return price; }
    //<< override
    friend ostream &operator<<(ostream &out, const Car &car);

};

class Dealer{
private:
    string dealerName;
    int dealerNumber;
    Car* carArrayPtr = nullptr;
    int numberOfCars;

public:
    //default contstructor
    Dealer();
    //custom contstructor
    Dealer(string, int, int);
    //setters
    void setDealerName(string n) { dealerName = std::move(n); }

    void setDealerNumber(int num) { dealerNumber = num; }
    void setCarArrayPtr(Car* carPtr);

    void setNumberOfCars(int cars) { numberOfCars = cars; }
    //getters
    string getDealerName() { return dealerName; }

    int getDealerNumber() { return dealerNumber; }

    Car *getCarArrayPtr() { return carArrayPtr; }

    int getNumberOfCars() { return numberOfCars; }
    //<< override
    friend ostream &operator<<(ostream &out, const Dealer &dr);
};
#endif /// dealer.hpp
