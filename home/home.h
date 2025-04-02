#ifndef HOME_H
#define HOME_H

#include <bits/stdc++.h>
#include "./../setting/color.h"
#include "./../Data/login.h"
#include "./../Data/create.h"
//#include "./../Utility/utils.h"

using namespace std;

void welcome()
{
     cout << "Welcome to " << CYAN << "Digital Mart" << RESET
          << endl
          << endl;

     cout << "Your one-stop shop for all essentials at the best prices! From daily groceries to stationery,\n snacks to self-care products, we have got everything you need all under one roof."
          << "" << endl
          << YELLOW << endl
          << endl
          << "|| Our Special Feature! ||" << RESET << endl
          << "Now, enjoy a seamless and smart shopping experience with our self-ordering devices!  Simply" << endl
          << "place your order from the device provided, and we will have everything ready for you quick, easy, and hassle-free!" << endl;

     cout << endl
          << endl
          << endl

          << INVERSE << BOLD << "Press Enter..." << RESET << endl;
     cin.get(); // Waits for the user to press Enter
}



void menu()
{
     while (1)
     {

          cout << LOGO_head;
          cout << "1. Login" << endl
               << "2. Create Account" << endl
               << RED << "3. Exit" << endl
               << RESET;

          cout << endl
               << "Enter your choice: ";
          int choice;
          cin >> choice;

          switch (choice)
          {
          case 1:
               system("clear");
               cout << GREEN << "logging........\n"
                    << RESET;
               login();
               system("clear");
               break;

          case 2:
               system("clear");
               cout << GREEN << "createing account........\n"
                    << RESET;
               createAccount();
               system("clear");
               break;

          case 3:

               cout << ""
                    << "THANK YOU FOR SHOPPING AT" << YELLOW << " AI Wallah " << RESET
                    << "We appreciate your visit and hope you had a smooth and enjoyable shopping experience.\n"
                    << "Your convenience is our priority, and we look forward to serving you again soon!"
                    << "\n\nOPENING HOURS: " << GREEN << "24 * 7\n"
                    << RESET
                    << "\n\n\n"
                    << CYAN << " SEE YOU SOON! SHOP SMART, STAY HAPPY!" << RESET
                    << "\n\n\n\n\n\n";
               cout << endl
                    << endl
                    << endl
                    << endl
                    << endl;
               cout << INVERSE << BOLD << "Press Enter to exit..." << RESET << endl;
               cin.ignore();
               cin.get(); // Waits for the user to press Enter
               exit(1);
               break;

          default:
               cout << RED << "Invalid choice\n"
                    << RESET;
               break;
          }
          // if (choice == 3)
          //      return;
     }
}

void project()
{
     welcome();
     system("clear");

     menu();
}

#endif 
// HOME_H

/*

cout << endl << endl << endl  << endl << endl;
     cout << INVERSE << BOLD << "Press Enter to exit..." << RESET << endl;
     cin.get(); // Waits for the user to press Enter

*/
