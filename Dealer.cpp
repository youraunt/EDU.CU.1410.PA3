//
//  Dealer.cpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#include "Dealer.h"
#include <iostream>

Dealer::Dealer()= default;

Dealer::Dealer(std::string _dealerName, unsigned int _dealerNumber, unsigned int _numberOfCars){
    dealerName = _dealerName;
    dealerNumber = _dealerNumber;
    numberOfCars = _numberOfCars;

}

void Dealer::setDealerName(std::string _dealerName){
    this->dealerName = _dealerName;
}

void Dealer::setDealerNumber(unsigned int _dealerNumber){
    this->dealerNumber = _dealerNumber;
}
void Dealer::setNumberOfCars(unsigned int _numberOfCars) {
    this->numberOfCars = _numberOfCars;
}

std::string Dealer::getDealerName(){
    return this->dealerName;
}

unsigned int Dealer::getDealerNumber(){
    return this->dealerNumber;
}
unsigned int Dealer::getNumberOfCars(){
    return  this->numberOfCars;
}

std::ostream& operator << (std::ostream& out, Dealer tempDealer){
    out << "Dealer Name: " << tempDealer.getDealerName() << std::endl;
    return out;
}



