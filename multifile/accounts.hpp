#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

// Base class for user accounts
class Account {
protected:
    std::string username;
    std::string password;

public:
    // compare accounts based on expenditure for the purpose of trend analysis to understand who spends most
    static bool compareByExpenditure(const Account *a, const Account *b);

    double expenditure = 0; // Expenditure associated with the account

    // Getters for username and password
    std::string getUsername() const; 
    std::string getPassword() const;

    // Constructor to initialize username, password, and optionally expenditure
    Account(const std::string &username, const std::string &password, int expenditure = 0);

    // Virtual method to authenticate login credentials
    virtual bool authenticate(const std::string &inputUsername, const std::string &inputPassword) const;

    // Virtual method to get balance (to be overridden by derived classes)
    virtual double getBalance() const;

    // Virtual method to get account type (to be overridden by derived classes)
    virtual std::string getAccountType() const = 0;
};

// Derived class representing a customer account
class CustomerAccount : public Account {
    double balance;

public:
    // Constructor to initialize username, password, expenditure, and balance
    CustomerAccount(const std::string &username, const std::string &password, int expenditure = 0, int balance = 0);

    // Override method to get account type
    std::string getAccountType() const override;
    double getBalance() const;
    void updateBalance(double amount);
};

// Derived class representing a merchant account
class MerchantAccount : public Account {
public:
    // Constructor to initialize username and password
    MerchantAccount(const std::string &username, const std::string &password);

    // Override method to get account type
    std::string getAccountType() const override;
    void viewUsersWithBalances(const std::vector<Account *> &accounts);
};

#endif // ACCOUNT_H
