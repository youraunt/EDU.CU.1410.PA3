///
///  main.cpp
///  PA3
///
///  CSCI-1411-003
///
///  Henok Ghebechristos
///
///  @author Created by BK Allen on 11/23/19.
///  Copyright © 2019 BK Allen. All rights reserved.
///
///  Status: Compiles and runs on cLion, xCode, QT Creator, Visual Studio, and CSE Grid
///
#include "SystemFunctions.h"
#include <iostream>
/// @macro for debugging
#define WHAT_IS(x) std::cerr << #x << " is " << (x) << std::endl;

///
/// @brief main This is the main method where compilation begins and ends
/// @return implied zero
///
int main() {
try {
    std::cin.exceptions(std::istream::failbit);
    int userChoice;
    std::ifstream infile;
    std::ofstream outfile;
    std::vector<Dealer> inventory;

    do {
        printMenu();
        userChoice = getMenuChoice(7);
        // std::cin >> userChoice;
        //for readability
        std::cout << std::endl;

        switch (userChoice) {
            case 1:
                readFromFile(infile, inventory);
                //for readability
                std::cout << std::endl;
                break;
            case 2:
                displayDealers(inventory);
                //for readability
                std::cout << std::endl;
                break;
            case 3:
                displayCarsFromDealer(inventory);
                //for readability
                std::cout << std::endl;
                break;
            case 4:
                addCarToDealer(inventory);
                //for readability
                std::cout << std::endl;
                break;
            case 5:
                listAndModifyCar(inventory);
                //for readability
                std::cout << std::endl;
                break;
            case 6:
                sortCars(inventory);
                //for readability
                std::cout << std::endl;
                break;
            case 7:
                writeDealersCarsToFile(outfile, inventory);
                //for readability
                std::cout << std::endl;
                break;
            case 0:
                std::cout << "Thank you for visiting!\n" << std::endl;
                break;
            default:
                unknownInput();
                //for readability
                std::cout << std::endl;
                break;
        }///#switch

    } while (userChoice != 0);

    exitProgram();
}catch (const std::exception&){
    unknownInput();
}///#catch
}///#main

