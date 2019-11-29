//
//  main.cpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//
//  CSCI 1410-003
//  Status: Compiles and runs on cLion
//  Notes: No error checking in place
//
#include "SystemFunctions.h"
#include <iostream>

/// @brief main function compilation begins and ends here
/// @return implied zero
int main() {
    int userChoice;
    std::ifstream infile;
    std::ofstream outfile;
    std::vector<Dealer> inventory;

    do {
        printMenu();
        std::cin >> userChoice;

        switch (userChoice) {
            case 1:
                readFromFile(infile, inventory);
                //Adds output buffer to make it more readable.
                std::cout << std::endl;
                break;
            case 2:
                displayDealers(inventory);
                break;
            case 3:
                displayCarsFromDealer(inventory);
                break;
            case 4:
                addCarToDealer(inventory);
                break;
            case 5:
                listAndModifyCar(inventory);
                break;
            case 6:
                sortCarsFromDealer(inventory);
                break;
            case 7:
                writeDealersCarsToFile(outfile, inventory);
                break;
            case 0:
                exitProgram();
                break;
            default:
                unknownInput();
                break;
        }

    } while (userChoice != 0);

    exitProgram();
}

