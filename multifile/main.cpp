#include <iostream>
#include "store.hpp"
#include "inventory.hpp"
#include "accounts.hpp"
using namespace std;

int main() {
    system("\x1b[32m"); // Change terminal color to green


    int option; // Variable to store user input for selecting account or inventory
    Store store; // solved the instantiation problem // Instantiate a Store object
    store.Load(); // Load data for the store
    store.printAccounts(); // Load data for the inventory
    cout << "Enter 1 if you want to enter accounts and 0 if you want to enter inventory: ";
    cin >> option;
    if(option==1)
    {
        store.run(); // Call the method to manage accounts
    }
    else
    {
        store.runInv(); // Call the method to manage inventory
    }
    return 0;
}