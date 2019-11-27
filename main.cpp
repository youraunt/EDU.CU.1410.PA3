//
//  main.cpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//
#include "SystemFunctions.h"
#include <iostream>


int main() {
    int userChoice;
    std::ifstream infile;
    std::ofstream outfile;

    std::vector<Dealer> inventory;



    do {
        printMenu();
        std::cin >> userChoice;

        //Adds output buffer to make it more readable.
        std::cout << std::endl;

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
                std::cout << "Thank you for visiting!\n" << std::endl;
                break;
            default:
                unknownInput();
                break;
        }

    } while (userChoice != 0);

    exitProgram();
}

