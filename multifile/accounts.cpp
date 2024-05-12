#include "accounts.hpp"
#include <iostream>

bool Account::compareByExpenditure(const Account *a, const Account *b) {
    return a->expenditure < b->expenditure;
}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

Account::Account(const std::string &username, const std::string &password, int expenditure)
    : username(username), password(password), expenditure(expenditure) {}

bool Account::authenticate(const std::string &inputUsername, const std::string &inputPassword) const {
    return username == inputUsername && password == inputPassword;
}

double Account::getBalance() const {
    return 0;
}

CustomerAccount::CustomerAccount(const std::string &username, const std::string &password, int expenditure, int balance)
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

MerchantAccount::MerchantAccount(const std::string &username, const std::string &password)
    : Account(username, password) {}

std::string MerchantAccount::getAccountType() const {
    return "Seller";
}

void MerchantAccount::viewUsersWithBalances(const std::vector<Account *> &accounts) {
    std::cout << "Users with balances:" << std::endl;
    for (const auto &acc : accounts) {
        if (dynamic_cast<CustomerAccount *>(acc)) {
            std::cout << "Username: " << acc->getUsername() << ", Balance: " << static_cast<CustomerAccount *>(acc)->getBalance() << std::endl;
        }
    }
}
