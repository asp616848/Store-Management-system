#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;
    int sales;

public:

    // Overloaded less than operator to compare products based on total sales value
    bool operator<(const Product &other) const;

    // Method to get the total sales of a product
    int getTotalSales() const;

    // Method to add sales to a product
    void addSales(int quantity);

    // Constructor to initialize a Product object with provided values
    Product(int id, std::string name, std::string category, double price, int quantity, int sales = 0);

    int getId() const;
    void setId(int id);
    std::string getName() const;
    void setName(std::string name);
    std::string getCategory() const;
    void setCategory(std::string category);
    double getPrice() const;
    void setPrice(double price);
    int getQuantity() const;
    void setQuantity(int quantity);
};

#endif // PRODUCT_HPP
