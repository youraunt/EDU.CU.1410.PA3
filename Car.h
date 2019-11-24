//
//  Car.hpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#ifndef Car_hpp
#define Car_hpp

#include <iostream>
#include "Dealer.h"

class Car{
private:
    std::string vin;
    std::string make;
    std::string model;
    unsigned int year;
    double price;

public:
    /// Public  pointer to cars dealer
    Car *carArrayPtr{};
    Car();
    Car(std::string _vin, std::string _make, std::string _model, unsigned int _year, double _price);
    void setVIN(std::string _vin);
    void setMake(std::string _make);
    void setModel(std::string _model);
    void setYear(unsigned int _year);
    void setPrice(double _price);
    std::string getVIN();
    std::string getMake();
    std::string getModel();
    unsigned int getYear();
    double getPrice();
    friend std::ostream& operator << (std::ostream& out, Car _car);
};

#endif /* Car_hpp */
