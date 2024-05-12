#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account {
protected:
    std::string username;
    std::string password;

public:
    static bool compareByExpenditure(const Account *a, const Account *b);

    double expenditure = 0;
    std::string getUsername() const;
    std::string getPassword() const;

    Account(const std::string &username, const std::string &password, int expenditure = 0);

    virtual bool authenticate(const std::string &inputUsername, const std::string &inputPassword) const;
    virtual double getBalance() const;
    virtual std::string getAccountType() const = 0;
};

class CustomerAccount : public Account {
    double balance;

public:
    CustomerAccount(const std::string &username, const std::string &password, int expenditure = 0, int balance = 0);

    std::string getAccountType() const override;
    double getBalance() const;
    void updateBalance(double amount);
};

class MerchantAccount : public Account {
public:
    MerchantAccount(const std::string &username, const std::string &password);

    std::string getAccountType() const override;
    void viewUsersWithBalances(const std::vector<Account *> &accounts);
};

#endif // ACCOUNT_H
