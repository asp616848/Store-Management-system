#include "inventory.hpp" // Include the header file for the Inventory class

// Method to print all products in the inventory
void Inventory::printAllProducts() const {

    // Check if the inventory is empty
    if(products.empty()) {
        std::cout << "No products available. (inventory.csv must be empty)" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        return;
    }

    // Iterate over each product and print its details
    for (const auto &product : products) {
        std::cout << "ID : " << product.getId() << std::endl;
        std::cout << "Name : " << product.getName() << std::endl;
        std::cout << "Category : " << product.getCategory() << std::endl;
        std::cout << "Price : ₹" << product.getPrice() << std::endl;
        std::cout << "Quantity : " << product.getQuantity() << std::endl;
    }
}

// Method to add a product to the inventory
void Inventory::addProduct(Product product) {

    // Check if the product ID already exists using binary search
    Product *found = findProduct(product.getId());
    if (found != nullptr) {
        std::cout << "Id already exists." << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
    } else {

        // Insert the product and maintain sorted order
        products.push_back(product);
        std::cout << "Product added successfully." << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
    }
}

// Method to retrieve a copy of the products and return a vector containing all the products
std::vector<Product> Inventory::getProducts() const {
    return products;
}

// Method to remove a product from inventory
void Inventory::removeProduct(int id) {
    Product *found = findProduct(id);
    if (found != nullptr) {
        auto index = found - &products[0]; // Calculate the index of the found product 
                                           //Auto deduces type from expression, over here it's assigning int
        products.erase(products.begin() + index); // Erases the product from 'products' vector at calculated index
                                                  //Uses products.begin() to get the iterator to the first element
        std::cout << "Product removed successfully." << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
    } else {
        std::cout << "Id does not exist" << std::endl;
    }
}

// Function to find a product by its ID
Product *Inventory::findProduct(int id) {
    int low = 0;
    int high = products.size() - 1;
    while (low <= high) {   // Perform binary search until the low index is less than or equal to the high index
        int mid = low + (high - low) / 2;
        if (products[mid].getId() == id) {
            return &products[mid]; // Return a pointer to the product found
        } else if (products[mid].getId() < id) {
            low = mid + 1;  // Update the low index to search the right half of the current range
        } else {
            high = mid - 1; // Update the high index to search the left half of the current range
        }
    }
    return nullptr; // If the loop exits without finding the target ID, 
                    //return nullptr indicating that the product was not found
}

// Updates product details if found by ID
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

// Saves inventory data to a file
void Inventory::saveInventoryToFile(std::string filename) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::trunc);
    for (const auto &p : products) {
        file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << "," << p.getTotalSales() << std::endl;
    }
    file.close();
}

// Loads inventory data from a file
void Inventory::loadInventoryFromFile(std::string filename) {
    std::ifstream file; // Declare an input file stream object
    file.open(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line); // Create a stringstream object to parse the line
            std::string idStr, name, category, priceStr, quantityStr, salesStr; // Declare string variables to store data fields
                                                                                // Extract data fields from the stringstream separated by commas
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, salesStr, ',');

            // Convert string data fields to their respective data types
            int id = std::stoi(idStr); //stoi = string to int
            double price = std::stod(priceStr); //stod = string to double
            int quantity = std::stoi(quantityStr);
            int sales = std::stoi(salesStr);
            // Create a Product object using the extracted data
            Product p(id, name, category, price, quantity, sales);
            // Add the Product object to the products vector
            products.push_back(p);
        }
        file.close();
    } else {
        std::cout << "Error: Could not open file " << filename << std::endl;
    }
}
