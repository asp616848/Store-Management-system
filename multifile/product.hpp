#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;
    int sales;

public:
    bool operator<(const Product &other) const;

    int getTotalSales() const;

    void addSales(int quantity);

    Product(int id, string name, string category, double price, int quantity, int sales = 0);

    int getId() const;
    void setId(int id);
    string getName() const;
    void setName(string name);
    string getCategory() const;
    void setCategory(string category);
    double getPrice() const;
    void setPrice(double price);
    int getQuantity() const;
    void setQuantity(int quantity);
};

#endif // PRODUCT_HPP
