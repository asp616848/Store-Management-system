#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<queue>
using namespace std;

class Account {
protected:
    string username;
    string password;
public:
    static bool compareByExpenditure(const Account* a, const Account* b) {
        return a->expenditure < b->expenditure; // Use < for descending order
    }
    double expenditure =0;
    string getUsername() const {
        return username;
    }
    string getPassword() const {
        return password;
    }
    Account(const string& username, const string& password, int expenditure = 0) : username(username), password(password), expenditure(expenditure) {}
    virtual bool authenticate(const string& inputUsername, const string& inputPassword) const 
    {
        return username == inputUsername && password == inputPassword;
    }
    virtual double getBalance() const {
        return 0;
    }
    virtual string getType() const = 0;
};

class UserAccount : public Account {
    double balance;
public:
    UserAccount(const string& username, const string& password, int expenditure = 0, int balance) : Account(username, password, expenditure) {
        this->balance = balance;
    }
    string getType() const override {
        return "User";
    }
    double getBalance() const {
        return balance;
    }
    void updateBalance(double amount) {
        balance += amount;
    }
};

class SellerAccount : public Account {
public:
    SellerAccount(const string& username, const string& password) : Account(username, password) {}

    string getType() const override {
        return "Seller";
    }
    void viewUsersWithBalances(const vector<Account*>& accounts) {
        cout << "Users with balances:" << endl;
        for (const auto& acc : accounts) {
            if (dynamic_cast<UserAccount*>(acc)) {
                cout << "Username: " << username << ", Balance: " << static_cast<UserAccount*>(acc)->getBalance() << endl;
            }
        }
    }
};


class Product
{
    private:
        int id;
        string name;
        string category;
        double price;
        int quantity;
        int sales;
    public:

        int getSales() const{
            return sales;
        }
        void addSales(int quantity)
        {
            this->sales+=quantity;
        }
        Product(int id, string name, string category, double price, int quantity, int sales=0)
        {
            this->id=id;
            this->name=name;
            this->category=category;
            this->price=price;
            this->quantity=quantity;
            this->sales=sales;
        }

        int getId() const{
            return id;
        }

        void setId(int id){
            this->id=id;
        }

        string getName() const{
            return name;
        }

        void setName(string name){
            this->name=name;
        }

        string getCategory() const{
            return category;
        }

        void setCategory(string category){
            this->category=category;
        }

        double getPrice() const{
            return price;
        }

        void setPrice(double price){
            this->price=price;
        }

        int getQuantity() const{
            return quantity;
        }

        void setQuantity(int quantity){
            this->quantity=quantity;
        }
};

class Inventory
{
    private:
        vector<Product> products;
    public:
        void printAllProducts() const{
            for(auto i=products.begin();i!=products.end();i++)
            {
                cout<<"ID : "<<i->getId()<<endl;
                cout<<"Name : "<<i->getName()<<endl;
                cout<<"Category : "<<i->getCategory()<<endl;
                cout<<"Price : $"<<i->getPrice()<<endl;
                cout<<"Quantity : "<<i->getQuantity()<<endl;
            }
        }
        void addProduct(Product product)
        {
            bool found = false;
            for (auto& p : products)
            {
                if (p.getId() == product.getId())
                {
                    cout << "Id already Exist."<< endl;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                products.push_back(product);
                cout << "Product added successfully." << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
        }            

        vector<Product> getProducts() const // return the products but not modify them
        {
            return products;
        }
        void removeProduct(int id)
        {
            bool found = false;
            for (auto i = products.begin(); i != products.end(); i++)
            {
                if (i->getId() == id)
                {
                    products.erase(i);
                    found = true;
                    cout << "Product removed successfully." << endl;        
                    cout << "-----------------------------------------------------------" <<endl;
                    break;
                }
            }
            if (!found)
            {
                cout << "Id does not exist" << endl;
            }
        }

        Product* findProduct(int id)
        {
            cout << "FINDING!" << endl;
            for(auto i=products.begin();i!=products.end();i++)
            {
                if(i->getId()==id)
                {
                    return &(*i);
                }
            }
            return nullptr;
        }

        void updateProduct(int id, string name, string category, double price, int quantity)
        {
            bool found = false;
            for (auto i = products.begin(); i != products.end(); i++)
            {
                if (i->getId() == id)
                {
                    i->setName(name);
                    i->setCategory(category);
                    i->setPrice(price);
                    i->setQuantity(quantity);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "ID does not exist." << endl;
            }
        }        

        void printProduct() const{
            for(auto i=products.begin();i!=products.end();i++)
            {
                cout<<"ID : "<<i->getId()<<endl;
                cout<<"Name : "<<i->getName()<<endl;
                cout<<"Category : "<<i->getCategory()<<endl;
                cout<<"Price : $"<<i->getPrice()<<endl;
                cout<<"Quantity : "<<i->getQuantity()<<endl;
            }
        }

        void saveInventoryToFile(string filename) 
        {
            ofstream file;
            file.open(filename, ios::out | ios::trunc);
            for (int i = 0; i < products.size(); i++) 
            {
                Product p = products[i];
                file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity()<< ","<< p.getSales() << endl;
            }
            file.close();
        }

        void loadInventoryFromFile(string filename) 
        {
            ifstream file;
            file.open(filename);

            if (file.is_open()) 
            {
                string line;
                while (getline(file, line)) 
                {
                    stringstream ss(line);
                    string idStr, name, category, priceStr, quantityStr, salesStr;
                    getline(ss, idStr, ',');
                    getline(ss, name, ',');
                    getline(ss, category, ',');
                    getline(ss, priceStr, ',');
                    getline(ss, quantityStr, ',');
                    getline(ss, salesStr, ',');

                    int id = stoi(idStr);
                    double price = stod(priceStr);
                    int quantity = stoi(quantityStr);
                    int sales = stoi(salesStr);

                    Product p(id, name, category, price, quantity, sales);
                    products.push_back(p);
                }

                file.close();
            } else {
                cout << "Error: Could not open file " << filename << endl;
            }
        }
};

class Store {
private:
    Inventory inventory;
    vector<Account*> accounts;

    Account* login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (Account* acc : accounts) {
            if (acc->authenticate(username, password)) {
                cout << "Login successful. Welcome, " << username << " (" << acc->getType() << ")" << endl;
                return acc;
            }
        }

        cout << "Login failed. Invalid username or password." << endl;
        return nullptr;
    }

    void createUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        accounts.push_back(new UserAccount(username, password));
        cout << "User account created successfully." << endl;
    }

    void stockAlert() // TODO
    {
        for(auto i=inventory.getProducts().begin();i!=inventory.getProducts().end();i++)
        {
            if(i->getQuantity() <= 4)
            {
                cout<<"Stock Empty Alert! for product : "<< i->getName() << "With product quantity" << i->getQuantity() <<endl;
            }
        }
        cout << "Stock Empty Alert!" << endl;
    }
    void createSeller() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        accounts.push_back(new SellerAccount(username, password));
        cout << "Seller account created successfully." << endl;
    }
    void saveToFile() {
        ofstream file;
        file.open("users.csv");

        for (const auto& acc : accounts) {
            file << acc->getType() << "," << acc->getUsername()<< "," << acc->getPassword()<< "," << acc->expenditure << "," << acc->getBalance() << endl;
        }
        file.close();
    }
    void loadFromFile() {
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


                if (type == "User") {
                    accounts.push_back(new UserAccount(username, password, expenditure, balance));
                } else if (type == "Seller") {
                    accounts.push_back(new SellerAccount(username, password));
                }
            }

            file.close();
        } else {
            cout << "Error: Could not open file accounts.txt" << endl;
        }
    }

public:
    Inventory getInventory() const {
        return inventory;
    }
    Store() {
        // create some default accounts for testing, removed from here
        inventory.loadInventoryFromFile("inventory.csv");
    }
    void Load()
    {
        loadFromFile();
    }

    void run() {
        char choice;
        Account* loggedInAccount = nullptr;
        do {
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

            switch (choice) {
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
                if (loggedInAccount && loggedInAccount->getType() == "User") {
                    double amount;
                    cout << "Enter amount to update balance: ";
                    cin >> amount;
                    static_cast<UserAccount*>(loggedInAccount)->updateBalance(amount);
                    cout << "Balance updated successfully." << endl;
                } else {
                    cout << "You need to be logged in as a user to update balance." << endl;
                }
                break;
            case '5':
                if (loggedInAccount && loggedInAccount->getType() == "Seller") {
                    static_cast<SellerAccount*>(loggedInAccount)->viewUsersWithBalances(accounts);
                } else {
                    cout << "You need to be logged in as a seller to view users with balances." << endl;
                }
                break;
            case '6':{
                cout<< "_____________________________________________________" << endl;
                inventory.printAllProducts();
                if (loggedInAccount && loggedInAccount->getType() == "User") {
                    double total = 0;
                    char choice;
                    do {
                        int id;
                        cout << "Enter product id: ";
                        cin >> id;
                        Product* product = inventory.findProduct(id);

                        int quantity;
                        cout << "Enter quantity: ";
                        cin >> quantity;
                        while(quantity<=0 || quantity > product->getQuantity())
                        {
                            cout << "Enter quantity in the range of 1 to " << product->getQuantity() << ":\n";
                            cin >> quantity;
                        }
                        if (product->getQuantity() >= quantity) {
                            total += product->getPrice() * quantity;
                            cout << "Product added to cart. Total: $" << total << endl;
                        } else {
                            cout << "Product not found." << endl;
                        }
                        cout << "Do you want to add more products to cart? (Y/N): ";
                        product->setQuantity(product->getQuantity()-quantity);  //updating the inventory product quantity
                        product->addSales(quantity); //updating the sales of the product
                        cin >> choice;
                    } while (choice == 'Y' || choice == 'y');
                    cout << "Total amount: $" << total << endl<< "Transaction Completed!" << endl;
                    if (total > 0) {
                        static_cast<UserAccount*>(loggedInAccount)->updateBalance(-total);
                        loggedInAccount->expenditure += total;
                    }
                    inventory.saveInventoryToFile("inventory.csv");
                } else {
                    cout << "You need to be logged in as a user to make a purchase." << endl;
                }
                break;}

            case '7':
                stockAlert();
                break;

            case '8': { // CAN't do variable declaration in switch case
                cout << "\nList of highest spending users in descending order:" << endl;
                auto compare = [](const Account* a1, const Account* a2) { // Using pointers
                    return a1->expenditure < a2->expenditure;
                };
                priority_queue<Account*, vector<Account*>, decltype(compare)> pq(compare);
                for (const auto& acc : accounts) {
                    pq.push(acc);
                }
                int i = 9;
                cout << "Top 10 highest spending users:" << endl;

                while (i && !pq.empty()) {
                    Account* acc = pq.top();
                    pq.pop();
                    cout << "Username: " << acc->getUsername() << ", Expenditure: " << acc->expenditure << endl;
                    i--;
                }
                cout << "-----------------------------------------------------------" <<endl;
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
};

int main() {
    int option;
    Store store; // solved the instantiation problem
    store.Load();
    Inventory inventory = store.getInventory();
    cout << "Enter 1 if you want to enter accounts and 0 if you want to enter inventory: ";
    cin >> option;
    if(option==1)
    {
    store.run();
    }
    else
    {
    cout << "-----------------------------------------------------------" <<endl;
    cout << "---------------Inventory Management System ----------------" <<endl;   
    cout << "-----------------------------------------------------------" <<endl;
    cout << "------------------------- Welcome! ------------------------" <<endl;
    cout << "-----------------------------------------------------------" <<endl;
    char choice;
    do {
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
        cout << "Q. Quit, And go to Accounts Screen" << endl;
        cin >> choice;

        switch (choice) {
        case '1': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: $ ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }

        case '2': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }

        case '3': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            Product* product = inventory.findProduct(id);
            if (product) {
                cout << "Name: " << product->getName() << endl;
                cout << "Category: " << product->getCategory() << endl;
                cout << "Price: $ " << product->getPrice() << endl;
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
            cout << "Enter the product id: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin >> name;
            cout << "Enter new product category: ";
            cin >> category;
            cout << "Enter new product price: $ ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "Product updated successfully." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
        case '5': {
            inventory.printProduct();
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
                auto compare = [](const Product& p1, const Product& p2) { // Using pointers
                    return p1.getSales()*p1.getPrice() < p2.getSales()*p1.getPrice();
                };
                priority_queue<Product, vector<Product>, decltype(compare)> pq(compare);
                for (const auto& p : inventory.getProducts()) {
                    pq.push(p);
                }
                int i = 9;
                cout << "Top 10 highest selling products:" << endl;
                while (i) {
                    Product p = pq.top();
                    pq.pop();
                    cout << "Product Name: " << p.getName() << ", Sales: " << p.getSales() << endl;
                    i--;
                }
                break;
            }

        case 'Q':
            cout << "Goodbye!" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            return 0;
        case 'q':
            cout << "Welcome to Accounts!" << endl;
            store.run();
            cout << "-----------------------------------------------------------" <<endl;
            return 0;
        default:
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
    } while (true);
    }
    return 0;
}