//
//  Dealer.hpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#ifndef Dealer_hpp
#define Dealer_hpp

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
    void setVIN(string _VIN);

    void setMake(string _make);

    void setModel(string _model);

    void setYear(int _year);

    void setPrice(double _price);
    //getters
    string getVIN();

    string getMake();

    string getModel();

    int getYear();

    double getPrice();
    //<< override
    friend ostream& operator<<(ostream& os, const Car& car);

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
    void setDealerName(string n);

    void setDealerNumber(int num);
    void setCarArrayPtr(Car* carPtr);

    void setNumberOfCars(int cars);
    //getters
    string getDealerName();

    int getDealerNumber();

    Car *getCarArrayPtr();

    int getNumberOfCars();
    //<< override
    friend ostream & operator << (ostream &out, const Dealer& dr);
};
#endif /// dealer.hpp
