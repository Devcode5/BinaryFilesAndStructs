//  main.cpp
//  BinaryFilesAndStructs
//  Created by Aqila Nasiry on 5/11/25.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

// Constants
const int DESC_SIZE = 51;
const int ID_SIZE = 21;
const char FILE_NAME[] = "inventory.dat";

// Structure to store inventory information
struct InventoryItem {
    char itemDescription[DESC_SIZE];
    char productId[ID_SIZE];
    int quantityOnHand;
    double wholesaleCost;
    double retailCost;
};

// Function prototypes
void showMenu();
void addNewRecord();
void displayAllRecords();

int main() {
    int userChoice = 0;

    do {
        showMenu();
        cin >> userChoice;

        // Input validation
        while (userChoice < 1 || userChoice > 3) {
            cout << "Invalid choice. Please select 1, 2, or 3: ";
            cin >> userChoice;
        }

        if (userChoice == 1) {
            addNewRecord();
        } else if (userChoice == 2) {
            displayAllRecords();
        }

    } while (userChoice != 3);

    return 0;
}

// Displays the main menu
void showMenu() {
    cout << "First Option: Add new records to the file\n";
    cout << "Second Option: Display all records in the file \n";
    cout << "Third Option: Done\n";
    cout << "Enter your Option number: ";
}

// Adds a new inventory record to the file
void addNewRecord() {
    InventoryItem newItem;
    fstream outFile(FILE_NAME, ios::out | ios::app | ios::binary);

    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    cin.ignore(); // Clear newline from input buffer

    cout << "Enter item description: ";
    cin.getline(newItem.itemDescription, DESC_SIZE);

    cout << "Enter product ID: ";
    cin.getline(newItem.productId, ID_SIZE);

    cout << "Enter quantity: ";
    cin >> newItem.quantityOnHand;

    cout << "Enter wholesale cost: ";
    cin >> newItem.wholesaleCost;

    cout << "Enter retail cost: ";
    cin >> newItem.retailCost;

    outFile.write(reinterpret_cast<char*>(&newItem), sizeof(InventoryItem));
    outFile.close();

    cout << "Record added successfully.\n";
}

// Displays all records
void displayAllRecords() {
    InventoryItem currentItem;
    fstream inFile(FILE_NAME, ios::in | ios::binary);

    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n*** Inventory Records Are As Followig:  ***\n";

    inFile.read(reinterpret_cast<char*>(&currentItem), sizeof(InventoryItem));

    while (!inFile.eof()) {
        cout << "\nItem Description : " << currentItem.itemDescription << endl;
        cout << "Product ID       : " << currentItem.productId << endl;
        cout << "Quantity on Hand : " << currentItem.quantityOnHand << endl;
        cout << "Wholesale Cost   : $" << currentItem.wholesaleCost << endl;
        cout << "Retail Cost      : $" << currentItem.retailCost << endl;

        inFile.read(reinterpret_cast<char*>(&currentItem), sizeof(InventoryItem));
    }

    inFile.close();
}
