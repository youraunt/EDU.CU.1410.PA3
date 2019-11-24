//
//  Dealer.hpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#ifndef Dealer_hpp
#define Dealer_hpp

#include <iostream>

class Dealer{
private:
    std::string dealerName;
    unsigned int dealerNumber{};
    unsigned int numberOfCars{};


public:
    Dealer();
    Dealer(std::string _dealerName, unsigned int _dealerNumber, unsigned int _numberOfCars);
    void setDealerName(std::string _dealerName);
    void setDealerNumber(unsigned int _dealerNumber);
    void setNumberOfCars(unsigned int _numberOfCars);
    std::string getDealerName();
    unsigned int getDealerNumber();
    unsigned int getNumberOfCars();
    friend std::ostream& operator << (std::ostream& out, Dealer _dealer);

};
#endif /// dealer.hpp
