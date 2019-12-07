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


class Car {
private:
    std::string VIN;
    std::string make;
    std::string model;
    int year;
    double price;

public:
    /// @brief Default constructor
    Car();
/// @brief Getters and setters
    inline void setVIN(std::string _VIN) { VIN = std::move(_VIN); }
    inline void setMake(std::string _make) { make = std::move(_make); }
    inline void setModel(std::string _model) { model = std::move(_model); }
    inline void setYear(int _year) { year = _year; }
    inline void setPrice(double _price) { price = _price; }
    inline std::string getVIN() { return VIN; }
    inline std::string getMake() { return make; }
    inline std::string getModel() { return model; }
    inline int getYear() { return year; }
    inline double getPrice() { return price; }
    /// @brief Overloaded operator
    /// @param out
    /// @param car
    /// @return
    friend std::ostream &operator<<(std::ostream &out, const Car &car);

    /// @brief  Default destructor
    ~Car();
};

class Dealer {
private:
    std::string dealerName;
    int dealerNumber;
    Car *carArrayPtr = nullptr;
    int numberOfCars;

public:
    /// @brief Default constructor
    Dealer();

    Dealer(std::string, int, int);

    inline void setDealerName(std::string n) { dealerName = std::move(n); }

    inline void setDealerNumber(int num) { dealerNumber = num; }

    void setCarArrayPtr(Car *);

    inline void setNumberOfCars(int cars) { numberOfCars = cars; }

    inline std::string getDealerName() { return dealerName; }

    inline int getDealerNumber() { return dealerNumber; }

    Car *getCarArrayPtr() { return carArrayPtr; }

    inline int getNumberOfCars() { return numberOfCars; }

    friend std::ostream &operator<<(std::ostream &out, const Dealer &dr);

    /// @brief Default destructor
    ~Dealer();
};

#endif /// dealer.h
