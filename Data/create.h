#ifndef CREATE_H
#define CREATE_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

void createAccount() {
          char name[50];
          char password[10];  
          char su[50];
      
          cout << "Enter your name: ";
          cin >> name;
          
          // Check if account already exists
          ifstream read("./Data/User/Userdata.txt",ios::app);
          if (!read) {
              cout << "Error opening accounts file" << endl;
              return;
          }
      
          while (read >> su) {
              if (strcmp(name, su) == 0) {
                  cout << "Account already exists" << endl;
                  read.close();
                  return;
              }
          }
          read.close();
      
          cout << "Enter your password: ";
          cin >> password;
      
          // Save account info
          ofstream file("./Data/User/Userdata.txt", ios::app);
          if (!file) {
              cout << "Error creating account" << endl;
              return;
          }
          file << name << " " << password << endl;
          file.close();
          
          cout << "Account created successfully!" << endl;
          system("PAUSE");
          
      }

#endif