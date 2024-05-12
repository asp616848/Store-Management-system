#include "store.hpp"
#include <iostream>
#include <queue>
using namespace std;
bool compareAccounts(const Account *a1, const Account *a2)
{
    return a1->expenditure < a2->expenditure;
}
void Store::encrypt(string &str) {
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

void Store::decrypt(string &str) {
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
    string username, password;
    cin.ignore();
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    for (Account *acc : accounts) {
        if (acc->authenticate(username, password)) {
            cout << "Login successful. Welcome, " << username << " (" << acc->getAccountType() << ")" << endl;
            return acc;
        }
    }

    cout << "Login failed. Invalid username or password." << endl;
    return nullptr;
}

void Store::createUser() {

    string username, password;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    accounts.push_back(new CustomerAccount(username, password));
    cout << "User account created successfully." << endl;
}

void Store::stockAlert() {
    bool alert = false;
    for (const auto &product : inventory.getProducts()) {
        if (product.getQuantity() <= 4) {
            cout << "Stock Empty Alert! for product: " << product.getName() << " with product quantity: " << product.getQuantity() << endl;
            alert = true;
        }
    }
    if (!alert) {
        cout << "No products with low stock." << endl;
    }
}

void Store::createSeller() {
    string username, password;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    accounts.push_back(new MerchantAccount(username, password));
    cout << "Seller account created successfully." << endl;
}

void Store::saveToFile() {
    ofstream file;
    file.open("users.csv");

    for (const auto &acc : accounts) {
        string a = acc->getAccountType();
        string b = acc->getUsername();
        string c = acc->getPassword();
        double d = acc->expenditure;
        double e = acc->getBalance();

        encrypt(a);
        encrypt(b);
        encrypt(c);

        d = d + 1029;
        e = e + 1029;

        file << a << "," << b << "," << c << "," << d << "," << e << endl;
    }
    file.close();
}

void Store::loadFromFile() {
    ifstream file;
    file.open("users.csv");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type, username, password, exp, bal;
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
        if(accounts.size() == 0){
            cout << "No accounts found. (account.csv must be empty)" << endl;
        }
        file.close();
    } else {
        cout << "Error: Could not open file accounts.txt" << endl;
    }
}

void Store::printAccounts() {
    for (Account *each : accounts) {
        cout << each->getUsername() << endl;
        cout << each->getPassword() << endl;
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
void Store::HighestSpendingUsers() {
    // CAN't do variable declaration in switch case
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
}
void Store::MakeAPurchase(){
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
                cout << "Insufficient Balance! kindly add funds and retry" << endl;
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
}

void Store::run() {
    char choice;
        do
        {
            cout<< "Press ctrl + c to exit the program"<<endl;
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
            cout << "Q. Quit and redirect to Inventory" << endl;
            
            cin >> choice;

            switch (choice)
            {
            case '1':
                loggedInAccount = login();
                cout << "-----------------------------------------------------------" <<endl;

                break;
            case '2':
                createUser();
                saveToFile();
                cout << "-----------------------------------------------------------" <<endl;
                
                break;
            case '3':
                createSeller();
                cout << "-----------------------------------------------------------" <<endl;

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
                    cout << "-----------------------------------------------------------" <<endl;

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
                MakeAPurchase();
                break;
            }

            case '7':
                stockAlert();
                break;

            case '8':
            {
                HighestSpendingUsers();
                break;
            }

            case 'Q':
                cout << "Goodbye!" << endl;
                saveToFile();
                runInv();
                return;
            default:
                cout << "Invalid Choice. Please Try again" << endl;
                break;
            }
        } 
        while (true);
}
void Store::runInv(){
    cout << "-----------------------------------------------------------" <<endl;
    cout << "---------------Inventory Management System ----------------" <<endl;  
    cout << "------------------------- Welcome! ------------------------" <<endl;
    cout << "-----------------------------------------------------------" <<endl;
    cout<< "Press ctrl + c to exit the program"<<endl;

    
    char choice;
    do {
        cout << "-----------------------------------------------------------" <<endl;

        cout << "Please choose an option:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Find a product" << endl;
        cout << "4. Update a product" << endl;
        cout << "5. View all products" << endl;
        cout << "6. Save inventory to file" << endl;
        cout << "7. Load Inventory from file" << endl;
        cout << "8. Get most selling products" << endl;
        cout << "Q. Quit, and terminate" << endl;
        cout << "q. Quit, And go to Accounts Screen" << endl;
        cin >> choice;

        switch (choice) {
        case '1': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "-----------------------------------------------------------" <<endl;
            cout << "Enter ID: ";

            cin >> id;
            cout << "Enter product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter product category: ";
            getline(cin, category);
            cout << "Enter product price: ₹ ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            inventory.saveInventoryToFile("inventory.csv");
            break;
        }

        case '2': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            inventory.removeProduct(id);
            inventory.saveInventoryToFile("inventory.csv");
            break;
        }

        case '3': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            Product* product = inventory.findProduct(id);
            if (product) {
                cout << "-----------------------------------------------------------" <<endl;
                cout << "Name: " << product->getName() << endl;
                cout << "Category: " << product->getCategory() << endl;
                cout << "Price: ₹ " << product->getPrice() << endl;
                cout << "Quantity: " << product->getQuantity() << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
            else {
                cout << "Product not found." << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
            break;
        }

        case '4': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "-----------------------------------------------------------" <<endl;
            cout << "Enter the product id: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new product category: ";
            cin.ignore();
            getline(cin, category);
            cout << "Enter new product price: ₹ ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "Product updated successfully." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
        case '5': {
            inventory.printAllProducts();
            break;
        }
        case '6': {
            inventory.saveInventoryToFile("inventory.csv");
            cout << "Inventory saved to file." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
        case '7': {
            inventory.loadInventoryFromFile("inventory.csv");
            cout << "Inventory loaded from file." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
        case '8': { // CAN't do variable declaration in switch case
                
                priority_queue<Product> pq;
                for (const auto& p : inventory.getProducts()) {
                    pq.push(p);
                }
                int i = 9;
                cout << "-----------------------------------------------------------" <<endl;

                cout << "Top 10 highest selling products:" << endl;
                while (i) {
                    Product p = pq.top();
                    pq.pop();
                    cout << "Product Name: " << p.getName() << ", Sales: " << p.getTotalSales() << endl;
                    i--;
                }
                break;
            }

        case 'Q':
            cout << "Goodbye!" << endl;
            inventory.saveInventoryToFile("inventory.csv");
            cout << "-----------------------------------------------------------" <<endl;
        case 'q':
            cout << "Welcome to Accounts!" << endl;
            inventory.saveInventoryToFile("inventory.csv");
            run();
            cout << "-----------------------------------------------------------" <<endl;
        default:
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
    } while (true);
}