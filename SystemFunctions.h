//
//  SystemFunctions.h
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
#include <zconf.h>
#include "Dealer.h"
#include <exception>


static const char MENU_TITLE[] =
        "\n\x1b[36m"
        "-----------------------------------\n"
        "|            Main Menu            |\n"
        "-----------------------------------\n"
        "\n\x1b[0m";


// @brief Function for user facing menu
/// @return true unless specified false by user
inline bool printMenu() {
    std::cout << MENU_TITLE

              << "\x1b[33m1.\tRead Dealers and Cars from file." << std::endl
              << "2.\tDisplay Dealers." << std::endl
              << "3.\tChoose a Dealer Number, Display Cars." << std::endl
              << "4.\tChoose a Dealer Number, Add Car." << std::endl
              << "5.\tChoose a Dealer Number, List Cars and Modify a Car" << std::endl
              << "6.\tChoose a Dealer, Sort cars by VIN." << std::endl
              << "7.\tWrite Dealers and Cars to file." << std::endl
              << "0.\tExit" << std::endl
              << "Please enter a number corresponding to the menu: \x1b[0m";
    return true;
}

/// @brief Exits program successfully with message
inline std::string exitProgram() {
    std::cout << "Exiting program!" << std::endl;
    /// @brief I used EXIT_SUCCESS here to unwind the stack
    exit(EXIT_SUCCESS);
}

/// @brief Handles unusable input
inline void unknownInput() {
    std::cerr << "\nError?! Unknown input.\n" << std::endl;
    sleep(1);
    exitProgram();

}


/// @brief Displays error and exits program
[[noreturn]] inline void fileNotFound() {
    std::cerr << "File not found!" << std::endl
              << "Exiting Program!" << std::endl;
    exit(EXIT_FAILURE);
}

inline bool carsInInventory(std::vector<Dealer> &inventory) {
    if (inventory.empty()) {
        printMenu();
        std::cout << "Inventory is empty." << std::endl
                  << "You can: " << std::endl
                  << "\t5. Add a Car" << std::endl
                  << "\t1. Read from file\n";
    }
    return !inventory.empty();
}

inline int getMenuChoice(int numChoices) {
    int choice = 0; // Holds user's choice

    // Keep asking until a valid choice is made
    do {

        std::cout << std::endl << "> ";


        std::cin.exceptions(std::istream::failbit);
        std::cin >> choice;
        std::cin.ignore();

        // Valid choices range from 0 to numChoices
        if (choice < 0 || choice > numChoices) {
            std::cout << "\n" << choice << " is not a valid menu choice."
                      << "\nPlease make a selection between 1 and " << numChoices << std::endl
                      << "0 to exit.";

        }

    } while (choice < 0 || choice > numChoices);

    return choice;
}

/// @brief Function to read in from file
/// @param infile file stream
/// @param inventory Dealer Vector to read into
///@TODO integrate BOOST serialization
inline void readFromFile(std::ifstream &infile, std::vector<Dealer> &inventory) {
    static bool called = false;
    if (called){
        std::cout << "File already read in!"<< std::endl;
        return;
    }
    called = true;
//    printMenu();
    std::cout << "Reading...";
    int dealerNumber;
    int numberOfCars;
    int carYear;
    double carPrice;
    std::string dealerName;
    std::string carMake;
    std::string carModel;
    std::string carVin;

    infile.open("/Users/bkallen/Desktop/CU Fall 2019/cFundiesPA3Outlines/dealers.txt");
    if (!infile || infile.fail()) { fileNotFound(); }

    while (infile.peek() != EOF) {
        int count = 0;

        Dealer dealer;

        std::getline(infile, dealerName);
        /// @brief To avoid reading blanks.
        if (dealerName.empty()) {
            break;
        }
        dealer.setDealerName(dealerName);
        infile >> dealerNumber;
        dealer.setDealerNumber(dealerNumber);
        infile >> numberOfCars;
        dealer.setNumberOfCars(numberOfCars);

        //Creates a pointer carArrayPtr of type Car
        Car *carArrayPtr = nullptr;

        /// @brief Sets the CarArrayPtr in the Dealer class to the dynamic pointer.
        //  @brief This function dynamically creates an array of type Car and of size numberOfCars.
        dealer.setCarArrayPtr(carArrayPtr);

        carArrayPtr = dealer.getCarArrayPtr();
        infile.ignore();
        while (count < dealer.getNumberOfCars()) {
            //Reads the VIN string from file in and set the car at index "count" VIN to the read vin.
            getline(infile, carVin);
            carArrayPtr[count].setVIN(carVin);

            getline(infile, carMake);
            carArrayPtr[count].setMake(carMake);

            getline(infile, carModel);
            carArrayPtr[count].setModel(carModel);

            infile >> carYear;
            carArrayPtr[count].setYear(carYear);

            infile >> carPrice;
            carArrayPtr[count].setPrice(carPrice);

            infile.ignore();

            count++;
        }

        //Adds the new dealer, "dealer", to the overall vector of "Dealers".
        inventory.push_back(dealer);
    }

    infile.close();
    sleep(1);
    std::cout << "\n\x1b[30;42m.....25%\x1b[0m" << std::endl;
    sleep(1);
    std::cout << "\n\x1b[30;42m.....50%\x1b[0m" << std::endl;
    sleep(1);
    std::cout << "\n\x1b[30;42m.....75%\x1b[0m" << std::endl;
    sleep(1);
    std::cout << "\n\x1b[30;42m.....100%\x1b[0m" << std::endl;
    sleep(1);
}

/// @brief Function to display dealer by name, number and # of cars in inventory
/// @param inventory Vector to hold dealers
inline void displayDealers(std::vector<Dealer> &inventory) {
    for (const auto &i : inventory
            ) {
        std::cout << i << std::endl;
    }
}

/// @brief Function to list dealers and then display their inventory based on user input
/// @param inventory Vector to hold dealers
inline void displayCarsFromDealer(std::vector<Dealer> &inventory) {
    int input = 0;
    unsigned long dealerIndex = 0;
    bool loopBool = true;
    displayDealers(inventory);
    std::cout << "Which dealer? Choose by number."<< std::endl
              << " > ";
    //Checks user input against all the dealer numbers in the vector and sets "dealerIndex" to the dealer found at the index.
    while (loopBool) {

        std::cin >> input;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (input == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) {
            std::cout << "\n\x1b[32;40mSorry, no dealers with  that number."
                      << " Please enter an updated number. " << std::endl
                      << " > \x1b[0m";
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
inline void addCarToDealer(std::vector<Dealer> &inventory) {

    int input;
    unsigned long dealerIndex = 0;
    bool loopBool = true;
    std::string newVin;
    std::string newMake;
    std::string newModel;
    int newYear;
    double newPrice;

    displayDealers(inventory);
    std::cout << "Which dealer? Choose by number."<< std::endl
              << " > ";
    while (loopBool) {

        std::cin >> input;
        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (input == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) {
            std::cout << "\n\x1b[32;40mSorry, no dealers with that number."
                      << " Please enter an updated number. " << std::endl
                      << " > \x1b[0m";
        }
    }
    Dealer currentDealer = inventory.at(dealerIndex);
    bool loop = true;
    std::cin.exceptions(std::istream::failbit);
    do {

        std::cin.ignore();
        std::cout << "Enter new car VIN: " << std::endl
                  << " > ";
        std::getline(std::cin, newVin);

        std::cout << "Enter new car make: " << std::endl
                  << " > ";
        std::getline(std::cin, newMake);

        std::cout << "Enter new car model: " << std::endl
                  << " > ";
        std::getline(std::cin, newModel);

        std::cout << "Enter new car year: " << std::endl
                  << " > ";
        std::cin >> newYear;

        std::cout << "Enter new car price: " << std::endl
                  << " > ";
        std::cin >> newPrice;

        Car *carArray = currentDealer.getCarArrayPtr();
        ///
        /// @brief Array tempCars uses c99 variable length array.
        ///        I would prefer to use vector here.
        ///
        Car tempCars[currentDealer.getNumberOfCars()];

        /// @brief Populates the temp array of cars with the existing cars in carArray.
        /// This is done so the memory can be freed up.
        for (int i = 0; i < currentDealer.getNumberOfCars(); i++) {
            tempCars[i] = carArray[i];
        }

        /// @brief Adds room for one additional car in dealer inventory
        int tempNumCars = currentDealer.getNumberOfCars();
        currentDealer.setNumberOfCars(tempNumCars + 1);

        /// @brief Creates new Car object pointing to the array created in setCarArrayPtr.
        Car *newCarArray = nullptr;
        currentDealer.setCarArrayPtr(newCarArray);

        newCarArray = currentDealer.getCarArrayPtr();

        currentDealer.getNumberOfCars();

        /// @brief newCarArr = carArray;
        for (int i = 0; i < currentDealer.getNumberOfCars() - 1; i++) {
            newCarArray[i] = tempCars[i];
        }

        newCarArray[currentDealer.getNumberOfCars() - 1].setVIN(newVin);
        newCarArray[currentDealer.getNumberOfCars() - 1].setMake(newMake);
        newCarArray[currentDealer.getNumberOfCars() - 1].setModel(newModel);
        newCarArray[currentDealer.getNumberOfCars() - 1].setYear(newYear);
        newCarArray[currentDealer.getNumberOfCars() - 1].setPrice(newPrice);

        inventory.at(dealerIndex) = currentDealer;

        char choice;
        std::cout << "Would you like to add another car? (y/n)" << std::endl
                  << " > ";
        std::cin >> choice;
        switch (choice) {
            case 'y':
            case 'Y':
                loop = true;
                break;
            case 'n':
            case 'N':
                loop = false;
                break;
            default:
                unknownInput();

        }
    } while (loop);
    /// @brief sleep feature.
    /// I'll take it out and offer improved
    /// performance in version two
    sleep(1);
}

/// @brief Function displays dealers, then their inventory
/// then allows user to modify any aspect of the car selected
/// @param inventory Vector to hold dealers
///@TODO implement loop to modify multiple cars and/or option at once
inline void listAndModifyCar(std::vector<Dealer> &inventory) {

    if (carsInInventory(inventory)) {
        int choice = -1;
        int choice1;
        int numberOfCars = 0;
        int input = 0;
        unsigned long dealerIndex = 0;

        bool loopBool = true;
        displayDealers(inventory);
        std::cout << "From the choices above. Enter the dealer number to see cars: " << std::endl;
        std::cout << " > ";
        /// @brief Checks input against all available dealer numbers in the vector and sets "dealerIndex" to the dealer found at the index.
        while (loopBool) {
            std::cin >> input;

            for (unsigned long i = 0; i < inventory.size(); i++) {
                if (input == inventory.at(i).getDealerNumber()) {
                    dealerIndex = i;
                    loopBool = false;
                }
            }
            if (loopBool) {
                std::cout << "\x1b[32;40mSorry, no dealers matched that number. Please enter an updated number. " << std::endl
                          << " > \x1b[0m";
            }
        }
        bool loop = true;
        do {
            Car *carArray = inventory.at(dealerIndex).getCarArrayPtr();

            std::cout << "\n" << inventory.at(dealerIndex).getDealerName() << "\n" << std::endl;
            for (int i = 0; i < inventory.at(dealerIndex).getNumberOfCars(); i++) {
                std::cout << "CAR # " << i + 1 << std::endl
                          << carArray[i] << "\n" << std::endl;
                numberOfCars++;
            }
            std::cout << "\nPlease enter the number of the car you would like to modify:"
                      << std::endl;
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

            std::cin >> choice1;
            switch (choice1) {
                case 1: {
                    std::string newVIN;
                    std::cout << "Current Vin: " << carArray[choice - 1].getVIN() << std::endl
                              << "Please enter new VIN: " << std::endl
                              << " > ";
                    std::cin.ignore();
                    std::getline(std::cin, newVIN);
                    carArray[choice - 1].setVIN(newVIN);
                    break;
                }
                case 2: {
                    std::string newMake;
                    std::cout << "Current Make: " << carArray[choice - 1].getMake() << std::endl
                              << "Please enter new make: " << std::endl
                              << " > ";
                    std::cin.ignore();
                    std::getline(std::cin, newMake);
                    carArray[choice - 1].setMake(newMake);
                }
                    break;
                case 3: {
                    std::string newModel;
                    std::cout << "Current Model: " << carArray[choice - 1].getModel() << std::endl
                              << "Please enter new model: " << std::endl
                              << " > ";
                    std::cin.ignore();
                    std::getline(std::cin, newModel);
                    carArray[choice - 1].setModel(newModel);
                }
                    break;
                case 4: {
                    int newYear;
                    std::cout << "Current Year: " << carArray[choice - 1].getYear() << std::endl
                              << "Please enter new year: " << std::endl
                              << " > ";
                    std::cin.ignore();
                    std::cin >> newYear;
                    carArray[choice - 1].setYear(newYear);
                }
                    break;
                case 5: {
                    double newPrice;
                    std::cout << "Current Price: " << carArray[choice - 1].getPrice() << std::endl
                              << "Please enter new price: " << std::endl
                              << " > ";
                    std::cin.ignore();
                    std::cin >> newPrice;
                    carArray[choice - 1].setPrice(newPrice);
                }
                    break;
                default:
                    unknownInput();
            }
            char choice3;

            std::cout << "Would you like to modify another car?"<< std::endl
                      << " > ";

            std::cin >> choice3;

            switch (choice3) {
                case 'y':
                case 'Y':
                    loop = true;
                    break;
                case 'n':
                case 'N':
                    loop = false;
                    break;
                default:
                    unknownInput();
                    break;
            }
        } while (loop);
    }
}

/// @brief Function bubble sorts cars by  vin
/// @param inventory Vector to hold dealers
inline void sortCarsFromDealer(std::vector<Dealer> &inventory) {
    int input = 0;
    unsigned long dealerIndex = 0;
    bool running = true;

    displayDealers(inventory);
    std::cout << "\x1b[32;40mEnter the dealer number to sort by VIN: "
              << " > \x1b[0m";

    while (running) {

        std::cin >> input;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (input == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                running = false;
            }
        }
        if (running) {
            std::cout << "\x1b[32;40mSorry, no dealers matched that number. Please enter an updated number. " << std::endl
                      << " > \x1b[0m";
        }
    }
    std::cout << std::endl;

    Car *carArray = inventory.at(dealerIndex).getCarArrayPtr();

    Car swap;

    int tempNumberOfCars = inventory.at(dealerIndex).getNumberOfCars();

    for (int i = 0; i < tempNumberOfCars - 1; i++) {
        for (int j = 0; j < tempNumberOfCars - i - 1; j++) {
            if (carArray[j].getVIN() > carArray[j + 1].getVIN()) {
                swap = carArray[j];
                carArray[j] = carArray[j + 1];
                carArray[j + 1] = swap;
            }
        }
    }

    for (int k = 0; k < inventory.at(dealerIndex).getNumberOfCars(); k++) {
        std::cout << carArray[k] << std::endl << std::endl;
    }
}

/// @brief Function to export data to file
/// @param outfile
/// @param inventory Vector to hold dealers
///@TODO integrate BOOST serialization
inline void writeDealersCarsToFile(std::ofstream &outfile, std::vector<Dealer> &inventory) {

    std::cout << "\x1b[32;40mWriting data to outfile.txt" << std::endl;

    outfile.open("../outfile.txt");

    Car *carOut = nullptr;

    for (auto &i : inventory) {
        /// @brief Sets carOut pointer to the Car array inside of the current Dealer.
        carOut = i.getCarArrayPtr();

        outfile << i.getDealerName() << std::endl
                << i.getDealerNumber() << std::endl
                << i.getNumberOfCars() << std::endl;

        for (int l = 0; l < i.getNumberOfCars(); l++) {
            outfile << carOut[l].getVIN() << std::endl
                    << carOut[l].getMake() << std::endl
                    << carOut[l].getModel() << std::endl
                    << carOut[l].getYear() << std::endl
                    << carOut[l].getPrice() << std::endl;
        }
    }
    outfile.close();
    std::cout << "Complete!\x1b[0m" << std::endl;
}



#endif /* SystemFunctions_h */
