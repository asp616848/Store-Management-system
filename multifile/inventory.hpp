#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "product.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Inventory {
private:
    std::vector<Product> products;

public:
    void printAllProducts() const;

    void addProduct(Product product);

    std::vector<Product> getProducts() const;

    void removeProduct(int id);

    Product *findProduct(int id);

    void updateProduct(int id, std::string name, std::string category, double price, int quantity);

    void saveInventoryToFile(std::string filename);

    void loadInventoryFromFile(std::string filename);
};

#endif // INVENTORY_HPP
