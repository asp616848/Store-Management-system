#include "accounts.hpp"
#include <iostream>

// compare accounts based on expenditure for the purpose of trend analysis to understand who spends most
bool Account::compareByExpenditure(const Account *a, const Account *b) {
    return a->expenditure < b->expenditure;
}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

// Constructor for Account class
Account::Account(const std::string &username, const std::string &password, int expenditure)
    : username(username), password(password), expenditure(expenditure) {}

// Virtual method to authenticate login credentials by comparing stored username 
//and password to the entered credentials
bool Account::authenticate(const std::string &inputUsername, const std::string &inputPassword) const {
    return username == inputUsername && password == inputPassword;
}

double Account::getBalance() const {
    return 0;
}


// Derived class for customer accounts
CustomerAccount::CustomerAccount(const std::string &username, const std::string &password, int expenditure, int balance) // Constructor for CustomerAccount class
    : Account(username, password, expenditure), balance(balance) {}

std::string CustomerAccount::getAccountType() const {
    return "User";
}

double CustomerAccount::getBalance() const {
    return balance;
}

void CustomerAccount::updateBalance(double amount) {
    balance += amount;
}

MerchantAccount::MerchantAccount(const std::string &username, const std::string &password) // Constructor for MerchantAccount class
    : Account(username, password) {}

std::string MerchantAccount::getAccountType() const {
    return "Seller";
}

// view users with balances for MerchantAccount
void MerchantAccount::viewUsersWithBalances(const std::vector<Account *> &accounts) {
    std::cout << "Users with balances:" << std::endl;
    for (const auto &acc : accounts) {  // Iterate through the accounts vector
        if (dynamic_cast<CustomerAccount *>(acc)) { // Check if 'acc' can be safely casted to a CustomerAccount pointer using dynamic_cast
                                                    // Helps ensure 'acc' is of type CustomerAccount to access its specific properties
                                                    // Safely filters out non-CustomerAccount objects, avoiding potential errors
                                                    
            std::cout << "Username: " << acc->getUsername() << ", Balance: " << static_cast<CustomerAccount *>(acc)->getBalance() << std::endl; 
            // Print username and balance by explicitly casting 'acc' to CustomerAccount pointer using static_cast
            // Assumes 'acc' is a CustomerAccount, may lead to runtime errors if 'acc' is not of that type 
        }
    }
}
