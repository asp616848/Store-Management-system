#include "accounts.hpp"
#include <iostream>
using namespace std;

// Define user types as constants for clarity
#define USER_TYPE_SELLER "Seller"
#define USER_TYPE_USER "User"

// Account class implementation
string Account::getUsername() const {
    return username;
}

string Account::getPassword() const {
    return password;
}

// Constructor for Account class
Account::Account(const string &username, const string &password, int expenditure)
    : username(username), password(password), expenditure(expenditure) {}
// Virtual method to authenticate login credentials by comparing stored username 
//and password to the entered credentials
bool Account::authenticate(const string &inputUsername, const string &inputPassword) const {
    return username == inputUsername && password == inputPassword;
}

// Placeholder method for getting balance (to be overridden by derived classes)
double Account::getBalance() const {
    return 0;
}


// CustomerAccount class implementation (derived from Account)
CustomerAccount::CustomerAccount(const string &username, const string &password, int expenditure, int balance)
    : Account(username, password, expenditure), balance(balance) {}

// Method to return the type of account (for a customer)
string CustomerAccount::getAccountType() const {
    return USER_TYPE_USER;
}

// Method to get the balance of a customer account
double CustomerAccount::getBalance() const {
    return balance;
}

// Method to update the balance of a customer account
void CustomerAccount::updateBalance(double amount) {
    balance += amount;
}
// Constructor for MerchantAccount class
// MerchantAccount class implementation (derived from Account)
MerchantAccount::MerchantAccount(const string &username, const string &password) : Account(username, password) {}

// Method to return the type of account (for a merchant)
string MerchantAccount::getAccountType() const {
    return USER_TYPE_SELLER;
}
// Method to view users (specifically customers) with balances
void MerchantAccount::viewUsersWithBalances(const vector<Account *> &accounts) {
    cout << "Users with balances:" << endl;// Iterate through the accounts vector
    for (const auto &acc : accounts) {
        // Check if the account is a CustomerAccount using dynamic_cast
        if (dynamic_cast<CustomerAccount *>(acc)) {// Check if 'acc' can be safely casted to a CustomerAccount pointer using dynamic_cast
                                                    // Helps ensure 'acc' is of type CustomerAccount to access its specific properties
                                                    // Safely filters out non-CustomerAccount objects, avoiding potential errors
            // Output username and balance for customer accounts
            cout << "Username: " << acc->getUsername() << ", Balance: " << static_cast<CustomerAccount *>(acc)->getBalance() << endl;
            // Print username and balance by explicitly casting 'acc' to CustomerAccount pointer using static_cast
            // Assumes 'acc' is a CustomerAccount, may lead to runtime errors if 'acc' is not of that type 
        }
    }
}
