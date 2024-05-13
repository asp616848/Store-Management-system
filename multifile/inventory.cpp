#include "inventory.hpp"

void Inventory::printAllProducts() const {
    if(products.empty()) {
        cout << "No products available. (inventory.csv must be empty)" << endl;
        cout << "-----------------------------------------------------------" << endl;
        return;
    }
    for (const auto &product : products) {
        cout << "ID : " << product.getId() << endl;
        cout << "Name : " << product.getName() << endl;
        cout << "Category : " << product.getCategory() << endl;
        cout << "Price : ₹" << product.getPrice() << endl;
        cout << "Quantity : " << product.getQuantity() << endl;
    }
}

void Inventory::addProduct(Product product) {
    Product *found = findProduct(product.getId());
    if (found != nullptr) {
        cout << "Id already exists." << endl;
        cout << "-----------------------------------------------------------" << endl;
    } else {
        products.push_back(product);
        cout << "Product added successfully." << endl;
        cout << "-----------------------------------------------------------" << endl;
    }
}

vector<Product> Inventory::getProducts() const {
    return products;
}

void Inventory::removeProduct(int id) {
    Product *found = findProduct(id);
    if (found != nullptr) {
        auto index = found - &products[0];
        products.erase(products.begin() + index);
        cout << "Product removed successfully." << endl;
        cout << "-----------------------------------------------------------" << endl;
    } else {
        cout << "Id does not exist" << endl;
    }
}

Product *Inventory::findProduct(int id) {
    int low = 0;
    int high = products.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (products[mid].getId() == id) {
            return &products[mid];
        } else if (products[mid].getId() < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return nullptr;
}

void Inventory::updateProduct(int id, string name, string category, double price, int quantity) {
    bool found = false;
    for (auto &product : products) {
        if (product.getId() == id) {
            product.setName(name);
            product.setCategory(category);
            product.setPrice(price);
            product.setQuantity(quantity);
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "ID does not exist." << endl;
    }
}

void Inventory::saveInventoryToFile(string filename) {
    ofstream file;
    file.open(filename, ios::out | ios::trunc);
    for (const auto &p : products) {
        file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << "," << p.getTotalSales() << endl;
    }
    file.close();
}

void Inventory::loadInventoryFromFile(string filename) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
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
