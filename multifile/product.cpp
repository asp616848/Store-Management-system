#include "product.hpp" // Include the header file for the Product class

// Overloaded less than operator to compare products based on total sales value
bool Product::operator < (const Product &other) const { return sales * price < other.sales * other.price; }

// Method to get the total sales of a product
int Product::getTotalSales() const { return sales; }

// Method to add sales to a product
void Product::addSales(int quantity) { this->sales += quantity; }

// Constructor to initialize a Product object with provided values
Product::Product(int id, std::string name, std::string category, double price, int quantity, int sales)
    : id(id), name(name), category(category), price(price), quantity(quantity), sales(sales) {}

int Product::getId() const { return id; } // Return the ID of the product

void Product::setId(int id) { this->id = id; } // Set the ID of the product to the provided value

std::string Product::getName() const { return name; } // Return the name of the product

void Product::setName(std::string name) { this->name = name; }

std::string Product::getCategory() const { return category; }

void Product::setCategory(std::string category) { this->category = category; }

double Product::getPrice() const { return price; }

void Product::setPrice(double price) { this->price = price; }

int Product::getQuantity() const { return quantity; }

void Product::setQuantity(int quantity) { this->quantity = quantity; }
