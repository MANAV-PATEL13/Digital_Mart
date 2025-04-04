#ifndef LOGIN_H
#define LOGIN_H

#include <bits/stdc++.h>
using namespace std;

#include "./../setting/color.h"
#include "./../home/home.h"
#include "./../ProductManager/product1.h"

// Function to create the admin file with default credentials
void createAdminFile()
{
    ofstream adminfile("./Data/Admin/admin.txt"); // Create the file
    if (adminfile)
    {
        adminfile << "Admin@321 475mp"; // Write default username & password
        adminfile.close();
        cout << "Admin file created with default credentials." << endl;
    }
}
// Function to handle the login process
void login()
{
    char name[50], password[10];
    char su[50], pass[10];
    int loginType = 0; // 1 = admin, 2 = employee, 3 = user
    int attempts = 0;

    // Login loop for retry on invalid input
    while (loginType == 0 && attempts < 3)
    {
        cout << "Enter your username: ";
        cin >> name;
        cout << "Enter your password: ";
        cin >> password;
        attempts++;

        ifstream adminfile("./Data/Admin/admin.txt");
        if (!adminfile)
        {
            createAdminFile();                        // Create admin file if it doesn't exist
            adminfile.open("./Data/Admin/admin.txt"); // Re-open the newly created file
        }
        if (adminfile)
        {
            adminfile >> su >> pass;
            adminfile.close();

            if (strcmp(name, su) == 0 && strcmp(password, pass) == 0)
            {
                loginType = 1; // Admin login
            }
        }
        ifstream employfile("./Data/Employer/employ.txt");
        if (employfile)
        {
            employfile >> su >> pass;
            if (strcmp(name, su) == 0 && strcmp(password, pass) == 0)
            {
                loginType = 2; // Employer login
            }
            employfile.close();
        }
        ifstream userfile("./Data/User/Userdata.txt");
        if (userfile)
        {
            while (userfile >> su >> pass)
            {
                if (strcmp(name, su) == 0 && strcmp(password, pass) == 0)
                {
                    loginType = 3; // User login
                }
            }
            userfile.close();
        }
        // Check the login type
        if (loginType == 0) {
            cout << RED<< "Invalid username or password. "<< RESET;
            if (attempts < 3) {
                cout << GREEN << "Please try again.\n" << RESET;
            } else {
                cout << RED << "Maximum attempts reached. Exiting...\n" << RESET;
                system("PAUSE");
            }
        }    
    }
    // Depending on the login type, display the appropriate message and show the relevant menu
    switch (loginType)
    {
    case 1:
    {
        cout << GREEN << "Login Successfully in Admin ..." << RESET << endl;
        Admin a1;
        string name;
        int price;
        int choice;
        while (1)
        {
            cout << "1. View Products\n2. Add Product\n3. Remove Product\n4. Manage Users\n5. Add Employees\n6. Manage Employees\n7. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                a1.viewproduct();
                break;
            case 2:
                cout << "Enter product name and price: ";
                cin >> name >> price;
                a1.addProduct(name, price);
                break;
            case 3:
                a1.removeProduct();
                // Implement remove product functionality
                break;
            case 4:
                a1.manageUsers();
                // Implement manage users functionality
                break;
            case 5:
                // Implement add employees functionality
                a1.addEmployee();
                break;
            case 6:
                a1.manage_employ();
                // Implement manage employees functionality
                break;
            case 7:
                cout << RED << "Exiting Admin Menu..." << RESET << endl;
                return; // Exit the loop and return
            default:
                cout << RED << "Invalid choice, please try again." << RESET << endl;
                break;
            }
        }
        break;
    }
    case 2:
    {
        cout << GREEN << "Login Successfully in Employer ..." << RESET << endl;
        Employee e1;
        string name;
        int price;
        int choice;
        while (1)
        {
            cout << "1. View Products\n2. Add Product\n3. Remove Product\n4. Manage Users\n5. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                e1.viewproduct();
                break;
            case 2:
                cout << "Enter product name and price: ";
                cin >> name >> price;
                e1.addProduct(name, price);
                break;
            case 3:
                e1.removeProduct();
                // Implement remove product functionality
                break;
            case 4:
                e1.manageUsers();
                // Implement manage users functionality
                break;
            case 5:
                cout << RED << "Exiting Employer Menu..." << RESET << endl;
                return; // Exit the loop and return
            default:
                cout << RED << "Invalid choice, please try again." << RESET << endl;
                break;
            }
        }
        break;
    }
    case 3:
    {
        cout << GREEN <<"Login Successfully in User ..." << RESET <<endl;
        User u1;
        int choice;
        while (1)
        {
            cout << "1. View Products\n2. Order Product\n3. View Order\n4. Generate Bill\n5. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                u1.viewproduct();
                break;
            case 2:
                u1.Order();
                break;
            case 3:
                u1.Vieworder();
                break;
            case 4:
                u1.generatebill(name); // pass the username
                break;
            case 5:
                cout << RED << "Exiting User Menu..." << RESET << endl;
                return; // Exit the loop and return
            default:
                cout << RED << "Invalid choice, please try again." << RESET << endl;
                break;
            }
        }
        break;
    }
    default:
        cout << RED << "Invalid login type. Exiting..." << RESET << endl;
        break;
    }
}

#endif
