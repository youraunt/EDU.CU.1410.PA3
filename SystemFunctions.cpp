//
//  SystemFunctions.cpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#include "SystemFunctions.h"
#include "Dealer.h"
#include <iostream>
#include <fstream>
/// macro to debug #x list variable name and x list contents
#define WHAT_IS(x) std::cerr << #x << " is " << x << std::endl;


bool displayUserInterface(std::vector<Car> &inventory, Car *carArrayPtr){

    std::cout << "\t~~~~~~~ Menu ~~~~~~~"<< std::endl
              << "1. Read Dealers and Cars from file." << std::endl
              <<  "2. Display Dealers." << std::endl
              << "3. Choose a Dealer Number, Display Cars." << std::endl
              << "4. Choose a Dealer Number, Add Car." << std::endl
              << "5. Choose a Dealer, Sort Cars by VIN." << std::endl
              << "6. Write Dealers and Cars to file." << std::endl
              << "7. Exit." << std::endl
              << "Enter your choice: " << std::endl;

    int choice;
    std::cin >> choice;
    //@TODO why is this a narrowing conversion from int to signed type char??
    //  figure it out

    switch(choice){
        case 1:
            readInDealer(inventory, carArrayPtr);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            return false;
        default:
            unknownInput();
    }
    return false;
}

/// @brief Handles unusable input
void unknownInput() {
    std::cout << "Error?! Please, try again: " << std::endl;
}

/// @brief Exits program succesfully with message
std::string exitProgram() {
    std::cout << "Exiting program!" << std::endl;
    exit(EXIT_SUCCESS);
}
/// @brief Displays error and exits program
void fileNotFound() {
    std::cerr << "File not found! \nExiting Program!" << std::endl;
    exit(EXIT_FAILURE);
}

void readInDealer(std::vector <Car> &inventory, Car *carArrayPtr) {
    std::ifstream infile;
    infile.open("/Users/bkallen/Desktop/CU Fall 2019/cFundiesPA3Outlines/dealers.txt");
    if (!infile || infile.fail()) { fileNotFound(); }
    Dealer tempDealer;
    Car tempCar;
    while(infile.peek()!=EOF){
        std::string dealerName;
        std::string tempVin;
        std::string tempMake;
        std::string tempModel;
        unsigned int dealerNumber;
        unsigned int numberOfCars;
        unsigned int tempYear;
        double tempPrice;
        Car *carPtr;

        getline(infile, dealerName);
        infile >> dealerNumber;
        infile >> numberOfCars;
        infile.ignore();
        tempDealer.setDealerName(dealerName);
        tempDealer.setDealerNumber(dealerNumber);
        tempDealer.setNumberOfCars(numberOfCars);

        carPtr = new Car[numberOfCars];

        for (unsigned int i = 0 ; i < numberOfCars; ++i) {
            getline(infile, tempVin);
            getline(infile, tempMake);
            getline(infile,tempModel);
            infile >> tempYear;
            infile >> tempPrice;
            infile.ignore();

            tempCar.setVIN(tempVin);
            tempCar.setMake(tempMake);
            tempCar.setModel(tempModel);
            tempCar.setYear(tempYear);
            tempCar.setPrice(tempPrice);

            carPtr[i] = tempCar;

        }
        inventory.push_back(tempCar);
    }
    std::cout << "Responses successfully uploaded!" << std::endl;


}
