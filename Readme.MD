# Digital Mart

Digital Mart is a C++ console-based application that simulates a self-ordering system for a retail store. It provides a complete management solution with distinct functionalities for administrators, employees, and customers. The system handles user authentication, product management, order processing, and automated bill generation.

## Features

*   **Role-Based Access Control:** The system supports three distinct user roles with different levels of access:
    *   **Admin:** Full control over the system, including product management, user management, and employee management.
    *   **Employee:** Can manage products and customer accounts.
    *   **User:** Can browse products, place orders, and generate bills.
*   **User Authentication:** Secure login system that authenticates users, employees, and admins based on credentials stored in text files. Users can also create a new account.
*   **Product Management:** Admins and Employees can:
    *   View all available products with their prices.
    *   Add new products to the inventory.
    *   Remove existing products.
*   **Customer Order System:**
    *   Browse a list of available products.
    *   Add products to a virtual shopping cart with specified quantities.
    *   View the current order summary, including item details and the grand total.
*   **Automated Billing:**
    *   Generates a detailed bill for the customer's order.
    *   Assigns a unique Bill ID using the date and time of generation to prevent conflicts.
    *   Saves each bill as an individual `.txt` file in the `Bills/` directory.
    *   Maintains a consolidated log of all transactions in `Bills/all_bills.txt`.
*   **Data Persistence:** All data, including user credentials, product lists, and bills, is persistently stored in local text files.
*   **Enhanced Console UI:** Utilizes ANSI escape codes to add color and text styling to the console output, creating a more user-friendly and visually appealing interface.

## How to Compile and Run

### Prerequisites
*   A C++ compiler, such as g++.
*   A Unix-like environment (Linux, macOS, or WSL on Windows) for the `system("clear")` and `mkdir` commands to work as intended.

### Steps
1.  Clone the repository to your local machine:
    ```sh
    git clone https://github.com/MANAV-PATEL13/Digital_Mart.git
    ```
2.  Navigate to the project's root directory:
    ```sh
    cd Digital_Mart
    ```
3.  Compile the application using g++:
    ```sh
    g++ main.cpp -o digital_mart
    ```
4.  Run the executable:
    ```sh
    ./digital_mart
    ```
    Default Admin Credentials:
    *   **Username:** `Admin@321`
    *   **Password:** `123456`

## Project Structure

The repository is organized into modules for data, product management, billing, and UI settings.

```
.
├── main.cpp              # Main entry point of the application.
├── home/
│   └── home.h            # Handles the welcome screen and main menu (Login, Create Account, Exit).
├── Data/
│   ├── login.h           # Manages login logic for all user types.
│   ├── create.h          # Handles new customer account creation.
│   ├── Admin/
│   │   └── admin.txt     # Stores administrator credentials.
│   ├── Employer/
│   │   └── employ.txt    # Stores employee credentials.
│   └── User/
│       └── Userdata.txt  # Stores customer credentials.
├── ProductManager/
│   ├── product.txt       # Database of products and their prices.
│   └── product1.h        # Defines classes and methods for all product-related operations.
├── Bills/
│   ├── all_bills.txt     # A consolidated log of all generated bills.
│   ├── id/id.txt         # Tracks the last used bill ID for uniqueness.
│   └── *.txt             # Individual bill files are stored here.
└── setting/
    ├── color.h           # Defines ANSI color and style codes for console output.
    └── color.cpp         # Implementation file for color definitions.