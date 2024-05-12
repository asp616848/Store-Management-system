#ifndef STORE_HPP
#define STORE_HPP

#include "inventory.hpp"
#include "accounts.hpp"
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

class Store {
private:
    Inventory inventory;
    std::vector<Account *> accounts;
    Account *loggedInAccount = nullptr;

    void encrypt(std::string &str);
    void decrypt(std::string &str);
    Account *login();
    void createUser();
    void stockAlert();
    void createSeller();
    void saveToFile();
    void loadFromFile();

public:
    void printAccounts();
    Inventory getInventory() const;
    Store();
    void Load();
    void run();
};

#endif // STORE_HPP
