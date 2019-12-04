//
//  SystemFunctions.hpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#ifndef SystemFunctions_h
#define SystemFunctions_h

#include <iostream>
#include <vector>
#include <fstream>
#include "Dealer.h"


/// @brief Handles unusable input
void inline unknownInput() {
    std::cout << "Error?! Please, try again: " << std::endl;
    std::cout << " >";
}

/// @brief Exits program successfully with message
std::string inline exitProgram() {
    std::cout << "Exiting program!" << std::endl;
    exit(EXIT_SUCCESS);
}

/// @brief Displays error and exits program
[[noreturn]]void inline fileNotFound() {
    std::cerr << "File not found! \nExiting Program!" << std::endl;
    exit(EXIT_FAILURE);
}

bool inline carsInInventory(std::vector<Dealer> &inventory
) {
    if (inventory.empty()) {
        std::cout << "\nThere are no cars in the inventory.\n";
        std::cout << "\nEither ";
        std::cout << "\n\t2. Add a Car";
        std::cout << "\n\t7. Read from file\n";
    }
    return !inventory.empty();
}

int inline getMenuChoice(int numChoices, bool hasSubmenu = false) {
    int choice; // Holds user's choice

    // Keep asking until a valid choice is made
    do {
        std::cout << "\n> ";
        std::cin >> choice;
        std::cin.ignore();

        // Valid choices range from 1 to numChoices
        if (choice < 0 || choice > numChoices) {
            std::cout << std::endl << choice << " is not a valid menu choice."
                      << "\nPlease make a selection between 1 and " << numChoices << std::endl;
            std::cout << " >";
        }

    } while (choice < 0 || choice > numChoices);

    return choice;
}

static const char menu_title[] =
        "\n"
        "------------------------------\n"
        "         Main Menu\n"
        "------------------------------\n"
        "\n";

/// @brief Function to read in from file
/// @param infile file stream
/// @param inventory Dealer Vector to read into
///@TODO integrate BOOST serialization
void inline readFromFile(std::ifstream &infile, std::vector<Dealer> &inventory) {

    std::cout << "Reading...";
    int dealer_number;
    int dealer_num_cars;
    int car_year;
    double car_price;
    std::string dealer_name;
    std::string car_make;
    std::string car_model;
    std::string car_vin;

    infile.open("/Users/bkallen/Desktop/CU Fall 2019/cFundiesPA3Outlines/dealers.txt");
    if (!infile || infile.fail()) { fileNotFound(); }

    while (infile.peek() != EOF) {
        int count = 0;

        Dealer dealer_in;

        std::getline(infile, dealer_name);
        //This is a protection against program thinking the blank line at the end of text files is a new dealer.
        if (dealer_name.empty()) {
            break;
        }
        dealer_in.setDealerName(dealer_name);
        infile >> dealer_number;
        dealer_in.setDealerNumber(dealer_number);
        infile >> dealer_num_cars;
        dealer_in.setNumberOfCars(dealer_num_cars);

        //Creates a pointer carArrayPtr of type "Car"
        Car *carArrayPtr = nullptr;
        //Sets the "CarArrayPtr" in the "Dealer" class to the dynamic pointer.
        //This function then dynamically creates an array of type "Car" and of size "number of cars".
        dealer_in.setCarArrayPtr(carArrayPtr);

        carArrayPtr = dealer_in.getCarArrayPtr();

        //Since the next input getter is "cin" the input needs to ignore the next "\0" to use "cin" after "getline"
        infile.ignore();
        while (count < dealer_in.getNumberOfCars()) {
            //Reads the VIN string from file in and set the car at index "count" VIN to the read vin.
            getline(infile, car_vin);
            carArrayPtr[count].setVIN(car_vin);

            getline(infile, car_make);
            carArrayPtr[count].setMake(car_make);

            getline(infile, car_model);
            carArrayPtr[count].setModel(car_model);

            infile >> car_year;
            carArrayPtr[count].setYear(car_year);

            infile >> car_price;
            carArrayPtr[count].setPrice(car_price);

            infile.ignore();

            count++;
        }

        //Adds the new dealer, "dealer_in", to the overall vector of "Dealers".
        inventory.push_back(dealer_in);
    }

    infile.close();
    std::cout << "Done." << std::endl;
}

/// @brief Function to display dealer by name, number and # of cars in inventory
/// @param inventory Vector to hold dealers
void inline displayDealers(std::vector<Dealer> &inventory) {
    for (const auto &i : inventory
            ) {
        std::cout << i << std::endl;
    }
}

/// @brief Function to list dealers and then display their inventory based on user input
/// @param inventory Vector to hold dealers
void inline displayCarsFromDealer(std::vector<Dealer> &inventory) {
    unsigned long userDealerInput = 0;
    unsigned long dealerIndex = 0;
    bool loopBool = true;
    displayDealers(inventory);
    std::cout << "From the choices above. Enter the dealer number to see cars: " << std::endl;
    std::cout << " >";
    //Checks user input against all the dealer numbers in the vector and sets "dealer_index" to the dealer found at the index.
    while (loopBool) {

        std::cin >> userDealerInput;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (userDealerInput == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) {
            std::cout << "No dealer found with that number. Try again: " << std::endl;
            std::cout << " >";
        }
    }

    Car *carArray = inventory.at(dealerIndex).getCarArrayPtr();

    std::cout << "\n" << inventory.at(dealerIndex).getDealerName() << "\n" << std::endl;
    for (int i = 0; i < inventory.at(dealerIndex).getNumberOfCars(); i++) {
        std::cout << carArray[i] << "\n" << std::endl;
    }
}

/// @brief Function displays dealers, then their inventory
/// then allows user to add a new car
/// @param inventory Vector to hold dealers
///@TODO implement loop to add multiple cars and/or option at once
void inline addCarToDealer(std::vector<Dealer> &inventory) {

    unsigned long input;
    unsigned long dealerIndex = 0;
    bool loopBool = true;
    std::string newVin;
    std::string newMake;
    std::string newModel;
    unsigned int newYear;
    double new_price;

    displayDealers(inventory);
    std::cout << "From the choices above. Enter the dealer number to add a new car: " << std::endl;
    std::cout << " >";
    while (loopBool) {

        std::cin >> input;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (input == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) {
            std::cout << "No dealer found with that number. Try again: " << std::endl;
            std::cout << " >";
        }
    }

    Dealer currentDealer = inventory.at(dealerIndex);

    std::cin.ignore();
    std::cout << "Enter new car VIN: " << std::endl;
    std::cout << " >";
    std::getline(std::cin, newVin);

    std::cout << "Enter new car make: " << std::endl;
    std::cout << " >";
    std::getline(std::cin, newMake);

    std::cout << "Enter new car model: " << std::endl;
    std::cout << " >";
    std::getline(std::cin, newModel);

    std::cout << "Enter new car year: " << std::endl;
    std::cout << " >";
    std::cin >> newYear;

    std::cout << "Enter new car price: " << std::endl;
    std::cout << " >";
    std::cin >> new_price;

    std::cout << "\nAdding...";

    Car *carArray = currentDealer.getCarArrayPtr();
    Car tempCars[currentDealer.getNumberOfCars()];

    //Populates the temporary array of cars with the existing cars in carArray. This is done so the memory can be freed up.
    for (int i = 0; i < currentDealer.getNumberOfCars(); i++) {
        tempCars[i] = carArray[i];
    }


    //Adds one to the number of cars in the dealers inventory in order to make room for new user car
    int tempNumCars = currentDealer.getNumberOfCars();
    currentDealer.setNumberOfCars(tempNumCars + 1);

    //Creates new Car object pointing to the array created in setCarArrayPtr.
    Car *newCarArr = nullptr;
    currentDealer.setCarArrayPtr(newCarArr);

    newCarArr = currentDealer.getCarArrayPtr();

    currentDealer.getNumberOfCars();

    // new_car_arr = car_array;
    for (int i = 0; i < currentDealer.getNumberOfCars() - 1; i++) {
        newCarArr[i] = tempCars[i];
    }

    newCarArr[currentDealer.getNumberOfCars() - 1].setVIN(newVin);
    newCarArr[currentDealer.getNumberOfCars() - 1].setMake(newMake);
    newCarArr[currentDealer.getNumberOfCars() - 1].setModel(newModel);
    newCarArr[currentDealer.getNumberOfCars() - 1].setYear(newYear);
    newCarArr[currentDealer.getNumberOfCars() - 1].setPrice(new_price);

    inventory.at(dealerIndex) = currentDealer;

    std::cout << "Done." << std::endl;
}

/// @brief Function displays dealers, then their inventory
/// then allows user to modify any aspect of the car selected
/// @param inventory Vector to hold dealers
///@TODO implement loop to modify multiple cars and/or option at once
void inline listAndModifyCar(std::vector<Dealer> &inventory) {

    if (carsInInventory(inventory)) {
        int choice = -1;
        int choice1;
        int numberOfCars = 0;

        unsigned long userDealerInput = 0;
        unsigned long dealerIndex = 0;

        bool loopBool = true;
        displayDealers(inventory);
        std::cout << "From the choices above. Enter the dealer number to see cars: " << std::endl;
        std::cout << " >";
        //Checks user input against all the dealer numbers in the vector and sets "dealerIndex" to the dealer found at the index.
        while (loopBool) {
            std::cin >> userDealerInput;

            for (unsigned long i = 0; i < inventory
                    .size(); i++) {
                if (userDealerInput == inventory
                        .at(i).getDealerNumber()) {
                    dealerIndex = i;
                    loopBool = false;
                }
            }
            if (loopBool) {
                std::cout << "No dealer found with that number. Try again: " << std::endl;
                std::cout << " >";
            }
        }

        Car *carArray = inventory
                .at(dealerIndex).getCarArrayPtr();

        std::cout << "\n" << inventory
                .at(dealerIndex).getDealerName() << "\n" << std::endl;
        for (int i = 0; i < inventory
                .at(dealerIndex).getNumberOfCars(); i++) {
            std::cout << "CAR # " << i + 1 << std::endl
                      << carArray[i] << "\n" << std::endl;
            numberOfCars++;
        }
        std::cout << "\nPlease enter the number of the car you would like to modify:" << std::endl;
//        getMenuChoice(choice);
        std::cin >> choice;
        std::cout << "You picked:  " << carArray[choice - 1].getYear() << " "
                  << carArray[choice - 1].getMake() << " "
                  << carArray[choice - 1].getModel() << std::endl
                  << "Which aspect would you like to update? " << std::endl
                  << "\t1.\tVIN" << std::endl
                  << "\t2.\tMAKE" << std::endl
                  << "\t3.\tMODEL" << std::endl
                  << "\t4.\tYEAR" << std::endl
                  << "\t5.\tPRICE" << std::endl;
//        getMenuChoice(choice1);
        std::cin >> choice1;
        switch (choice1) {
            case 1: {
                std::string newVIN;
                std::cout << "Please enter new VIN: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::getline(std::cin, newVIN);
                carArray[choice - 1].setVIN(newVIN);
                break;
            }
            case 2: {
                std::string newMake;
                std::cout << "Please enter new make: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::getline(std::cin, newMake);
                carArray[choice - 1].setMake(newMake);
            }
                break;
            case 3: {
                std::string newModel;
                std::cout << "Please enter new model: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::getline(std::cin, newModel);
                carArray[choice - 1].setModel(newModel);
            }
                break;
            case 4: {
                int newYear;
                std::cout << "Please enter new year: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::cin >> newYear;
                carArray[choice - 1].setYear(newYear);
            }
                break;
            case 5: {
                double newPrice;
                std::cout << "Please enter new price: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::cin >> newPrice;
                carArray[choice - 1].setPrice(newPrice);
            }
                break;
            default:
                unknownInput();

        }


    }
}

/// @brief Function bubble sorts cars vin
/// @param inventory Vector to hold dealers
void inline sortCarsFromDealer(std::vector<Dealer> &inventory) {
    unsigned long userDealerInput = 0;
    unsigned long dealerIndex = 0;
    bool loopBool = true;

    displayDealers(inventory
    );
    std::cout << "From the choices above. Enter the dealer number to add a new car: " << std::endl;
    std::cout << " >";

    while (loopBool) {

        std::cin >> userDealerInput;

        for (unsigned long i = 0; i < inventory
                .size(); i++) {
            if (userDealerInput == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) {
            std::cout << "No dealer found with that number. Try again: " << std::endl;
            std::cout << " >";
        }
    }
    //Adds output buffer to make it more readable.
    std::cout << std::endl;

    Car *carArray = inventory.at(dealerIndex).getCarArrayPtr();

    Car swap;
    int n = inventory.at(dealerIndex).getNumberOfCars();

    //Using bubble sort
    for (unsigned int i = 0; i < n - 1; i++) {
        for (unsigned int j = 0; j < n - i - 1; j++) {
            if (carArray[j].getVIN() > carArray[j + 1].getVIN()) {
                swap = carArray[j];
                carArray[j] = carArray[j + 1];
                carArray[j + 1] = swap;
            }
        }
    }

    for (int k = 0; k < inventory.at(dealerIndex).getNumberOfCars(); k++) {
        std::cout << carArray[k] << "\n" << std::endl;
    }
}

/// @brief Function to export data to file
/// @param outfile
/// @param inventory Vector to hold dealers
///@TODO integrate BOOST serialization
void inline writeDealersCarsToFile(std::ofstream &outfile, std::vector<Dealer> &inventory) {
    std::cout << "Writing to outfile...";
    outfile.open("../outfile.txt");

    //Creates instance of pointing to class Car called carOut.
    Car *carOut = nullptr;

    for (auto &i : inventory
            ) {
        //Sets carOut pointer to the Car array inside of the current Dealer.
        carOut = i.getCarArrayPtr();

        outfile << i.getDealerName() << std::endl
                << i.getDealerNumber() << std::endl
                << i.getNumberOfCars() << std::endl;
        for (int j = 0; j < i.getNumberOfCars(); j++) {
            outfile << carOut[j].getVIN() << std::endl
                    << carOut[j].getMake() << std::endl
                    << carOut[j].getModel() << std::endl
                    << carOut[j].getYear() << std::endl
                    << carOut[j].getPrice() << std::endl;
        }

    }
    outfile.close();
    std::cout << "Done." << std::endl;
}

/// @brief Function for user facing menu
/// @return true unless specified false by user
bool inline printMenu() {
    std::cout << menu_title << std::endl
              << "1.\tRead Dealers and Cars from file." << std::endl
              << "2.\tDisplay Dealers." << std::endl
              << "3.\tChoose a Dealer Number, Display Cars." << std::endl
              << "4.\tChoose a Dealer Number, Add Car." << std::endl
              << "5.\tChoose a Dealer Number, List Cars and Modify a Car" << std::endl
              << "6.\tChoose a Dealer, Sort cars by VIN." << std::endl
              << "7.\tWrite Dealers and Cars to file." << std::endl
              << "0.\tExit" << std::endl
              << "Please enter a number corresponding to the menu: ";
//    std::cout << " >";
    return true;
}

#endif /* SystemFunctions_h */
