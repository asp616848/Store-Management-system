#include "inventory.hpp"

void Inventory::printAllProducts() const {
    if(products.empty()) {
        std::cout << "No products available. (inventory.csv must be empty)" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        return;
    }
    for (const auto &product : products) {
        std::cout << "ID : " << product.getId() << std::endl;
        std::cout << "Name : " << product.getName() << std::endl;
        std::cout << "Category : " << product.getCategory() << std::endl;
        std::cout << "Price : ₹" << product.getPrice() << std::endl;
        std::cout << "Quantity : " << product.getQuantity() << std::endl;
    }
}

void Inventory::addProduct(Product product) {
    Product *found = findProduct(product.getId());
    if (found != nullptr) {
        std::cout << "Id already exists." << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
    } else {
        products.push_back(product);
        std::cout << "Product added successfully." << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
    }
}

std::vector<Product> Inventory::getProducts() const {
    return products;
}

void Inventory::removeProduct(int id) {
    Product *found = findProduct(id);
    if (found != nullptr) {
        auto index = found - &products[0];
        products.erase(products.begin() + index);
        std::cout << "Product removed successfully." << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
    } else {
        std::cout << "Id does not exist" << std::endl;
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

void Inventory::updateProduct(int id, std::string name, std::string category, double price, int quantity) {
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
        std::cout << "ID does not exist." << std::endl;
    }
}

void Inventory::saveInventoryToFile(std::string filename) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::trunc);
    for (const auto &p : products) {
        file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << "," << p.getTotalSales() << std::endl;
    }
    file.close();
}

void Inventory::loadInventoryFromFile(std::string filename) {
    std::ifstream file;
    file.open(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name, category, priceStr, quantityStr, salesStr;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, salesStr, ',');
            int id = std::stoi(idStr);
            double price = std::stod(priceStr);
            int quantity = std::stoi(quantityStr);
            int sales = std::stoi(salesStr);
            Product p(id, name, category, price, quantity, sales);
            products.push_back(p);
        }
        file.close();
    } else {
        std::cout << "Error: Could not open file " << filename << std::endl;
    }
}
