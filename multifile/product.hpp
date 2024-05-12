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
    bool operator<(const Product &other) const;

    int getTotalSales() const;

    void addSales(int quantity);

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
