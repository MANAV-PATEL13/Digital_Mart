#ifndef PRODUCT1_H
#define PRODUCT1_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> // For formatted output

using namespace std;

double grandTotal = 0;
int id;

// Struct to store order details
struct OrderItem
{
    string productName;
    int quantity;
    int price;         // Price per unit
    double totalPrice; // Total price for this item (quantity * price)
};

class Product
{
public:
    vector<pair<string, int>> cart; // Stores Product Name & Price
    vector<OrderItem> order;        // Stores ordered products with quantity, price, and total price

    // Load products from file
    void loadProducts()
    {
        cart.clear(); // Clear previous data
        ifstream file("./ProductManager/product.txt");
        if (!file)
        {
            cout << "Error loading product file!" << endl;
            return;
        }
        string name;
        int price;
        while (file >> name >> price)
        {
            cart.push_back({name, price});
        }
        file.close();
    }

    // Display all products
    void viewproduct()
    {
        loadProducts(); // Load products from file

        if (cart.empty())
        {
            cout << "No products available!" << endl;
            return;
        }

        cout << BLUE << "\n--------- Available Products -------------\n";
        cout << left << setw(4) << "ID" << left << setw(30) << "Product Name" << left << setw(10) << "Price" << endl;
        cout << BLUE << "-------------------------------------------\n"
             << RESET;
        for (size_t i = 0; i < cart.size(); i++)
        {
            cout << setw(4) << (i + 1) << left << setw(30) << cart[i].first << left << setw(10) << cart[i].second << endl;
        }
        cout << BLUE << "-------------------------------------------\n"
             << RESET;
    }
};

class User : public Product
{
public:
    // Order product
    void Order()
    {
        int number, quantity;
        viewproduct(); // Show products before ordering

        cout << "Enter the number of the product: ";
        cin >> number;

        if (number < 1 || number > cart.size())
        { // Validate user input
            cout << "Invalid product number!" << endl;
            return;
        }

        cout << "Enter quantity: ";
        cin >> quantity;

        // Get the price for the selected product
        int price = cart[number - 1].second;

        // Create new order item
        OrderItem newItem;
        newItem.productName = cart[number - 1].first;
        newItem.quantity = quantity;
        newItem.price = price;
        newItem.totalPrice = quantity * price;

        grandTotal += newItem.totalPrice;

        // Add to order vector
        order.push_back(newItem);

        cout << "Product added to your order!" << endl;
    }

    // View the user's current order
    void Vieworder()
    {

        if (order.empty())
        {
            cout << "\nYour order is empty!" << endl;
            return;
        }

        cout << "\n----------- Your Current Order -----------\n";
        cout << left << setw(20) << "Product" << setw(10) << "Quantity"
             << setw(10) << "Price" << setw(15) << "Total" << endl;
        cout << "--------------------------------------------\n";

        double grandTotal = 0;
        for (const OrderItem &item : order)
        {
            cout << left << setw(20) << item.productName
                 << setw(10) << item.quantity
                 << setw(10) << item.price
                 << setw(15) << item.totalPrice << endl;
            grandTotal += item.totalPrice;
        }

        cout << "----------------------------------------\n";
        cout << "Grand Total: " << grandTotal << endl;
    }

    // Generate bill and save to file
    void generatebill(string username)
    {
        if (order.empty())
        {
            cout << "No items in order to generate bill!" << endl;
            return;
        }

        // Generate unique bill ID using compile-time macros (__TIME__ and __DATE__)
        string billId = __TIME__; // Time in HH:MM:SS format
        billId += "_";
        billId += __DATE__; // Date in Mmm DD YYYY format

        // Replace spaces and colons with underscores and hyphens
        for (char &c : billId)
        {
            if (c == ' ')
                c = '_'; // Replace space with underscore
            if (c == ':')
                c = '-'; // Replace colon with hyphen
        }

        billId = "_" + billId;

        // Read the last ID from the file (if it exists) or initialize to 1
        int id = 1;
        ifstream idFile("./Bills/id/id.txt");
        if (idFile)
        {
            idFile >> id; // Read the last used ID
            idFile.close();
        }

        // Increment the ID for the new bill
        id++;

        // Save the new ID back into the file
        ofstream idFileOut("./Bills/id/id.txt");
        if (idFileOut)
        {
            idFileOut << id; // Store the incremented ID
            idFileOut.close();
        }
        else
        {
            cout << "Error updating the ID file!" << endl;
            return;
        }

        // Create filename with bill ID and incremented ID
        string filename = "./Bills/bill_" + to_string(id) + billId + ".txt";

        // Create bills directory if it doesn't exist
        system("mkdir -p ./Bills");

        // Open file for writing
        ofstream billFile(filename);
        if (!billFile)
        {
            cout << "Error creating bill file!" << endl;
            return;
        }

        // Write bill header with bill ID and compile-time date & time
        billFile << "========== BILL ==========\n";
        billFile << "Bill ID: " << id << billId << "\n";
        billFile << "Date & Time: " << __DATE__ << " " << __TIME__ << "\n";
        billFile << "User name : " << username << "\n";
        billFile << "========================\n\n";
        billFile << left << setw(20) << "Product" << setw(10) << "Quantity"
                 << setw(10) << "Price" << setw(15) << "Total" << endl;
        billFile << "----------------------------------------\n";

        // Write order items
        double grandTotal = 0;
        for (const OrderItem &item : order)
        {
            billFile << left << setw(20) << item.productName
                     << setw(10) << item.quantity
                     << setw(10) << item.price
                     << setw(15) << item.totalPrice << endl;
            grandTotal += item.totalPrice;
        }

        // Write total
        billFile << "----------------------------------------\n";
        billFile << "Grand Total: " << grandTotal << endl;
        billFile << "========================\n";

        billFile.close();

        ofstream all("./Bills/all_bills.txt", ios::app);
        if (!all)
        {
            cout << "Error creating bill file!" << endl;
            return;
        }

        all << "================= BILL =================\n";
        all << "Bill ID: " << id << billId << "\n";
        all << "Date & Time: " << __DATE__ << " " << __TIME__ << "\n";
        all << "User name : " << username << "\n";
        all << "========================================\n\n";
        all << left << setw(20) << "Product" << setw(10) << "Quantity"
            << setw(10) << "Price" << setw(15) << "Total" << endl;
        all << "----------------------------------------\n";

        // Write order items

        for (const OrderItem &item : order)
        {
            all << left << setw(20) << item.productName
                << setw(10) << item.quantity
                << setw(10) << item.price
                << setw(15) << item.totalPrice << endl;
        }

        // Write total
        all << "----------------------------------------\n";
        all << "Grand Total: " << grandTotal << endl;
        all << "========================================\n\n";

        all.close();

        cout << "Bill generated successfully! Bill ID: " << id << endl;
        cout << "Saved as: " << filename << endl;

        // Clear the order after generating bill
        order.clear();
    }
};

class Employee : public Product
{
public:
    // Add product to file
    void addProduct(string name, int price)
    {
        cart.push_back({name, price});

        ofstream file("./ProductManager/product.txt", ios::app);
        if (!file)
        {
            cout << "Error opening file!" << endl;
            return;
        }
        file << name << "\t" << price << endl;
        file.close();

        cout << "Product added successfully!" << endl;
    }

    void removeProduct()
    {
        // Display the list of products before removal

        viewproduct(); // Just call the viewproduct() method to display products

        int productNumber;
        cout << "Enter the number of the product to remove: ";
        cin >> productNumber;

        // Validate input
        if (productNumber < 1 || productNumber > cart.size())
        {
            cout << "Invalid product number!" << endl;
            return;
        }

        // Remove the product from cart using the product number (adjust for 0-based index)
        cart.erase(cart.begin() + productNumber - 1);
        cout << "Product removed successfully!" << endl;

        // Re-write the product file without the removed product
        ofstream file("./ProductManager/product.txt", ios::trunc);
        if (!file)
        {
            cout << "Error opening product file!" << endl;
            return;
        }

        // Write the updated list of products back to the file
        for (const auto &p : cart)
        {
            file << p.first << "\t" << p.second << endl;
        }

        file.close();
        cout << "Product list updated in the file." << endl;
    }

    void manageUsers()
    {

        string username;
        cout << "Enter the username of the user to remove: ";
        cin >> username;

        ifstream userfile("./Data/User/Userdata.txt");
        vector<string> users;
        string line;
        bool userFound = false;

        // Read users from the file and store in a vector
        while (getline(userfile, line))
        {
            users.push_back(line);
        }
        userfile.close();

        // Find and remove the user
        ofstream userfile_out("./Data/User/Userdata.txt");
        for (const string &user : users)
        {
            if (user.find(username) == string::npos)
            {
                userfile_out << user << endl;
            }
            else
            {
                userFound = true;
            }
        }
        userfile_out.close();

        if (userFound)
        {
            cout << "User '" << username << "' removed successfully." << endl;
        }
        else
        {
            cout << "User '" << username << "' not found." << endl;
        }
    }
};

class Admin : public Employee
{
public:
    void addEmployee()
    {
        // Open the file where employee credentials will be saved
        string employ;
        string password;

        cout << "Enter the employee's username: ";
        cin >> employ;
        cout << "Enter the employee's password: ";
        cin >> password;

        ofstream employeeFile("./Data/Employer/employ.txt", ios::app);

        if (employeeFile)
        {
            // Append employee credentials to the file
            employeeFile << employ << " " << password << endl;
            employeeFile.close();
            cout << "Employee '" << employ << "' added successfully." << endl;
        }
        else
        {
            cout << "Failed to open employee file." << endl;
        }
    }

    void manage_employ()
    {

        string employ;
        cout << "Enter the username of the Employee to remove: ";
        cin >> employ;

        ifstream userfile("./Data/Employer/employ.txt");
        vector<string> users;
        string line;
        bool userFound = false;

        // Read users from the file and store in a vector
        while (getline(userfile, line))
        {
            users.push_back(line);
        }
        userfile.close();

        // Find and remove the user
        ofstream userfile_out("./Data/Employer/employ.txt");
        for (const string &user : users)
        {
            if (user.find(employ) == string::npos)
            {
                userfile_out << user << endl;
            }
            else
            {
                userFound = true;
            }
        }
        userfile_out.close();

        if (userFound)
        {
            cout << "User '" << employ << "' removed successfully." << endl;
        }
        else
        {
            cout << "User '" << employ << "' not found." << endl;
        }
    }
};

#endif
