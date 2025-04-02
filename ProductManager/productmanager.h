#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

const string PRODUCTS_FILE = "products.txt"; // Store products in this file
const string USERS_FILE = "./Data/User/Userdata.txt"; // Store users in this file

class ProductManager {
public:
    // Load products from the product file
    vector<pair<string, string>> loadProducts() {
        ifstream file(PRODUCTS_FILE);
        vector<pair<string, string>> products;
        string line, name, price;

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, '\t');  // Extract product name
            getline(ss, price);       // Extract product price
            products.push_back({name, price}); // Store product as a pair
        }
        return products;
    }

    // View the list of products
    void viewProducts() {
        vector<pair<string, string>> products = loadProducts();
        cout << "------ Available Products ------" << endl;
        for (const auto& product : products) {
            cout << left << setw(20) << product.first << "\t" << product.second << endl;
        }
        cout << "------------------------------" << endl;
    }

    // Add product to the products file
    void addProduct(const string& name, const string& price) {
        ofstream file(PRODUCTS_FILE, ios::app);
        file << name << "\t" << price << endl;
        cout << "Product added successfully." << endl;
    }

    // Remove product from the products file
    void removeProduct(const string& name) {
        vector<pair<string, string>> products = loadProducts();
        ofstream file(PRODUCTS_FILE);
        
        bool found = false;
        for (const auto& product : products) {
            if (product.first != name) {
                file << product.first << "\t" << product.second << endl;
            } else {
                found = true;
            }
        }

        if (found) {
            cout << "Product removed successfully." << endl;
        } else {
            cout << "Product not found." << endl;
        }
    }

    // Create a bill and store it in a text file
    void createBill(const string& username, vector<pair<string, int>>& cart, vector<pair<string, string>>& products) {
        time_t now = time(0);
        char* dt = ctime(&now);
        // Remove spaces and newline from the date string to make it a valid filename
        string filenameTime = string(dt);
        filenameTime.erase(remove(filenameTime.begin(), filenameTime.end(), ' '), filenameTime.end());
        filenameTime.erase(remove(filenameTime.begin(), filenameTime.end(), '\n'), filenameTime.end());

        stringstream filename;
        filename << "./Bills/" << username << "_" << filenameTime << ".txt";
        
        ofstream bill(filename.str());

        double totalAmount = 0.0;
        bill << "------ BILL RECEIPT ------" << endl;
        bill << "User: " << username << endl;
        bill << "Date & Time: " << dt;
        bill << "---------------------------------------" << endl;
        bill << left << setw(20) << "Product" << setw(10) << "Qty" << setw(10) << "Price" << setw(10) << "Total" << endl;
        bill << "---------------------------------------" << endl;

        for (const auto& item : cart) {
            string productName = item.first;
            int quantity = item.second;

            double price = 0.0;
            for (const auto& product : products) {
                if (product.first == productName) {
                    price = stod(product.second);  // Convert price string to double
                    break;
                }
            }

            double totalPriceForItem = price * quantity;
            totalAmount += totalPriceForItem;

            bill << left << setw(20) << productName
                 << setw(10) << quantity
                 << setw(10) << price
                 << setw(10) << totalPriceForItem << endl;
        }

        bill << "---------------------------------------" << endl;
        bill << "Total Amount: " << totalAmount << endl;
        bill << "---------------------------------------" << endl;

        cout << "Bill generated successfully: " << filename.str() << endl;
    }
};

class Admin : public ProductManager {
public:
    void manageUsers() {
        cout << "Manage users function (to be implemented)" << endl;
    }

    void addEmployee(const string& username, const string& password) {
        ofstream file("./Data/Employer/employ.txt", ios::app);
        file << username << " " << password << endl;
        cout << "Employee added successfully." << endl;
    }

    void removeEmployee(const string& username) {
        // Logic for removing an employee (similar to removing product)
    }
};

class Employee : public ProductManager {
};

class User : public ProductManager {
public:
    void orderProduct(vector<pair<string, int>>& cart) {
        string productName;
        int quantity;
        cout << "Enter product name: ";
        cin >> productName;
        cout << "Enter quantity: ";
        cin >> quantity;
        cart.push_back({productName, quantity});  // Add to the cart
    }

    void payBill(vector<pair<string, int>>& cart) {
        vector<pair<string, string>> products = loadProducts();
        string username = "UserName";  // Get the actual username

        createBill(username, cart, products);
    }
};

#endif
