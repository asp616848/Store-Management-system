#include "inventory.hpp" // Include the header file for the Inventory class

// Method to print all products in the inventory
void Inventory::printAllProducts() const {

    // Check if the inventory is empty
    if(products.empty()) {
        cout << "No products available. (inventory.csv must be empty)" << endl;
        cout << "-----------------------------------------------------------" << endl;
        return;
    }

    // Iterate over each product and print its details
    for (const auto &product : products) {
        cout << "ID : " << product.getId() << endl;
        cout << "Name : " << product.getName() << endl;
        cout << "Category : " << product.getCategory() << endl;
        cout << "Price : ₹" << product.getPrice() << endl;
        cout << "Quantity : " << product.getQuantity() << endl;
    }
}

// Method to add a product to the inventory
void Inventory::addProduct(Product product) {

    // Check if the product ID already exists using binary search
    Product *found = findProduct(product.getId());
    if (found != nullptr) {
        cout << "Id already exists." << endl;
        cout << "-----------------------------------------------------------" << endl;
    } else {
        
        // Insert the product and maintain sorted order
        products.push_back(product);
        cout << "Product added successfully." << endl;
        cout << "-----------------------------------------------------------" << endl;
    }
}

// Method to retrieve a copy of the products and return a vector containing all the products
vector<Product> Inventory::getProducts() const {
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
        cout << "Product removed successfully." << std::endl;
        cout << "-----------------------------------------------------------" << std::endl;
    } else {
        cout << "Id does not exist" << endl;
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

// Saves inventory data to a file
void Inventory::saveInventoryToFile(string filename) {
    ofstream file;
    file.open(filename, ios::out | ios::trunc);
    for (const auto &p : products) {
        file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << "," << p.getTotalSales() << endl;
    }
    file.close();
}

// Loads inventory data from a file
void Inventory::loadInventoryFromFile(string filename) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line); // Create a stringstream object to parse the line
            string idStr, name, category, priceStr, quantityStr, salesStr; // Declare string variables to store data fields
                                                                                // Extract data fields from the stringstream separated by commas
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, salesStr, ',');

            // Convert string data fields to their respective data types
            int id = stoi(idStr); //stoi = string to int
            double price = stod(priceStr); //stod = string to double
            int quantity = stoi(quantityStr);
            int sales = stoi(salesStr);
            // Create a Product object using the extracted data
            Product p(id, name, category, price, quantity, sales);
            // Add the Product object to the products vector
            products.push_back(p);
        }
        file.close();
    } else {
        cout << "Error: Could not open file " << filename << endl;
    }
}
