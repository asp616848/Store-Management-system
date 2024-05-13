#include "accounts.hpp"
#include <iostream>


#define USER_TYPE_SELLER "Seller"
#define USER_TYPE_USER "User"

string Account::getUsername() const {
    return username;
}

string Account::getPassword() const {
    return password;
}

Account::Account(const string &username, const string &password, int expenditure)
    : username(username), password(password), expenditure(expenditure) {}

bool Account::authenticate(const string &inputUsername, const string &inputPassword) const {
    return username == inputUsername && password == inputPassword;
}

double Account::getBalance() const {
    return 0;
}

CustomerAccount::CustomerAccount(const string &username, const string &password, int expenditure, int balance)
    : Account(username, password, expenditure), balance(balance) {}

string CustomerAccount::getAccountType() const {
    return USER_TYPE_USER;
}

double CustomerAccount::getBalance() const {
    return balance;
}

void CustomerAccount::updateBalance(double amount) {
    balance += amount;
}

MerchantAccount::MerchantAccount(const string &username, const string &password)
    : Account(username, password) {}

string MerchantAccount::getAccountType() const {
    return USER_TYPE_SELLER;
}

void MerchantAccount::viewUsersWithBalances(const vector<Account *> &accounts) {
    cout << "Users with balances:" << endl;
    for (const auto &acc : accounts) {
        if (dynamic_cast<CustomerAccount *>(acc)) {
            cout << "Username: " << acc->getUsername() << ", Balance: " << static_cast<CustomerAccount *>(acc)->getBalance() << endl;
        }
    }
}
