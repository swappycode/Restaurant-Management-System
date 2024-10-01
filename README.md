
# Restaurant Management System

## Description

The **Restaurant Management System** is a C-based project that simulates a simple restaurant ordering system. This program allows users to place food orders, manage an order queue, and calculate both the total bill and preparation time for each order. It is designed to streamline the ordering process, from selecting menu items to delivery scheduling based on preparation time.

## Features

- **Menu Management**: Displays a list of available food items with their respective costs and preparation times.
- **Order Placement**: Users can place multiple orders and specify the quantity for each item.
- **Order Delivery**: Manages the delivery of orders based on their preparation times.
- **Total Bill Calculation**: Computes the total bill for all items in the order list.
- **Preparation Time Calculation**: Provides the total time required to prepare the current list of orders.
- **Order History**: Maintains an order history for tracking previous orders.

## Data Structures Used

1. **Struct for Food Items**:
   - The `food` struct represents each menu item and contains attributes such as:
     - `cost`: Cost of the food item.
     - `hours`: Preparation time in hours.
     - `minutes`: Preparation time in minutes.
     - `quantity`: Available quantity of the food item.
     - `name`: Name of the food item.

   ```c
   struct food {
       int cost;
       int hours;
       int minutes;
       int quantity;
       char name[20];
   };
   ```

2. **Linked List for Orders**:
   - The `Order` struct is used to create a linked list for managing orders. It includes:
     - `itemIndex`: Index of the food item in the menu.
     - `quantity`: Quantity ordered.
     - `next`: Pointer to the next order in the list.

   ```c
   struct Order {
       int itemIndex;
       int quantity;
       struct Order* next;
   };
   ```

3. **Order Stack**:
   - A stack structure (using linked list) is used to manage the orders placed by users. The stack allows for the Last-In-First-Out (LIFO) processing of orders.

   ```c
   struct Order* orderStack = NULL;
   ```

4. **Delivery Queue**:
   - A queue structure (using linked list) is implemented to manage the delivery of orders based on their preparation times, ensuring that orders are delivered in an efficient manner.

   ```c
   struct Order* deliveryQueue = NULL;
   ```

## Usage

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/swappycode/Restaurant-Management-System.git
   cd Restaurant-Management-System
   ```

2. **Compile the Code**:
   Use a C compiler to compile the program. For example, using `gcc`:
   ```bash
   gcc -o restaurant_management restaurant.c
   ```

3. **Run the Program**:
   Execute the compiled program:
   ```bash
   ./restaurant_management
   ```

4. **Follow the Prompts**:
   The program will guide you through the ordering process. Select food items from the menu, specify quantities, and manage your orders.

## Contributing

Contributions are welcome! If you have suggestions or improvements, please create a pull request or open an issue.

## License

IT IS FREE USE IT AS PER YOUR REQUIREMENT

## Author

Developed by [swappycode](https://github.com/swappy-code).
