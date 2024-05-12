#ifndef STORE_SYSTEM_H
#define STORE_SYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// Classes I shall need
class Account;
class UserAccount;
class SellerAccount; //these three for accounts
class Product;
class Inventory;
class Store; // these three for inventory and store

// Base class for user accounts
class Account {
protected:
    std::string username;
    std::string password;
public:
    Account(const std::string& username, const std::string& password);
    virtual bool authenticate(const std::string& inputUsername, const std::string& inputPassword) const;
    virtual std::string getType() const = 0;
};

// Derived class representing user accounts
class UserAccount : public Account {
    double balance; // private balance of user
public:
    UserAccount(const std::string& username, const std::string& password); //param constructor
    std::string getType() const override;  //User or store owner?
    double getBalance() const;  //User can check his/her balance
    void updateBalance(double amount); // update balance is yet set to user but the seller will be notified so its trusted
};

// Derived class representing seller accounts
class SellerAccount : public Account { 
public:
    SellerAccount(const std::string& username, const std::string& password);  //  param constructor
    std::string getType() const override;  //User or store owner?
    void viewUsersWithBalances(const std::vector<Account*>& accounts);  //view all users with balances like ledger
};


// NOW INVENTORY PART

// Class representing a product
class Product { 
    private: // private so they are safe upon inheritance
        int id;
        std::string name;
        std::string category;
        double price;
        int quantity;
    
    public:
        Product(int id, std::string name, std::string category, double price, int quantity); //param constructor
        // Getter and Setters here if required later. I don't see a need now cuz constructor is enough
};

// inventory with seller
class Inventory {
    private:
        std::vector<Product> products; // using vector data type which resembles array but is dynamic
    
    public:
        // Methods for managing inventory
        // functions like add product, remove product, view stock, Analyze stock trends will go here
        void addProduct(const Product& product);
        void removeProduct(int id);
        void viewStock();
        void analyzeStockTrendsAndRecommendBusinessTactics();
};

// just a additional class to seperate the functionalities on inventory 
class Store {
private:
    Inventory inventory;
    std::vector<Account*> accounts;

    // Methods for store functionalities
};

#endif // STORE_SYSTEM_H
