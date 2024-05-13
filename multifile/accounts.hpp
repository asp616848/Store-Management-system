#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
using namespace std;

// Base class for user accounts
class Account {
protected:
    string username;
    string password;

public:
    // Getters for username and password
    double expenditure = 0;
    string getUsername() const;
    string getPassword() const;

    Account(const string &username, const string &password, int expenditure = 0);

    // Virtual method to authenticate login credentials
    virtual bool authenticate(const string &inputUsername, const string &inputPassword) const;

    // Virtual method to get balance (to be overridden by derived classes)
    virtual double getBalance() const;

    // Virtual method to get account type (to be overridden by derived classes)
    virtual string getAccountType() const = 0;

};

// Derived class representing a customer account
class CustomerAccount : public Account {
    double balance;
public:
    // Constructor to initialize username, password, expenditure, and balance
    CustomerAccount(const string &username, const string &password, int expenditure = 0, int balance = 0);
    // Override method to get account type
    string getAccountType() const override;
    double getBalance() const;
    void updateBalance(double amount);
};

// Derived class representing a merchant account
class MerchantAccount : public Account {
public:
    // Constructor to initialize username and password
    MerchantAccount(const string &username, const string &password);

    // Override method to get account type
    string getAccountType() const override;
    void viewUsersWithBalances(const vector<Account *> &accounts);
};

#endif // ACCOUNT_H
