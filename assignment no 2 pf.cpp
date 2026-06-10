
                                           PF Theory Assignment No. 2

Program 1: Electricity Bill Management System for LESCO
#include <iostream>
#include <iomanip>
using namespace std;

// ---------------- CUSTOMER DATA ----------------
string name, id, type;
int meters;
int units;

// Slab rates (1D array)
double rates[] = {12.21, 14.53, 31.51, 38.41, 41.62, 43.04, 44.18, 49.10};

// ---------------- REGISTER CUSTOMER ----------------
void registerCustomer() {
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Customer ID: ";
    cin >> id;

    cout << "Customer Type (Household/Commercial): ";
    cin >> type;

    cout << "Number of meters (1/2): ";
    cin >> meters;
}

// ---------------- ELECTRICITY CHARGES ----------------
double consumptionCharges(int u) {
    double total = 0;

    if (u <= 100) total = u * rates[0];
    else if (u <= 200) total = u * rates[1];
    else if (u <= 300) total = u * rates[2];
    else if (u <= 400) total = u * rates[3];
    else if (u <= 500) total = u * rates[4];
    else if (u <= 600) total = u * rates[5];
    else if (u <= 700) total = u * rates[6];
    else total = u * rates[7];

    return total;
}

// ---------------- FIXED CHARGES ----------------
double fixedCharges(int u) {
    if (u <= 300) return 0;
    else if (u <= 400) return 200;
    else if (u <= 500) return 400;
    else if (u <= 600) return 600;
    else if (u <= 700) return 800;
    else return 1000;
}

// ---------------- ELECTRICITY DUTY ----------------
double duty(double consumption) {
    return consumption * 0.015;
}

// ---------------- GST ----------------
double gst(double total) {
    return total * 0.18;
}

// ---------------- INCOME TAX ----------------
double incomeTax(double total) {
    if (type == "Household" || type == "household")
        return total * 0.10;
    else
        return total * 0.15;
}

// ---------------- NEW CONNECTION ----------------
double newConnectionCharges() {
    double cost = 0;

    if (type == "Household" || type == "household") {
        if (meters == 1) cost = 2500;
        else cost = 5000;
    }
    else {
        if (meters == 1) cost = 35000;
        else cost = 70000;
    }

    cost += 250000; // new connection cost

    return cost;
}

// ---------------- DISPLAY DETAILS ----------------
void showCustomer() {
    cout << "\n========== CUSTOMER DETAILS ==========\n";
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Type: " << type << endl;
    cout << "Meters: " << meters << endl;
}

// ---------------- FINAL BILL ----------------
void showBill() {

    double consumption = consumptionCharges(units);
    double dutyAmt = duty(consumption);
    double fixed = fixedCharges(units);

    double meterRent = 250;
    double tvFee = 35;

    double subtotal = consumption + dutyAmt + fixed + meterRent + tvFee;
    double tax = gst(subtotal);
    double income = incomeTax(subtotal);

    double total = subtotal + tax + income;

    cout << fixed << setprecision(2);

    cout << "\n========== LESCO ELECTRICITY BILL ==========\n";
    cout << "Customer Name: " << name << endl;
    cout << "Customer ID: " << id << endl;
    cout << "Customer Type: " << type << endl;
    cout << "Units Consumed: " << units << endl;

    cout << "Consumption Charges: Rs. " << consumption << endl;
    cout << "Electricity Duty: Rs. " << dutyAmt << endl;
    cout << "Fixed Charges: Rs. " << fixed << endl;
    cout << "Meter Rent: Rs. " << meterRent << endl;
    cout << "TV Fee: Rs. " << tvFee << endl;
    cout << "GST: Rs. " << tax << endl;
    cout << "Income Tax: Rs. " << income << endl;

    cout << "------------------------------------------\n";
    cout << "Total Payable Bill: Rs. " << total << endl;
    cout << "==========================================\n";
}

// ---------------- MAIN ----------------
int main() {

    int choice;

    registerCustomer();

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Calculate Monthly Bill\n";
        cout << "2. New Connection Charges\n";
        cout << "3. View Customer Details\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                cout << "Enter Units Consumed: ";
                cin >> units;
                showBill();
                break;

            case 2:
                cout << "\nNew Connection Cost: Rs. "
                     << newConnectionCharges() << endl;
                break;

            case 3:
                showCustomer();
                break;

            case 4:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 4);

    return 0;
}

Program 2: Restaurant Billing Management System
#include <iostream>
#include <iomanip>
using namespace std;

// Menu data (1D arrays)
string items[] = {
    "Chicken Burger", "Zinger Burger", "Pizza Small", "Pizza Large",
    "Chicken Biryani", "BBQ Platter", "Fries", "Cold Drink"
};

int prices[] = {450, 550, 900, 1800, 350, 1200, 250, 120};
int quantity[8] = {0};

// Customer data
string name, contact, orderType;
int persons;

// Function declarations
void registerCustomer();
void displayMenu();
void placeOrder();
double calculateFoodBill();
double serviceCharges(double bill);
double gst(double bill);
double discount(double bill);
void displayCustomer();
void displayFinalBill();

int main() {
    int choice;

    registerCustomer();

    do {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. View Food Menu\n";
        cout << "2. Place Order\n";
        cout << "3. Calculate Bill\n";
        cout << "4. View Customer Details\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                displayMenu();
                break;

            case 2:
                placeOrder();
                break;

            case 3:
                displayFinalBill();
                break;

            case 4:
                displayCustomer();
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 5);

    return 0;
}

// 1. Register customer
void registerCustomer() {
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Contact Number: ";
    cin >> contact;

    cout << "Order Type (Dine-in/Takeaway): ";
    cin >> orderType;

    cout << "Number of Persons: ";
    cin >> persons;
}

// 2. Display menu
void displayMenu() {
    cout << "\n========== FOOD MENU ==========\n";
    for(int i = 0; i < 8; i++) {
        cout << i + 1 << ". " << items[i]
             << " - Rs. " << prices[i] << endl;
    }
}

// 3. Place order
void placeOrder() {
    int itemNo, qty;

    displayMenu();

    cout << "\nEnter item number (0 to stop): ";

    while(true) {
        cin >> itemNo;

        if(itemNo == 0) break;

        if(itemNo < 1 || itemNo > 8) {
            cout << "Invalid item!\n";
            continue;
        }

        cout << "Enter quantity: ";
        cin >> qty;

        quantity[itemNo - 1] += qty;

        cout << "Add more items or 0 to stop: ";
    }
}

// 4. Food bill
double calculateFoodBill() {
    double total = 0;

    for(int i = 0; i < 8; i++) {
        total += quantity[i] * prices[i];
    }

    return total;
}

// 5. Service charges
double serviceCharges(double bill) {
    if(orderType == "Dine-in" || orderType == "dine-in")
        return bill * 0.10;
    else
        return bill * 0.05;
}

// 6. GST
double gst(double bill) {
    return bill * 0.16;
}

// 7. Discount
double discount(double bill) {
    if(bill >= 3000 && bill <= 5000)
        return bill * 0.05;
    else if(bill <= 10000)
        return bill * 0.10;
    else if(bill > 10000)
        return bill * 0.15;
    else
        return 0;
}

// 8 & 9. Final bill + free delivery rule
void displayFinalBill() {
    double foodBill = calculateFoodBill();
    double service = serviceCharges(foodBill);
    double tax = gst(foodBill);
    double disc = discount(foodBill);

    double total = foodBill + service + tax - disc;

    cout << "\n========== RESTAURANT BILL ==========\n";
    cout << "Customer Name: " << name << endl;
    cout << "Order Type: " << orderType << endl;
    cout << "Number of Persons: " << persons << endl;

    cout << fixed << setprecision(2);

    cout << "\nFood Bill: Rs. " << foodBill;
    cout << "\nService Charges: Rs. " << service;
    cout << "\nGST: Rs. " << tax;
    cout << "\nDiscount: Rs. " << disc;

    if(total > 5000)
        cout << "\nFree Delivery: Applied";

    cout << "\n------------------------------------";
    cout << "\nTotal Payable Amount: Rs. " << total;
    cout << "\nEnjoy Your Meal :)\n";
    cout << "====================================\n";
}

// 10. Customer details
void displayCustomer() {
    cout << "\n========== CUSTOMER DETAILS ==========\n";
    cout << "Name: " << name << endl;
    cout << "Contact: " << contact << endl;
    cout << "Order Type: " << orderType << endl;
    cout << "Persons: " << persons << endl;
}

Program 3: Grocery Mart Billing System
#include <iostream>
#include <iomanip>
using namespace std;

// ---------- Grocery Data ----------

string items[] = {
    "Rice 1 KG",
    "Sugar 1 KG",
    "Cooking Oil 1 Litre",
    "Milk Pack",
    "Tea Pack",
    "Flour 5 KG",
    "Eggs Dozen",
    "Detergent"
};

double prices[] = {
    350, 180, 580, 220,
    450, 950, 320, 600
};

int quantity[8] = {0};

// ---------- Customer Data ----------

string customerName;
int customerID;
int customerType;
int paymentMethod;

// ---------- Function Declarations ----------

void registerCustomer();
void displayGroceryItems();
void addItemsToCart();

double calculateGrossBill();
double calculateSalesTax(double bill);
double calculateMembershipDiscount(double bill);
double calculateBillDiscount(double bill);
double calculateCardCharges(double bill);

int calculateLoyaltyPoints(double bill);

void displayCustomerDetails();
void displayFinalBill();

// ---------- Main Function ----------

int main()
{
    int choice;

    registerCustomer();

    do
    {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. View Grocery Items\n";
        cout << "2. Add Items to Cart\n";
        cout << "3. Calculate Bill\n";
        cout << "4. View Customer Details\n";
        cout << "5. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayGroceryItems();
                break;

            case 2:
                addItemsToCart();
                break;

            case 3:
                displayFinalBill();
                break;

            case 4:
                displayCustomerDetails();
                break;

            case 5:
                cout << "\nProgram Exited Successfully!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 5);

    return 0;
}

// ---------- 1. Register Customer ----------

void registerCustomer()
{
    cout << "========== CUSTOMER REGISTRATION ==========\n";

    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "Enter Customer ID: ";
    cin >> customerID;

    cout << "\nCustomer Type\n";
    cout << "1. Regular Customer\n";
    cout << "2. Member Customer\n";
    cout << "Enter Choice: ";
    cin >> customerType;

    cout << "\nPayment Method\n";
    cout << "1. Cash\n";
    cout << "2. Card\n";
    cout << "Enter Choice: ";
    cin >> paymentMethod;
}

// ---------- 2. Display Grocery List ----------

void displayGroceryItems()
{
    cout << "\n========== GROCERY ITEMS ==========\n";

    for(int i = 0; i < 8; i++)
    {
        cout << i + 1 << ". "
             << items[i]
             << " - Rs. "
             << prices[i]
             << endl;
    }
}

// ---------- 3. Add Items To Cart ----------

void addItemsToCart()
{
    int itemNo, qty;

    displayGroceryItems();

    cout << "\nEnter Item Number (0 to stop): ";

    while(true)
    {
        cin >> itemNo;

        if(itemNo == 0)
            break;

        if(itemNo < 1 || itemNo > 8)
        {
            cout << "Invalid Item Number!\n";
            continue;
        }

        cout << "Enter Quantity: ";
        cin >> qty;

        quantity[itemNo - 1] += qty;

        cout << "Add More Items or 0 to stop: ";
    }
}

// ---------- 4. Calculate Gross Bill ----------

double calculateGrossBill()
{
    double total = 0;

    for(int i = 0; i < 8; i++)
    {
        total += quantity[i] * prices[i];
    }

    return total;
}

// ---------- 5. Calculate Sales Tax ----------

double calculateSalesTax(double bill)
{
    double tax = 0;

    for(int i = 0; i < 8; i++)
    {
        double itemTotal = quantity[i] * prices[i];

        // Food Items 1–7
        if(i >= 0 && i <= 6)
        {
            tax += itemTotal * 0.05;
        }

        // Non-food Item 8
        else
        {
            tax += itemTotal * 0.10;
        }
    }

    return tax;
}

// ---------- 6. Membership Discount ----------

double calculateMembershipDiscount(double bill)
{
    if(customerType == 2)
    {
        return bill * 0.07;
    }

    return 0;
}

// ---------- 7. Bill Amount Discount ----------

double calculateBillDiscount(double bill)
{
    if(bill >= 5000 && bill <= 10000)
    {
        return bill * 0.05;
    }

    else if(bill > 10000)
    {
        return bill * 0.10;
    }

    return 0;
}

// ---------- 8. Card Charges ----------

double calculateCardCharges(double bill)
{
    if(paymentMethod == 2)
    {
        return bill * 0.02;
    }

    return 0;
}

// ---------- 9. Loyalty Points ----------

int calculateLoyaltyPoints(double bill)
{
    return bill / 100;
}

// ---------- Final Bill ----------

void displayFinalBill()
{
    double grossBill = calculateGrossBill();

    double salesTax =
        calculateSalesTax(grossBill);

    double membershipDiscount =
        calculateMembershipDiscount(grossBill);

    double billDiscount =
        calculateBillDiscount(grossBill);

    double subtotal =
        grossBill
        + salesTax
        - membershipDiscount
        - billDiscount;

    double cardCharges =
        calculateCardCharges(subtotal);

    double totalBill =
        subtotal + cardCharges;

    // Loyalty Points

    int generatedPoints =
        calculateLoyaltyPoints(totalBill);

    int existingPoints;

    cout << "\nGenerated Loyalty Points: "
         << generatedPoints << endl;

    cout << "Enter Your Existing Loyalty Points "
         << "(Enter 0 if new user): ";

    cin >> existingPoints;

    int totalPoints =
        generatedPoints + existingPoints;

    cout << "Loyalty Points after Purchase: "
         << totalPoints << endl;

    int choice;

    cout << "\nPress 1 to redeem loyalty points\n";
    cout << "Press 2 to continue\n";
    cout << "Enter Choice: ";
    cin >> choice;

    if(choice == 1)
    {
        totalBill -= totalPoints;

        if(totalBill < 0)
        {
            totalBill = 0;
        }
    }

    cout << fixed << setprecision(2);

    cout << "\n========== GROCERY MART BILL ==========\n";

    cout << "Customer Name: "
         << customerName << endl;

    if(customerType == 1)
        cout << "Customer Type: Regular Customer\n";
    else
        cout << "Customer Type: Member Customer\n";

    if(paymentMethod == 1)
        cout << "Payment Method: Cash\n";
    else
        cout << "Payment Method: Card\n";

    cout << "\nGross Bill: Rs. "
         << grossBill;

    cout << "\nSales Tax: Rs. "
         << salesTax;

    cout << "\nMembership Discount: Rs. "
         << membershipDiscount;

    cout << "\nBill Discount: Rs. "
         << billDiscount;

    cout << "\nCard Charges: Rs. "
         << cardCharges;

    cout << "\nGenerated Loyalty Points: "
         << generatedPoints;

    cout << "\nLoyalty Points after Purchase: "
         << totalPoints;

    cout << "\n---------------------------------------";

    cout << "\nTotal Payable Amount: Rs. "
         << totalBill;

    cout << "\nThank You For Shopping :)";

    cout << "\n=======================================\n";
}

// ---------- Customer Details ----------

void displayCustomerDetails()
{
    cout << "\n========== CUSTOMER DETAILS ==========\n";

    cout << "Customer Name: "
         << customerName << endl;

    cout << "Customer ID: "
         << customerID << endl;

    if(customerType == 1)
        cout << "Customer Type: Regular Customer\n";
    else
        cout << "Customer Type: Member Customer\n";

    if(paymentMethod == 1)
        cout << "Payment Method: Cash\n";
    else
        cout << "Payment Method: Card\n";
}

Program 4: Online Shopping System
#include <iostream>
#include <iomanip>
using namespace std;

// Global Variables
string userName, email, city;
int customerType; // 1 = New, 2 = Returning

string products[8] = {
    "T-Shirt",
    "Jeans",
    "Shoes",
    "Watch",
    "Handbag",
    "Headphones",
    "Mobile Cover",
    "Perfume"
};

int prices[8] = {
    1200,
    3500,
    5000,
    2500,
    4200,
    3000,
    700,
    2800
};

int cart[100];
int cartCount = 0;

// Function Prototypes
void registerUser();
void displayProducts();
void addToCart();
double calculateProductTotal();
double calculateGST(double total);
double calculateDeliveryCharges();
double calculateCustomerDiscount(double total);
double calculateOrderValueDiscount(double total);
double calculatePaymentCharges(double amount, int paymentMethod);
void displayCheckoutBill();
void viewUserDetails();

int main()
{
    registerUser();

    int choice;

    do
    {
        cout << "\n========== ONLINE SHOPPING SYSTEM ==========\n";
        cout << "1. View Products\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. Calculate Checkout Bill\n";
        cout << "4. View User Details\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayProducts();
                break;

            case 2:
                addToCart();
                break;

            case 3:
                displayCheckoutBill();
                break;

            case 4:
                viewUserDetails();
                break;

            case 5:
                cout << "\nThank You for Using Online Shopping System!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 5);

    return 0;
}

// Register User
void registerUser()
{
  

    cout << "Enter User Name: ";
    getline(cin, userName);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter City: ";
    getline(cin, city);

    cout << "\nCustomer Type\n";
    cout << "1. New Customer\n";
    cout << "2. Returning Customer\n";
    cout << "Enter Choice: ";
    cin >> customerType;
}

// Display Products
void displayProducts()
{
    cout << "\n========== PRODUCT LIST ==========\n";

    for(int i = 0; i < 8; i++)
    {
        cout << i + 1 << ". "
             << products[i]
             << " - Rs. "
             << prices[i]
             << endl;
    }
}

// Add Product To Cart
void addToCart()
{
    int productNo;

    displayProducts();

    cout << "\nEnter Product Number: ";
    cin >> productNo;

    if(productNo >= 1 && productNo <= 8)
    {
        cart[cartCount] = productNo - 1;
        cartCount++;

        cout << products[productNo - 1]
             << " added to cart successfully.\n";
    }
    else
    {
        cout << "Invalid Product Number!\n";
    }
}

// Calculate Product Total
double calculateProductTotal()
{
    double total = 0;

    for(int i = 0; i < cartCount; i++)
    {
        total += prices[cart[i]];
    }

    return total;
}

// Calculate GST
double calculateGST(double total)
{
    return total * 0.17;
}

// Calculate Delivery Charges
double calculateDeliveryCharges()
{
    if(city == "Lahore" ||
       city == "Karachi" ||
       city == "Islamabad")
    {
        return 250;
    }

    return 500;
}

// Customer Discount
double calculateCustomerDiscount(double total)
{
    if(customerType == 1)
    {
        return total * 0.05;
    }
    else if(customerType == 2)
    {
        return total * 0.10;
    }

    return 0;
}

// Order Value Discount
double calculateOrderValueDiscount(double total)
{
    if(total >= 5000 && total <= 10000)
    {
        return total * 0.05;
    }
    else if(total > 10000)
    {
        return total * 0.12;
    }

    return 0;
}

// Payment Charges
double calculatePaymentCharges(double amount, int paymentMethod)
{
    if(paymentMethod == 2)
    {
        return amount * 0.025;
    }

    return 0;
}

// View User Details
void viewUserDetails()
{
    cout << "\n========== USER DETAILS ==========\n";

    cout << "User Name: " << userName << endl;
    cout << "Email: " << email << endl;
    cout << "City: " << city << endl;

    if(customerType == 1)
        cout << "Customer Type: New Customer\n";
    else
        cout << "Customer Type: Returning Customer\n";
}

// Display Checkout Bill
void displayCheckoutBill()
{
    if(cartCount == 0)
    {
        cout << "\nCart is Empty!\n";
        return;
    }

    double productTotal = calculateProductTotal();
    double gst = calculateGST(productTotal);
    double deliveryCharges = calculateDeliveryCharges();
    double customerDiscount =
        calculateCustomerDiscount(productTotal);
    double orderDiscount =
        calculateOrderValueDiscount(productTotal);

    int paymentMethod;

    cout << "\nSelect Payment Method\n";
    cout << "1. Cash on Delivery\n";
    cout << "2. Debit/Credit Card\n";
    cout << "Enter Choice: ";
    cin >> paymentMethod;

    double paymentCharges =
        calculatePaymentCharges(productTotal, paymentMethod);

    double finalAmount =
        productTotal +
        gst +
        deliveryCharges +
        paymentCharges -
        customerDiscount -
        orderDiscount;

    cout << fixed << setprecision(2);

    cout << "\n\n========== ONLINE SHOPPING BILL ==========\n";

    cout << "User Name: " << userName << endl;
    cout << "City: " << city << endl;

    if(customerType == 1)
        cout << "Customer Type: New Customer\n";
    else
        cout << "Customer Type: Returning Customer\n";

    cout << "\nProduct Total: Rs. " << productTotal << endl;
    cout << "GST: Rs. " << gst << endl;
    cout << "Delivery Charges: Rs. "
         << deliveryCharges << endl;
    cout << "Customer Discount: Rs. "
         << customerDiscount << endl;
    cout << "Order Discount: Rs. "
         << orderDiscount << endl;
    cout << "Payment Charges: Rs. "
         << paymentCharges << endl;

    cout << "------------------------------------------\n";
    cout << "Final Payable Amount: Rs. "
         << finalAmount << endl;

    cout << "Thank You for Shopping :)\n";
    cout << "==========================================\n";
}

Program 5: Social Media Management System
#include <iostream>
#include <iomanip>
using namespace std;

// Platform Data (1D Arrays)
string platforms[] = {
    "Instagram",
    "Facebook",
    "LinkedIn"
};

double platformCharges[] = {
    15000,
    12000,
    20000
};

// Client Data
string clientName;
string businessName;
int businessType;      // 1=Small, 2=Medium, 3=Corporate
int campaignDuration;

int selectedPlatform = -1;

int staticPosts = 0;
int reelPosts = 0;
int carouselPosts = 0;

double adBudget = 0;

// Function Prototypes
void registerClient();
void displayPlatforms();
void selectPlatform();
double calculatePostDesignCost();
double calculateAdHandlingFee();
double calculateExtraDurationCharges();
double calculateGST(double amount);
double calculateDiscount(double amount);
void displayFinalCampaignBill();
void displayClientDetails();

int main()
{
    int choice;

    registerClient();

    do
    {
        cout << "\n========== SOCIAL MEDIA MANAGEMENT SYSTEM ==========\n";
        cout << "1. View Platforms\n";
        cout << "2. Select Campaign Platform\n";
        cout << "3. Calculate Campaign Cost\n";
        cout << "4. View Client Details\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayPlatforms();
                break;

            case 2:
                selectPlatform();
                break;

            case 3:
                displayFinalCampaignBill();
                break;

            case 4:
                displayClientDetails();
                break;

            case 5:
                cout << "\nProgram Closed Successfully.\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 5);

    return 0;
}

// 1. Register Client
void registerClient()
{
    cin.ignore();

    cout << "Enter Client Name: ";
    getline(cin, clientName);

    cout << "Enter Business Name: ";
    getline(cin, businessName);

    cout << "\nBusiness Type\n";
    cout << "1. Small Business\n";
    cout << "2. Medium Business\n";
    cout << "3. Corporate Business\n";
    cout << "Enter Choice: ";
    cin >> businessType;

    cout << "Enter Campaign Duration (Days): ";
    cin >> campaignDuration;
}

// 2. Display Platforms
void displayPlatforms()
{
    cout << "\n========== SOCIAL MEDIA PLATFORMS ==========\n";

    for(int i = 0; i < 3; i++)
    {
        cout << i + 1 << ". "
             << platforms[i]
             << " - Rs. "
             << platformCharges[i]
             << endl;
    }
}

// 3. Select Platform
void selectPlatform()
{
    displayPlatforms();

    cout << "\nSelect Platform Number: ";
    cin >> selectedPlatform;

    if(selectedPlatform < 1 || selectedPlatform > 3)
    {
        cout << "Invalid Platform Selection!\n";
        selectedPlatform = -1;
    }
    else
    {
        cout << platforms[selectedPlatform - 1]
             << " Selected Successfully.\n";
    }
}

// 4. Calculate Post Design Cost
double calculatePostDesignCost()
{
    cout << "\nEnter Number of Static Posts: ";
    cin >> staticPosts;

    cout << "Enter Number of Reel/Video Posts: ";
    cin >> reelPosts;

    cout << "Enter Number of Carousel Posts: ";
    cin >> carouselPosts;

    double cost =
        (staticPosts * 1000) +
        (reelPosts * 2500) +
        (carouselPosts * 1800);

    return cost;
}

// 5. Calculate Ad Handling Fee
double calculateAdHandlingFee()
{
    cout << "\nEnter Advertisement Budget: ";
    cin >> adBudget;

    if(adBudget < 50000)
        return adBudget * 0.05;

    else if(adBudget <= 100000)
        return adBudget * 0.08;

    else
        return adBudget * 0.10;
}

// 6. Calculate Extra Duration Charges
double calculateExtraDurationCharges()
{
    if(campaignDuration > 30)
    {
        return (campaignDuration - 30) * 500;
    }

    return 0;
}

// 7. Calculate GST
double calculateGST(double amount)
{
    return amount * 0.16;
}

// 8. Calculate Discount
double calculateDiscount(double amount)
{
    if(businessType == 1)
        return amount * 0.05;

    else if(businessType == 2)
        return amount * 0.08;

    else if(businessType == 3)
        return amount * 0.10;

    return 0;
}

// 9. Display Final Campaign Bill
void displayFinalCampaignBill()
{
    if(selectedPlatform == -1)
    {
        cout << "\nPlease Select a Platform First!\n";
        return;
    }

    double managementCharges =
        platformCharges[selectedPlatform - 1];

    double postDesignCost =
        calculatePostDesignCost();

    double handlingFee =
        calculateAdHandlingFee();

    double extraCharges =
        calculateExtraDurationCharges();

    double serviceCost =
        managementCharges +
        postDesignCost +
        adBudget +
        handlingFee +
        extraCharges;

    double gst =
        calculateGST(serviceCost);

    double discount =
        calculateDiscount(serviceCost);

    double finalCost =
        serviceCost +
        gst -
        discount;

    cout << fixed << setprecision(2);

    cout << "\n\n========== SOCIAL MEDIA CAMPAIGN BILL ==========\n";

    cout << "Client Name: "
         << clientName << endl;

    cout << "Business Name: "
         << businessName << endl;

    if(businessType == 1)
        cout << "Business Type: Small Business\n";
    else if(businessType == 2)
        cout << "Business Type: Medium Business\n";
    else
        cout << "Business Type: Corporate Business\n";

    cout << "Selected Platform: "
         << platforms[selectedPlatform - 1] << endl;

    cout << "Campaign Duration: "
         << campaignDuration
         << " Days\n";

    cout << "\nPlatform Management Charges: Rs. "
         << managementCharges << endl;

    cout << "Post Design Cost: Rs. "
         << postDesignCost << endl;

    cout << "Ad Budget: Rs. "
         << adBudget << endl;

    cout << "Ad Handling Fee: Rs. "
         << handlingFee << endl;

    cout << "Extra Duration Charges: Rs. "
         << extraCharges << endl;

    cout << "GST: Rs. "
         << gst << endl;

    cout << "Discount: Rs. "
         << discount << endl;

    cout << "------------------------------------------------\n";

    cout << "Final Campaign Cost: Rs. "
         << finalCost << endl;

    cout << "================================================\n";
}

// 10. Display Client Details
void displayClientDetails()
{
    cout << "\n========== CLIENT DETAILS ==========\n";

    cout << "Client Name: "
         << clientName << endl;

    cout << "Business Name: "
         << businessName << endl;

    cout << "Campaign Duration: "
         << campaignDuration
         << " Days" << endl;

    if(businessType == 1)
        cout << "Business Type: Small Business\n";
    else if(businessType == 2)
        cout << "Business Type: Medium Business\n";
    else
        cout << "Business Type: Corporate Business\n";
}

