//
//  Car.cpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#include "Car.h"

Car::Car(){}


Car::Car(std::string _vin, std::string _make, std::string _model, unsigned int _year, double _price){

    vin = _vin;
    make = _make;
    model = _model;
    year = _year;
    price = _price;
}
void Car::setVIN(std::string _vin){
    this->vin = _vin;
}
void Car::setMake(std::string _make){
    this->make = _make;
}
void Car::setModel(std::string _model){
    this->model = _model;
}
void Car::setYear(unsigned int _year){
    this->year = _year;
}
void Car::setPrice(double _price){
    this->price = _price;
}
std::string Car::getVIN(){
    return this->vin;
}
std::string Car::getMake(){
    return this->make;
}
std::string Car::getModel(){
    return this->model;
}
unsigned int Car::getYear(){
    return this->year;
}
double Car::getPrice(){
    return this->price;
}

std::ostream& operator << (std::ostream& out, Car tempcar){

    out << "Vin: " << tempcar.getVIN() << std::endl
        << "Make: " << tempcar.getMake() << std::endl
        << "Model: " << tempcar.getModel() << std::endl
        << "Year: " << tempcar.getYear() << std::endl
        << "Price: " << "$" << tempcar.getPrice() << std::endl;

    return out;
}

