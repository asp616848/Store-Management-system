#include <iostream>
#include "store.hpp"
#include "inventory.hpp"
#include "accounts.hpp"
using namespace std;

int main() {
    system("\x1b[32m");

    int option;
    Store store; // solved the instantiation problem
    store.Load();
    
    Inventory inventory = store.getInventory();
    cout << "Enter 1 if you want to enter accounts and 0 if you want to enter inventory: ";
    cin >> option;
    if(option==1)
    {
        store.run();
    }
    else
    {
        store.runInv();
    }
    return 0;
}