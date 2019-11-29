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

template<class T>
void bubbleSort(T a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; i < j; j--)
            if (a[j] < a[j - 1])
                swap(a[j], a[j - 1]);
}
/*
 * I was trying to implement a more re-usable menu
 * but have yet to get it to work
 *
/// @brief Defines pointer-to-function type.
typedef void (*Menu_Processing_Function_Pointer)();

/// @brief
struct Menu_Option {
    char choice;
    char const *p_selection_text;
    Menu_Processing_Function_Pointer pProcessingPointer;
};

/// @brief prototypes
void Process_Selection_One(std::vector<Car> &inventory) { SystemFunctions::read(inventory); }

void Process_Selection_Two() { SystemFunctions::display(); }

void Process_Selection_Three() { std::cout << "test 3"; }

void Process_Selection_Four() { std::cout << "test 4"; }

void Process_Selection_Five() { std::cout << "test 5"; }

void Process_Selection_Six() { std::cout << "test 6"; }

void Process_Selection_Seven() { std::cout << "test 7"; }

void Process_Selection_Zero() { exit(EXIT_SUCCESS); }

static const Menu_Option main_menu[] =
        {
                {'1', "1. Read Dealers and Cars from file",                    reinterpret_cast<Menu_Processing_Function_Pointer>(Process_Selection_One)},
                {'2', "2. Display Dealers",                                    Process_Selection_Two},
                {'3', "3. Choose a Dealer Number, Display Cars",               Process_Selection_Three},
                {'4', "4. Choose a Dealer Number, Add Car",                    Process_Selection_Four},
                {'5', "5. Choose a Dealer Number, List Cars and Modify a Car", Process_Selection_Five},
                {'6', "6. Choose a Dealer, Sort cars by VIN (EXTRA CREDIT)",   Process_Selection_Six},
                {'7', "7. Write Dealers and Cars to file (EXTRA CREDIT)",      Process_Selection_Seven},
                {'0', "0. Exit",                                               Process_Selection_Zero},

        };
bool userInterface() {
    static const char menu_title[] =
            "\n"
            "------------------------------\n"
            "         Main Menu\n"
            "------------------------------\n"
            "\n";
    std::cout.write(menu_title, sizeof(menu_title) - 1);
    for (const auto &i : main_menu) {
        std::cout << i.p_selection_text << "\n";
    }
    std::cout << "Enter selection, 0 to quit: ";
    char choice = 0;
    std::cin >> choice;


    for (const auto &i : main_menu) {
        if (choice == i.choice) {
            Menu_Processing_Function_Pointer p_function = i.pProcessingPointer;
            (p_function)();
            break;
        }

    }
    return true;
}*/

/// @brief Handles unusable input
/// I don't know why but cLion
/// flags this as too complex to
/// perform data-flow analysis?!?
void unknownInput() {
    { std::cout << "Error?! Please, try again: " << std::endl; }
}

/// @brief Exits program successfully with message
std::string exitProgram() {
    {
        std::cout << "Exiting program!" << std::endl;
        exit(EXIT_SUCCESS);
    }
}

/// @brief Displays error and exits program
void fileNotFound() {
    {
        std::cerr << "File not found! \nExiting Program!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/// @brief
/// @param inventory
/// @return
bool carsInInventory(vector<Dealer> &inventory) {
    {
        if (inventory.empty()) {
            cout << "\nThere are no employees in the directory.\n";
            cout << "\nEither ";
            cout << "\n\t4. Add a Car";
            cout << "\n\t1. Read from file\n";
        }
        return !inventory.empty();
    }
}


static const char menu_title[] =
        "\n"
        "------------------------------\n"
        "         Main Menu\n"
        "------------------------------\n"
        "\n";

/// @brief Reads in Dealers and Cars from file dealers.txt
/// @param infile ifstream variable
/// @param inventory Vector variable
void readFromFile(std::ifstream &infile, vector<Dealer> &inventory) {

    cout << "Reading...";
    int dealer_number, dealer_num_cars, car_year;
    double car_price;
    string dealer_name, car_make, car_model, car_vin;

    infile.open("/Users/bkallen/Desktop/CU Fall 2019/cFundiesPA3Outlines/dealers.txt");
    if (!infile || infile.fail()) { fileNotFound(); }

    while (infile.peek() != EOF) {
        int count = 0;

        Dealer dealer_in;

        getline(infile, dealer_name);
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
    cout << "Done." << endl;
}

/// @brief Displays Dealers to screen
/// @param inventory
void displayDealers(vector<Dealer> &inventory) {
    for (const auto &i : inventory
            ) {
        cout << i << endl;
    }
}

void displayCarsFromDealer(vector<Dealer> &inventory) {
    unsigned long user_dealer_input, dealer_index = 0;
    bool loopBool = true;
    displayDealers(inventory);
    cout << "From the choices above. Enter the dealer number to see cars: ";
    std::cout << "> ";
    //Checks user input against all the dealer numbers in the vector and sets "dealer_index" to the dealer found at the index.
    while (loopBool) {

        cin >> user_dealer_input;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (user_dealer_input == inventory.at(i).getDealerNumber()) {
                dealer_index = i;
                loopBool = false;
            }
        }
        if (loopBool) { cout << "No dealer found with that number. Try again: "; }
    }

    Car *car_array = inventory.at(dealer_index).getCarArrayPtr();

    cout << "\n" << inventory.at(dealer_index).getDealerName() << "\n" << endl;
    for (int i = 0; i < inventory.at(dealer_index).getNumberOfCars(); i++) {
        cout << car_array[i] << "\n" << endl;
    }
}

void addCarToDealer(vector<Dealer> &inventory) {

    unsigned long input;
    unsigned long dealerIndex = 0;
    bool loopBool = true;
    std::string newVin;
    std::string newMake;
    std::string newModel;
    unsigned int newYear;
    double new_price;

    displayDealers(inventory
    );
    cout << "From the choices above. Enter the dealer number to add a new car: ";
    std::cout << "> ";
    while (loopBool) {

        cin >> input;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (input == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) {
            std::cout << "No dealer found with that number. Try again: ";
            std::cout << "> ";
        }
    }

    Dealer currentdealer = inventory.at(dealerIndex);

    std::cin.ignore();
    std::cout << "Enter new car VIN: " << std::endl;
    std::cout << "> ";
    std::getline(cin, newVin);

    std::cout << "Enter new car make: " << std::endl;
    std::cout << "> ";
    std::getline(cin, newMake);

    std::cout << "Enter new car model: " << std::endl;
    std::cout << "> ";
    std::getline(cin, newModel);

    std::cout << "Enter new car year: " << std::endl;
    std::cout << "> ";
    std::cin >> newYear;

    std::cout << "Enter new car price: " << std::endl;

    std::cout << "> ";
    std::cin >> new_price;

    std::cout << "\nAdding..." << std::endl;

    Car *carArray = currentdealer.getCarArrayPtr();
    Car tempCars[currentdealer.getNumberOfCars()];

    //Populates the temporary array of cars with the existing cars in carArray. This is done so the memory can be freed up.
    for (int i = 0; i < currentdealer.getNumberOfCars(); i++) {
        tempCars[i] = carArray[i];
    }


    //Adds one to the number of cars in the dealers inventory in order to make room for new user car
    int tempNumberOfCars = currentdealer.getNumberOfCars();
    currentdealer.setNumberOfCars(tempNumberOfCars + 1);

    //Creates new Car object pointing to the array created in setCarArrayPtr.
    Car *newCarArray = nullptr;
    currentdealer.setCarArrayPtr(newCarArray);

    newCarArray = currentdealer.getCarArrayPtr();

    currentdealer.getNumberOfCars();

    // newCarArray = carArray;
    for (int i = 0; i < currentdealer.getNumberOfCars() - 1; i++) {
        newCarArray[i] = tempCars[i];
    }

    newCarArray[currentdealer.getNumberOfCars() - 1].setVIN(newVin);
    newCarArray[currentdealer.getNumberOfCars() - 1].setMake(newMake);
    newCarArray[currentdealer.getNumberOfCars() - 1].setModel(newModel);
    newCarArray[currentdealer.getNumberOfCars() - 1].setYear(newYear);
    newCarArray[currentdealer.getNumberOfCars() - 1].setPrice(new_price);

    inventory.at(dealerIndex) = currentdealer;

    std::cout << "Done." << std::endl;
}


void listAndModifyCar(vector<Dealer> &inventory) {

    if (carsInInventory(inventory)) {
        int choice;
        int choice1;
        int numberOfCars = 0;

        unsigned long userDealerInput;
        unsigned long dealerIndex = 0;

        bool loopBool = true;
        displayDealers(inventory);
        std::cout << "From the choices above. Enter the dealer number to see cars: " << std::endl;
        std::cout << "> ";
        //Checks user input against all the dealer numbers in the vector and sets "dealerIndex" to the dealer found at the index.
        while (loopBool) {

            cin >> userDealerInput;

            for (unsigned long i = 0; i < inventory.size(); i++) {
                if (userDealerInput == inventory.at(i).getDealerNumber()) {
                    dealerIndex = i;
                    loopBool = false;
                }
            }
            if (loopBool) {
                std::cout << "No dealer found with that number. Try again: " << std::endl
                          << "> " << std::endl;
            }
        }

        Car *carArrayPtr = inventory.at(dealerIndex).getCarArrayPtr();

        cout << "\n" << inventory.at(dealerIndex).getDealerName() << "\n" << endl;
        for (int i = 0; i < inventory.at(dealerIndex).getNumberOfCars(); i++) {
            cout << "CAR # " << i + 1 << std::endl
                 << carArrayPtr[i] << "\n" << endl;
            numberOfCars++;
        }
        std::cout << "\nPlease enter the number of the car you would like to modify:" << std::endl;
        std::cout << "> ";
        std::cin >> choice;
        std::cout << "You picked:  " << carArrayPtr[choice - 1].getModel() << std::endl
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
                std::getline(cin, newVIN);
                carArrayPtr[choice - 1].setVIN(newVIN);
            }
                break;
            case 2: {
                std::string newMake;
                std::cout << "Please enter new make: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::getline(cin, newMake);
                carArrayPtr[choice - 1].setMake(newMake);
            }
                break;
            case 3: {
                std::string newModel;
                std::cout << "Please enter new model: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::getline(cin, newModel);
                carArrayPtr[choice - 1].setModel(newModel);
            }
                break;
            case 4: {
                int newYear;
                std::cout << "Please enter new year: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::cin >> newYear;
                carArrayPtr[choice - 1].setYear(newYear);
            }
                break;
            case 5: {
                double newPrice;
                std::cout << "Please enter new price: " << std::endl
                          << "> ";
                std::cin.ignore();
                std::cin >> newPrice;
                carArrayPtr[choice - 1].setPrice(newPrice);
            }
                break;
            default: {
                unknownInput();
            }
        }


    }
}

void sortCarsFromDealer(vector<Dealer> &inventory) {
    unsigned long userDealerInput;
    unsigned long dealerIndex = 0;
    bool loopBool = true;

    displayDealers(inventory);
    std::cout << "From the choices above. Enter the dealer number to add a new car: " << std::endl
              << "> ";
    while (loopBool) {

        std::cin >> userDealerInput;

        for (unsigned long i = 0; i < inventory.size(); i++) {
            if (userDealerInput == inventory.at(i).getDealerNumber()) {
                dealerIndex = i;
                loopBool = false;
            }
        }
        if (loopBool) {
            std::cout << "No dealer found with that number. Try again: " << std::endl
                      << "> ";
        }
    }

    Car *carArrayPtr = inventory.at(dealerIndex).getCarArrayPtr();


    Car swap;

    int n = inventory.at(dealerIndex).getNumberOfCars();
    //Using bubble sort
    for (unsigned int i = 0; i < n - 1; i++) {
        for (unsigned int j = 0; j < n - i - 1; j++) {
            if (carArrayPtr[j].getVIN() > carArrayPtr[j + 1].getVIN()) {
                swap = carArrayPtr[j];
                carArrayPtr[j] = carArrayPtr[j + 1];
                carArrayPtr[j + 1] = swap;
            }
        }
    }
    for (unsigned int k = 0; k < n; k++) {
        std::cout << carArrayPtr[k] << "\n" << std::endl;
        std::cout << endl;
    }
    std::cout << std::endl;
}

void writeDealersCarsToFile(ofstream &outfile, vector<Dealer> &inventory) {
    std::cout << "Outputting...";
    outfile.open("../output.txt");

    //Creates instance of pointing to class Car called carOut.
    Car *carOut = nullptr;

    for (auto &i : inventory) {
        //Sets carOut pointer to the Car array inside of the current Dealer.
        carOut = i.getCarArrayPtr();

        outfile << i.getDealerName() << std::endl;
        outfile << i.getDealerNumber() << std::endl;
        outfile << i.getNumberOfCars() << std::endl;
        for (int j = 0; j < i.getNumberOfCars(); j++) {
            outfile << carOut[j].getVIN() << std::endl;
            outfile << carOut[j].getMake() << std::endl;
            outfile << carOut[j].getModel() << std::endl;
            outfile << carOut[j].getYear() << std::endl;
            outfile << carOut[j].getPrice() << std::endl;
        }

    }
    outfile.close();
    std::cout << "Done." << std::endl;
}

bool printMenu() {
    std::cout << menu_title
              << "1.\tRead Dealers and Cars from file." << std::endl
              << "2.\tDisplay Dealers." << std::endl
              << "3.\tChoose a Dealer Number, Display Cars." << std::endl
              << "4.\tChoose a Dealer Number, Add Car." << endl
              << "5.\tChoose a Dealer Number, List Cars and Modify a Car" << std::endl
              << "6.\tChoose a Dealer, Sort cars by VIN." << endl
              << "7.\tWrite Dealers and Cars to file." << endl
              << "0.\tExit" << endl
              << "Please enter a number corresponding to the menu: " << std::endl
              << "> ";
    return true;
}

#endif /* SystemFunctions_hpp */
