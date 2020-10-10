// Title stockmgmt.cpp
// Assignment 4
// Goal:Your task is to create a linked list data structure for an inventory manager application.
// What you learn:This lab assignment will give you further opportunitiesto practice writingclassesand using dynamic memory allocation.
// This lab will give the opportunity to implement the Linked List ADT.
// This is main class that run the program that will call Item, Inventory and Node class.
// Users have menu list to choose adding or delete or load all the product
// Class: CSC 2430 Spring 2019
// Author: Nghi Vo

#include <stdio.h>
#include "item.h"
#include "inventory.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    // Implement variables
    Inventory in;
    int choice;
    ifstream fin;
    
    // User interface of menu that user can choose
    // Break the menu until user choose 7
    while (true){
        // Keep print out the menu until user choose to exit
        cout << "1. Load an Inventory File" << endl;
        cout << "2. List all items" << endl;
        cout << "3. Search by Name" << endl;
        cout << "4. Search by ID" << endl;
        cout << "5. Add a New Item" << endl;
        cout << "6. Delete Item" << endl;
        cout << "7. Exit" << endl;
        cin >> choice;
        
        // User choose 1 - load file
        if (choice == 1){
            string fileName;
            cout << "Input filename:" << endl;
            cin >> fileName;
            
            // Try to open file
            fin.open(fileName);
            if (!fin.is_open()) {
                cout << "Can't open " << "'" << fileName << "'" << endl;
                return -1;
            }
            int loadCount = in.load(fin);
            // Close file after load data
            fin.close();
            cout << loadCount << " items loaded." << endl;
        }
         // User choose 2 - print out all the item in the list
        else if (choice == 2){
            // If list is empty
            if (in.isEmpty()){
                cout << "No item" << endl;
            }
            // Print out using format
            else{
                cout << "ID    Name        Price   Quantity" << endl;
                in.formattedPrint(cout);
            }
        }
        
        // User choose 3 - Search Item by name
        else if (choice == 3){
            string name;
            cout << "Input item name:" << endl;
            // Get name from user
            cin >> name;
            // Using name to find the Item using findItem function
            Item* item = in.findItemByName(name);
            
            // If list have the same name item
            if (item !=  nullptr){
                cout << "ID: " << item->getID() << ", Quantity: " << item->getQuantity() << endl;
            }
            // If no item
            else {
                cout << "No such item" << endl;
            }
        }
        
        // User choose 4 - search by ID
        else if (choice == 4){
            int id;
            // Get item id from user
            cout << "Input item ID:" << endl;
            cin >> id;
            // Using name to find the Item using findItem function
            Item* item = in.findItemByID(id);
            // If list have same Id item
            if (item != nullptr){
                cout << "Name: " << item->getName() << ", Quantity: " << item->getQuantity() << endl;
            }
            // If no item
            else {
                cout << "No such item" << endl;
            }
        }
        
        // User choose 5 - add item with id, name, price, quantity
        else if (choice == 5){
            int id;
            string name;
            double price;
            int quantity;
            
            cout << "Input item ID:" << endl;
            cin >> id;
            cout << "Input item name:" << endl;
            cin >> name;
            cout << "Input price:" << endl;
            cin >> price;
            cout << "Input quantity:" << endl;
            cin >> quantity;
            
            // Create new Item using information from user
            Item* item = new Item(id, name, price, quantity);
            // Add item into list
            if (in.addNewItem(item)){
                cout << "Item has been successfully added" << endl;
            }
            else {
                cout << "Same ID exists, failed to add" << endl;
            }
        }
        // User choose 6 - delete Item
        else if (choice == 6){
            // Get user ID
            int id;
            cout << "Input item ID:" << endl;
            cin >> id;
            // Using delete  function
            if (in.deleteItem(id)){
                cout << "Item has been successfully deleted" << endl;
            }
            else {
                cout << "No such item" << endl;
            }
        }
        // User choose 7 - exit
        else {
            // Break the while
            break;
        }
    }
    return 0;
}

