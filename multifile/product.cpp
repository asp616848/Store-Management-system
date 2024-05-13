#include "product.hpp" // Include the header file for the Product class

// Overloaded less than operator to compare products based on total sales value
bool Product::operator < (const Product &other) const { return sales * price < other.sales * other.price; }

// Method to get the total sales of a product
int Product::getTotalSales() const { return sales; }

// Method to add sales to a product
void Product::addSales(int quantity) { this->sales += quantity; }

// Constructor to initialize a Product object with provided values
Product::Product(int id, string name, string category, double price, int quantity, int sales)
    : id(id), name(name), category(category), price(price), quantity(quantity), sales(sales) {}

// Getter method to retrieve the ID of a product
int Product::getId() const { return id; } // Return the ID of the product

// Setter method to update the ID of a product
void Product::setId(int id) { this->id = id; } // Set the ID of the product to the provided value

// Getter method to retrieve the name of a product
string Product::getName() const { return name; } // Return the name of the product

// Setter method to update the name of a product
void Product::setName(string name) { this->name = name; }

// Getter method to retrieve the category of a product
string Product::getCategory() const { return category; }

// Setter method to update the category of a product
void Product::setCategory(string category) { this->category = category; }

// Getter method to retrieve the price of a product
double Product::getPrice() const { return price; }

// Setter method to update the price of a product
void Product::setPrice(double price) { this->price = price; }

// Getter method to retrieve the quantity of a product
int Product::getQuantity() const { return quantity; }

// Setter method to update the quantity of a product
void Product::setQuantity(int quantity) { this->quantity = quantity; }
