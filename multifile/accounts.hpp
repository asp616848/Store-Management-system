#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
using namespace std;

class Account {
protected:
    string username;
    string password;

public:

    double expenditure = 0;
    string getUsername() const;
    string getPassword() const;

    Account(const string &username, const string &password, int expenditure = 0);

    virtual bool authenticate(const string &inputUsername, const string &inputPassword) const;
    virtual double getBalance() const;
    virtual string getAccountType() const = 0;
};

class CustomerAccount : public Account {
    double balance;
public:
    CustomerAccount(const string &username, const string &password, int expenditure = 0, int balance = 0);

    string getAccountType() const override;
    double getBalance() const;
    void updateBalance(double amount);
};

class MerchantAccount : public Account {
public:
    MerchantAccount(const string &username, const string &password);

    string getAccountType() const override;
    void viewUsersWithBalances(const vector<Account *> &accounts);
};

#endif // ACCOUNT_H
