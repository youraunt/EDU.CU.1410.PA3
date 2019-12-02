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



class Car{
private:
    std::string VIN;
    std::string make;
    std::string model;
    int year;
    double price;

public:
    //default constructor
    Car();
    //custom constructor
//    Car(int, std::string, std::string, int, double);
    //setters
    void setVIN(std::string _VIN) { VIN = std::move(_VIN); }

    void setMake(std::string _make) { make = std::move(_make); }

    void setModel(std::string _model) { model = std::move(_model); }

    void setYear(int _year) { year = _year; }

    void setPrice(double _price) { price = _price; }
    //getters
    std::string getVIN() { return VIN; }

    std::string getMake() { return make; }

    std::string getModel() { return model; }

    int getYear() { return year; }

    double getPrice() { return price; }
    //<< override
    friend std::ostream &operator<<(std::ostream &out, const Car &car);

};

class Dealer{
private:
    std::string dealerName;
    int dealerNumber;
    Car* carArrayPtr = nullptr;
    int numberOfCars;

public:
    //default contstructor
    Dealer();
    //custom contstructor
    Dealer(std::string, int, int);
    //setters
    void setDealerName(std::string n) { dealerName = std::move(n); }

    void setDealerNumber(int num) { dealerNumber = num; }
    void setCarArrayPtr(Car* carPtr);

    void setNumberOfCars(int cars) { numberOfCars = cars; }
    //getters
    std::string getDealerName() { return dealerName; }

    int getDealerNumber() { return dealerNumber; }

    Car *getCarArrayPtr() { return carArrayPtr; }

    int getNumberOfCars() { return numberOfCars; }
    //<< override
    friend std::ostream &operator<<(std::ostream &out, const Dealer &dr);
};
#endif /// dealer.hpp
