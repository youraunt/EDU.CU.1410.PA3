//
//  SystemFunctions.hpp
//  PA3
//
//  Created by BK Allen on 11/23/19.
//  Copyright © 2019 BK Allen. All rights reserved.
//

#ifndef SystemFunctions_hpp
#define SystemFunctions_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include "Dealer.h"


/// @brief Handles unusable input
void unknownInput() {
    std::cout << "Error?! Please, try again: " << std::endl;
}

/// @brief Exits program successfully with message
std::string exitProgram() {
    std::cout << "Exiting program!" << std::endl;
    exit(EXIT_SUCCESS);
}

/// @brief Displays error and exits program
void fileNotFound() {
    std::cerr << "File not found! \nExiting Program!" << std::endl;
    exit(EXIT_FAILURE);
}

bool carsInInventory(std::vector<Dealer> &inventory
) {
    if (inventory.empty()) {
        cout << "\nThere are no employees in the directory.\n";
        cout << "\nEither ";
        cout << "\n\t2. Add a Car";
        cout << "\n\t7. Read from file\n";
    }
    return !inventory.empty();
}

int getMenuChoice(int numChoices) {
    int choice; // Holds user's choice

    // Keep asking until a valid choice is made
    do {
        std::cout << "\n> ";
        std::cin >> choice;
        std::cin.ignore();

        // Valid choices range from 1 to numChoices
        if (choice < 1 || choice > numChoices) {
            std::cout << std::endl << choice << " is not a valid menu choice."
                      << "\nPlease make a selection between 1 and " << numChoices << std::endl;
        }

    } while (choice < 1 || choice > numChoices);

    return choice;
}

static const char menu_title[] =
        "\n"
        "------------------------------\n"
        "         Main Menu\n"
        "------------------------------\n"
        "\n";


void readFromFile(std::ifstream &infile, std::vector<Dealer> &inventory) {

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
        inventory
                .push_back(dealer_in);
    }

    infile.close();
    std::cout << "Done." << std::endl;
}

void displayDealers(std::vector<Dealer> &inventory
) {
    for (const auto &i : inventory
            ) {
        std::cout << i << std::endl;
    }
}

void displayCarsFromDealer(std::vector<Dealer> &inventory
) {
    unsigned long userDealerInput = 0;
    unsigned long dealerIndex = 0;
    bool loopBool = true;
    displayDealers(inventory
    );
    std::cout << "From the choices above. Enter the dealer number to see cars: ";
    //Checks user input against all the dealer numbers in the vector and sets "dealer_index" to the dealer found at the index.
    while (loopBool) {

        std::cin >> userDealerInput;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (userDealerInput == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) { cout << "No dealer found with that number. Try again: "; }
    }

    Car *carArray = inventory.at(dealerIndex).getCarArrayPtr();

    std::cout << "\n" << inventory.at(dealerIndex).getDealerName() << "\n" << std::endl;
    for (int i = 0; i < inventory.at(dealerIndex).getNumberOfCars(); i++) {
        std::cout << carArray[i] << "\n" << std::endl;
    }
}

void addCarToDealer(std::vector<Dealer> &inventory) {

    unsigned long input;
    unsigned long dealerIndex = 0;
    bool loopBool = true;
    std::string newVin;
    std::string newMake;
    std::string newModel;
    unsigned int newYear;
    double new_price;

    displayDealers(inventory);
    std::cout << "From the choices above. Enter the dealer number to add a new car: ";
    while (loopBool) {

        std::cin >> input;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (input == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) { cout << "No dealer found with that number. Try again: "; }
    }

    Dealer currentDealer = inventory.at(dealerIndex);

    std::cin.ignore();
    std::cout << "Enter new car VIN: ";
    std::getline(cin, newVin);

    std::cout << "Enter new car make: ";
    std::getline(cin, newMake);

    std::cout << "Enter new car model: ";
    std::getline(cin, newModel);

    std::cout << "Enter new car year: ";
    std::cin >> newYear;

    std::cout << "Enter new car price: ";
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

    cout << "Done." << endl;
}


void listAndModifyCar(std::vector<Dealer> &inventory) {

    if (carsInInventory(inventory)) {
        int choice;
        int choice1;
        int numberOfCars = 0;

        unsigned long userDealerInput = 0;
        unsigned long dealerIndex = 0;

        bool loopBool = true;
        displayDealers(inventory
        );
        cout << "From the choices above. Enter the dealer number to see cars: ";
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
            if (loopBool) { cout << "No dealer found with that number. Try again: "; }
        }

        Car *carArray = inventory
                .at(dealerIndex).getCarArrayPtr();

        cout << "\n" << inventory
                .at(dealerIndex).getDealerName() << "\n" << endl;
        for (int i = 0; i < inventory
                .at(dealerIndex).getNumberOfCars(); i++) {
            cout << "CAR # " << i + 1 << std::endl
                 << carArray[i] << "\n" << endl;
            numberOfCars++;
        }
        std::cout << "\nPlease enter the number of the car you would like to modify:" << std::endl;
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

void sortCarsFromDealer(vector<Dealer> &inventory
) {
    unsigned long userDealerInput = 0;
    unsigned long dealerIndex = 0;
    bool loopBool = true;

    displayDealers(inventory
    );
    cout << "From the choices above. Enter the dealer number to add a new car: ";
    while (loopBool) {

        cin >> userDealerInput;

        for (unsigned long i = 0; i < inventory
                .size(); i++) {
            if (userDealerInput == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) { cout << "No dealer found with that number. Try again: "; }
    }
    //Adds output buffer to make it more readable.
    cout << endl;

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
        cout << carArray[k] << "\n" << endl;
    }
}

void writeDealersCarsToFile(ofstream &outfile, vector<Dealer> &inventory) {
    cout << "Writing to outfile...";
    outfile.open("../outfile.txt");

    //Creates instance of pointing to class Car called carOut.
    Car *carOut = nullptr;

    for (auto &i : inventory
            ) {
        //Sets carOut pointer to the Car array inside of the current Dealer.
        carOut = i.getCarArrayPtr();

        outfile << i.getDealerName() << endl;
        outfile << i.getDealerNumber() << endl;
        outfile << i.getNumberOfCars() << endl;
        for (int j = 0; j < i.getNumberOfCars(); j++) {
            outfile << carOut[j].getVIN() << endl;
            outfile << carOut[j].getMake() << endl;
            outfile << carOut[j].getModel() << endl;
            outfile << carOut[j].getYear() << endl;
            outfile << carOut[j].getPrice() << endl;
        }

    }
    outfile.close();
    cout << "Done." << endl;
}

bool printMenu() {
    std::cout << menu_title;
    std::cout << "1.\tRead Dealers and Cars from file." << std::endl;
    std::cout << "2.\tDisplay Dealers." << std::endl;
    std::cout << "3.\tChoose a Dealer Number, Display Cars." << std::endl;
    std::cout << "4.\tChoose a Dealer Number, Add Car." << endl;
    std::cout << "5.\tChoose a Dealer Number, List Cars and Modify a Car" << std::endl;
    std::cout << "6.\tChoose a Dealer, Sort cars by VIN." << endl;
    std::cout << "7.\tWrite Dealers and Cars to file." << endl;
    std::cout << "0.\tExit" << endl;
    std::cout << "Please enter a number corresponding to the menu: ";
    return true;
}

#endif /* SystemFunctions_hpp */
