#include "store.hpp"
#include <iostream>
#include <queue>
using namespace std;

void Store::encrypt(std::string &str) {
    int key = 3;
    for (char &c : str) {
        if (isalpha(c)) {
            if (islower(c)) {
                c = ((c - 'a' + key) % 26) + 'a';
            } else if (isupper(c)) {
                c = ((c - 'A' + key) % 26) + 'A';
            }
        }
    }
}

void Store::decrypt(std::string &str) {
    int key = 3;
    for (char &c : str) {
        if (isalpha(c)) {
            if (islower(c)) {
                c = (((c - 'a' - key) % 26 + 26) % 26) + 'a';
            } else {
                c = (((c - 'A' - key) % 26 + 26) % 26) + 'A';
            }
        }
    }
}

Account *Store::login() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (Account *acc : accounts) {
        if (acc->authenticate(username, password)) {
            std::cout << "Login successful. Welcome, " << username << " (" << acc->getAccountType() << ")" << std::endl;
            return acc;
        }
    }

    std::cout << "Login failed. Invalid username or password." << std::endl;
    return nullptr;
}

void Store::createUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    accounts.push_back(new CustomerAccount(username, password));
    std::cout << "User account created successfully." << std::endl;
}

void Store::stockAlert() {
    bool alert = false;
    for (const auto &product : inventory.getProducts()) {
        if (product.getQuantity() <= 4) {
            std::cout << "Stock Empty Alert! for product: " << product.getName() << " with product quantity: " << product.getQuantity() << std::endl;
            alert = true;
        }
    }
    if (!alert) {
        std::cout << "No products with low stock." << std::endl;
    }
}

void Store::createSeller() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    accounts.push_back(new MerchantAccount(username, password));
    std::cout << "Seller account created successfully." << std::endl;
}

void Store::saveToFile() {
    std::ofstream file;
    file.open("users.csv");

    for (const auto &acc : accounts) {
        std::string a = acc->getAccountType();
        std::string b = acc->getUsername();
        std::string c = acc->getPassword();
        double d = acc->expenditure;
        double e = acc->getBalance();

        encrypt(a);
        encrypt(b);
        encrypt(c);

        d = d + 1029;
        e = e + 1029;

        file << a << "," << b << "," << c << "," << d << "," << e << std::endl;
    }
    file.close();
}

void Store::loadFromFile() {
    std::ifstream file;
    file.open("users.csv");

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string type, username, password, exp, bal;
            getline(ss, type, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, exp, ',');
            getline(ss, bal, ',');
            double expenditure = stoi(exp);
            double balance = stoi(bal);

            decrypt(type);
            decrypt(username);
            decrypt(password);
            expenditure = expenditure - 1029;
            balance = balance - 1029;

            if (type == "User") {
                accounts.push_back(new CustomerAccount(username, password, expenditure, balance));
            } else if (type == "Seller") {
                accounts.push_back(new MerchantAccount(username, password));
            }
        }

        file.close();
    } else {
        std::cout << "Error: Could not open file accounts.txt" << std::endl;
    }
}

void Store::printAccounts() {
    for (Account *each : accounts) {
        std::cout << each->getUsername() << std::endl;
        std::cout << each->getPassword() << std::endl;
    }
}

Inventory Store::getInventory() const {
    return inventory;
}

Store::Store() {
    inventory.loadInventoryFromFile("inventory.csv");
}

void Store::Load() {
    loadFromFile();
}

void Store::run() {
    char choice;
    char choice;
        do
        {
            cout << "-----------------------------------------------------------" << endl;
            cout << "Please choose an option:" << endl;
            cout << "1. Login" << endl;
            cout << "2. Create User Account" << endl;
            cout << "3. Create Seller Account" << endl;
            cout << "4. Update Balance (for users)" << endl;
            cout << "5. View Users with Balances (for sellers)" << endl;
            cout << "6. Make a purchase (Customers Only)" << endl;
            cout << "7. Stock Alert" << endl;
            cout << "8. List of highest spending users" << endl;
            cout << "Q. Quit" << endl;
            cin >> choice;

            switch (choice)
            {
            case '1':
                loggedInAccount = login();
                break;
            case '2':
                createUser();
                break;
            case '3':
                createSeller();
                break;
            case '4':
                if (loggedInAccount && loggedInAccount->getAccountType() == "User")
                {
                    double amount;
                    cout << "-----------------------------------------------------------" << endl;

                    cout << "Enter amount to update balance: ";
                    cin >> amount;
                    static_cast<CustomerAccount *>(loggedInAccount)->updateBalance(amount);
                    cout << "Balance updated successfully." << endl;
                }
                else
                {
                    cout << "You need to be logged in as a user to update balance." << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
                break;
            case '5':
                if (loggedInAccount && loggedInAccount->getAccountType() == "Seller")
                {
                    static_cast<MerchantAccount *>(loggedInAccount)->viewUsersWithBalances(accounts);
                }
                else
                {
                    cout << "You need to be logged in as a seller to view users with balances." << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
                break;
            case '6':
            {
                cout << "_____________________________________________________" << endl;
                inventory.printAllProducts();
                if (loggedInAccount && loggedInAccount->getAccountType() == "User")
                {
                    double total = 0;
                    char choice;
                    do
                    {
                        int id;
                        cout << "Enter product id: ";
                        cin >> id;
                        Product *product = inventory.findProduct(id);
                        int quantity;
                        if (!product)
                        {
                            cout << "Product not found." << endl;
                            cout << "-----------------------------------------------------------" << endl;
                            continue;
                        }
                        cout << "Enter quantity: ";
                        cin >> quantity;
                        while (quantity <= 0 || quantity > product->getQuantity())
                        {
                            cout << "Enter quantity in the range of 1 to " << product->getQuantity() << ": (_Enter Q to quit_)\n";
                            cin >> quantity;
                        }

                        total += product->getPrice() * quantity;

                        if (loggedInAccount->getBalance() < total) // When user has insufficient balance
                        {
                            cout << "Insufficient Balance! Retry" << endl;
                            cout << "-----------------------------------------------------------" << endl;
                            this->run();
                        }
                        cout << "Do you want to add more products to cart? (Y/N): ";
                        product->setQuantity(product->getQuantity() - quantity); // updating the inventory product quantity
                        product->addSales(quantity);                             // updating the sales of the product
                        cin >> choice;
                    } while (choice == 'Y' || choice == 'y');
                    cout << "Total amount: ₹" << total << endl
                         << "Transaction Completed!" << endl;
                    if (total > 0)
                    {
                        static_cast<CustomerAccount *>(loggedInAccount)->updateBalance(-total);
                        loggedInAccount->expenditure += total;
                    }
                    inventory.saveInventoryToFile("inventory.csv");
                }
                else
                {
                    cout << "You need to be logged in as a user to make a purchase." << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
                break;
            }

            case '7':
                stockAlert();
                break;

            case '8':
            { // CAN't do variable declaration in switch case
                cout << "-----------------------------------------------------------" << endl;
                cout << "\nList of highest spending users in descending order:" << endl;

                // priority_queue<Account*, vector<Account*>, comparator> pq; //ANCHOR - This uses class or functor
                priority_queue<Account *, vector<Account *>, decltype(compareAccounts) *> pq(compareAccounts); // this uses function pointer
                for (const auto &acc : accounts)
                {
                    pq.push(acc);
                }
                int i = 9;
                cout << "Top 10 highest spending users:" << endl;

                while (i && !pq.empty())
                {
                    Account *acc = pq.top();
                    pq.pop();
                    cout << "Username: " << acc->getUsername() << ", Expenditure: " << acc->expenditure << endl;
                    i--;
                }
                cout << "-----------------------------------------------------------" << endl;
                break;
            }

            case 'Q':
                cout << "Goodbye!" << endl;
                saveToFile();
                return;
            default:
                cout << "Invalid Choice. Please Try again" << endl;
                break;
            }
        } while (true);
    }

bool compareAccounts(const Account *a1, const Account *a2)
{
    return a1->expenditure < a2->expenditure;
}