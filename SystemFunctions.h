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

using namespace std;

/*
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
bool carsInInventory(vector<Dealer> &dealerVec)
{
    if (dealerVec.empty())
    {
        cout << "\nThere are no employees in the directory.\n";
        cout << "\nEither ";
        cout << "\n\t2. Add a Car";
        cout << "\n\t7. Read from file\n";
    }
    return !dealerVec.empty();
}
int getMenuChoice(int numChoices)
{
    int choice; // Holds user's choice

    // Keep asking until a valid choice is made
    do {
        cout << "\n> ";
        cin >> choice;
        cin.ignore();

        // Valid choices range from 1 to numChoices
        if (choice < 1 || choice > numChoices)
        {
            cout << endl << choice << " is not a valid menu choice."
                 << "\nPlease make a selection between 1 and " << numChoices << endl;
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


void readDealersAndCarsFromFile(std::ifstream &infile, vector<Dealer> &dealerVec) {

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
        if (dealer_name.empty()){
            break;
        }
        dealer_in.setDealerName(dealer_name);

        infile >> dealer_number;
        dealer_in.setDealerNumber(dealer_number);

        infile >> dealer_num_cars;
        dealer_in.setNumberOfCars(dealer_num_cars);

        //Creates a pointer carArr of type "Car"
        Car *carArr = nullptr;
        //Sets the "CarArrayPtr" in the "Dealer" class to the dynamic pointer.
        //This function then dynamically creates an array of type "Car" and of size "number of cars".
        dealer_in.setCarArrayPtr(carArr);

        carArr = dealer_in.getCarArrayPtr();

        //Since the next input getter is "cin" the input needs to ignore the next "\0" to use "cin" after "getline"
        infile.ignore();
        while (count < dealer_in.getNumberOfCars()) {
            //Reads the VIN string from file in and set the car at index "count" VIN to the read vin.
            getline(infile, car_vin);
            carArr[count].setVIN(car_vin);

            getline(infile, car_make);
            carArr[count].setMake(car_make);

            getline(infile, car_model);
            carArr[count].setModel(car_model);

            infile >> car_year;
            carArr[count].setYear(car_year);

            infile >> car_price;
            carArr[count].setPrice(car_price);

            infile.ignore();

            count++;
        }

        //Adds the new dealer, "dealer_in", to the overall vector of "Dealers".
        dealerVec.push_back(dealer_in);
    }

    infile.close();
    cout << "Done." << endl;
}

void displayDealers(vector<Dealer> &dealerVec){
    for (const auto & i : dealerVec){
        cout << i << endl;
    }
}

void displayCarsFromDealer(vector<Dealer> &dealerVec) {
    unsigned long user_dealer_input, dealer_index = 0;
    bool loop_bool = true;
    displayDealers(dealerVec);
    cout << "From the choices above. Enter the dealer number to see cars: ";
    //Checks user input against all the dealer numbers in the vector and sets "dealer_index" to the dealer found at the index.
    while(loop_bool) {

        cin >> user_dealer_input;

        for (unsigned long i = 0; i < dealerVec.size(); i++){
            if (user_dealer_input == dealerVec.at(i).getDealerNumber()) {
                dealer_index = i;
                loop_bool = false;
            }
        }
        if (loop_bool) { cout << "No dealer found with that number. Try again: "; }
    }

    Car* car_array = dealerVec.at(dealer_index).getCarArrayPtr();

    cout << "\n" << dealerVec.at(dealer_index).getDealerName() << "\n" << endl;
    for (int i = 0; i < dealerVec.at(dealer_index).getNumberOfCars(); i++){
        cout << car_array[i] << "\n" << endl;
    }
}

void addCarToDealer(vector<Dealer> &dealerVec) {



        unsigned long user_dealer_input, dealer_index = 0;
        bool loop_bool = true;
        string new_vin, new_make, new_model;
        int new_year;
        double new_price;

        displayDealers(dealerVec);
        cout << "From the choices above. Enter the dealer number to add a new car: ";
        while (loop_bool) {

            cin >> user_dealer_input;

            for (unsigned long i = 0; i < dealerVec.size(); i++) {
                if (user_dealer_input == dealerVec.at(i).getDealerNumber()) {
                    dealer_index = i;
                    loop_bool = false;
                }
            }
            if (loop_bool) { cout << "No dealer found with that number. Try again: "; }
        }

        Dealer curr_dealer = dealerVec.at(dealer_index);

        cin.ignore();
        cout << "Enter new car VIN: ";
        getline(cin, new_vin);

        cout << "Enter new car make: ";
        getline(cin, new_make);

        cout << "Enter new car model: ";
        getline(cin, new_model);

        cout << "Enter new car year: ";
        cin >> new_year;

        cout << "Enter new car price: ";
        cin >> new_price;

        cout << "\nAdding...";

        Car *car_array = curr_dealer.getCarArrayPtr();
        Car temp_cars[curr_dealer.getNumberOfCars()];

        //Populates the temporary array of cars with the existing cars in car_array. This is done so the memory can be freed up.
        for (int i = 0; i < curr_dealer.getNumberOfCars(); i++) {
            temp_cars[i] = car_array[i];
        }


        //Adds one to the number of cars in the dealers inventory in order to make room for new user car
        int temp_num_cars = curr_dealer.getNumberOfCars();
        curr_dealer.setNumberOfCars(temp_num_cars + 1);

        //Creates new Car object pointing to the array created in setCarArrayPtr.
        Car *new_car_arr = nullptr;
        curr_dealer.setCarArrayPtr(new_car_arr);

        new_car_arr = curr_dealer.getCarArrayPtr();

        curr_dealer.getNumberOfCars();

        // new_car_arr = car_array;
        for (int i = 0; i < curr_dealer.getNumberOfCars() - 1; i++) {
            new_car_arr[i] = temp_cars[i];
        }

        new_car_arr[curr_dealer.getNumberOfCars() - 1].setVIN(new_vin);
        new_car_arr[curr_dealer.getNumberOfCars() - 1].setMake(new_make);
        new_car_arr[curr_dealer.getNumberOfCars() - 1].setModel(new_model);
        new_car_arr[curr_dealer.getNumberOfCars() - 1].setYear(new_year);
        new_car_arr[curr_dealer.getNumberOfCars() - 1].setPrice(new_price);

        dealerVec.at(dealer_index) = curr_dealer;

        cout << "Done." << endl;
    }


void listAndModifyCar(vector<Dealer> &dealerVec) {

    if (carsInInventory(dealerVec)) {
        int choice;
        int choice1;
        int numberOfCars = 0;

        unsigned long user_dealer_input, dealer_index = 0;

        bool loop_bool = true;
        displayDealers(dealerVec);
        cout << "From the choices above. Enter the dealer number to see cars: ";
        //Checks user input against all the dealer numbers in the vector and sets "dealer_index" to the dealer found at the index.
        while (loop_bool) {

            cin >> user_dealer_input;

            for (unsigned long i = 0; i < dealerVec.size(); i++) {
                if (user_dealer_input == dealerVec.at(i).getDealerNumber()) {
                    dealer_index = i;
                    loop_bool = false;
                }
            }
            if (loop_bool) { cout << "No dealer found with that number. Try again: "; }
        }

        Car *car_array = dealerVec.at(dealer_index).getCarArrayPtr();

        cout << "\n" << dealerVec.at(dealer_index).getDealerName() << "\n" << endl;
        for (int i = 0; i < dealerVec.at(dealer_index).getNumberOfCars(); i++) {
            cout <<"CAR # " <<  i +1 <<std::endl
                 << car_array[i] << "\n" << endl;
            numberOfCars ++;
        }
        std::cout << "\nPlease enter the number of the car you would like to modify:" << std::endl;
        std::cin >> choice;
        std::cout << "You picked:  " << car_array[choice-1].getModel()  << std::endl
                  << "Which aspect would you like to update? " << std::endl
                  << "\t1.\tVIN"<<std::endl
                  << "\t2.\tMAKE"<<std::endl
                  << "\t3.\tMODEL"<<std::endl
                  << "\t4.\tYEAR"<<std::endl
                  << "\t5.\tPRICE"<<std::endl;
        std::cin >> choice1;
            switch(choice1){
                case 1:

                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    unknownInput();

            }




    }
}
void sortCarsFromDealer(vector<Dealer> &dealerVec) {
    unsigned long  user_dealer_input, dealer_index = 0;
    bool loop_bool = true;

    displayDealers(dealerVec);
    cout << "From the choices above. Enter the dealer number to add a new car: ";
    while(loop_bool) {

        cin >> user_dealer_input;

        for (unsigned long i = 0; i < dealerVec.size(); i++){
            if (user_dealer_input == dealerVec.at(i).getDealerNumber()) {
                dealer_index = i;
                loop_bool = false;
            }
        }
        if (loop_bool) { cout << "No dealer found with that number. Try again: "; }
    }
    //Adds output buffer to make it more readable.
    cout << endl;

    Car* car_array = dealerVec.at(dealer_index).getCarArrayPtr();

    int i, j;
    Car swap;
    int n = dealerVec.at(dealer_index).getNumberOfCars();

    //Using bubble sort
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (car_array[j].getVIN() > car_array[j+1].getVIN()){
                swap = car_array[j];
                car_array[j] = car_array[j+1];
                car_array[j+1] = swap;
            }
        }
    }

    for (unsigned long k = 0; k < dealerVec.at(dealer_index).getNumberOfCars(); k++){
        cout << car_array[k] << "\n" << endl;
    }
}

void writeDealersCarsToFile(ofstream &outfile, vector<Dealer> &dealerVec) {
    cout << "Outputting...";
    outfile.open("out.txt");

    //Creates instance of pointing to class Car called carOut.
    Car *carOut = nullptr;

    for (auto & i : dealerVec){
        //Sets carOut pointer to the Car array inside of the current Dealer.
        carOut = i.getCarArrayPtr();

        outfile << i.getDealerName() << endl;
        outfile << i.getDealerNumber() << endl;
        outfile << i.getNumberOfCars() << endl;
        for (int j = 0; j < i.getNumberOfCars(); j++){
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
