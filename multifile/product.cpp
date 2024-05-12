#include "product.hpp"

bool Product::operator<(const Product &other) const {
    return sales * price < other.sales * other.price;
}

int Product::getTotalSales() const {
    return sales;
}

void Product::addSales(int quantity) {
    this->sales += quantity;
}

Product::Product(int id, std::string name, std::string category, double price, int quantity, int sales)
    : id(id), name(name), category(category), price(price), quantity(quantity), sales(sales) {}

int Product::getId() const {
    return id;
}

void Product::setId(int id) {
    this->id = id;
}

std::string Product::getName() const {
    return name;
}

void Product::setName(std::string name) {
    this->name = name;
}

std::string Product::getCategory() const {
    return category;
}

void Product::setCategory(std::string category) {
    this->category = category;
}

double Product::getPrice() const {
    return price;
}

void Product::setPrice(double price) {
    this->price = price;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}
