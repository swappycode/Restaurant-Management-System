#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ORDERS 100

struct food {
    int cost;
    int hours;
    int minutes;
    int quantity;
    char name[20];
};

struct Order {
    int itemIndex;
    int quantity;
    struct Order* next;
};

struct food menu[] = {
    {135, 0, 45, 0, "Pav Bhaji"},       // pavbhaji
    {150, 1, 30, 0, "Mutter Paneer"},   // mutterpaneer
    {230, 1, 45, 0, "Chicken Tikka"},   // chickentikka
    {120, 0, 45, 0, "Misal Pav"},       // misalpav
    {200, 1, 45, 0, "Biryani"},         // biryani
    {210, 1, 25, 0, "Dal Makhani"},     // dalmakhani
    {260, 0, 45, 0, "Chana Masala"},    // chanamasala
    {50, 0, 10, 0, "Roti"}              // roti
};

struct Order* orderStack = NULL;
struct Order* deliveryQueue = NULL;

// Function prototype for calculateOrderPreparationTime
int calculateOrderPreparationTime(struct Order* order);

void enqueueDelivery(struct Order* order); // Function prototype

void pushOrder(int itemIndex, int quantity) {
    struct Order* newOrder = (struct Order*)malloc(sizeof(struct Order));
    newOrder->itemIndex = itemIndex;
    newOrder->quantity = quantity;
    newOrder->next = orderStack;
    orderStack = newOrder;

    // Enqueue the order for delivery
    enqueueDelivery(newOrder);
}

void enqueueDelivery(struct Order* order) {
    struct Order* newOrder = (struct Order*)malloc(sizeof(struct Order));
    *newOrder = *order;
    newOrder->next = NULL;

    if (deliveryQueue == NULL) {
        // If the delivery queue is empty, add the order as the first element
        deliveryQueue = newOrder;
    } else {
        struct Order* prev = NULL;
        struct Order* current = deliveryQueue;
        // Traverse the delivery queue to find the correct position to insert the new order
        while (current != NULL && calculateOrderPreparationTime(order) >= calculateOrderPreparationTime(current)) {
            prev = current;
            current = current->next;
        }
        // Insert the new order before the current one
        if (prev == NULL) {
            newOrder->next = deliveryQueue;
            deliveryQueue = newOrder;
        } else {
            prev->next = newOrder;
            newOrder->next = current;
        }
    }
}

struct Order* dequeueDelivery() {
    if (deliveryQueue == NULL)
        return NULL;

    struct Order* temp = deliveryQueue;
    deliveryQueue = deliveryQueue->next;
    temp->next = NULL; // Disconnecting the dequeued order from the queue
    return temp;
}

void displayOrderList() {
    if (orderStack == NULL) {
        printf("Order list is empty.\n");
        return;
    }

    printf("Order List:\n");
    struct Order* temp = orderStack;
    while (temp != NULL) {
        printf("%s x %d\n", menu[temp->itemIndex].name, temp->quantity);
        temp = temp->next;
    }
}

void clearOrderList() {
    struct Order* temp;
    while (orderStack != NULL) {
        temp = orderStack;
        orderStack = orderStack->next;
        free(temp);
    }
    printf("Order list cleared.\n");
}

int calculatePreparationTime() {
    int totalMinutes = 0;
    struct Order* temp = orderStack;
    while (temp != NULL) {
        totalMinutes += calculateOrderPreparationTime(temp);
        temp = temp->next;
    }

    // Convert total minutes to hours and minutes
    int totalHours = totalMinutes / 60;
    totalMinutes %= 60;

    return totalHours * 60 + totalMinutes; // Return total time in minutes
}

// Calculate preparation time for a single order
int calculateOrderPreparationTime(struct Order* order) {
    return (menu[order->itemIndex].hours * 60 + menu[order->itemIndex].minutes) * order->quantity;
}

float calculateTotalBill() {
    float totalBill = 0.0;
    struct Order* temp = orderStack;
    while (temp != NULL) {
        totalBill += (menu[temp->itemIndex].cost * temp->quantity);
        temp = temp->next;
    }
    return totalBill;
}

int main() {
    int choice, itemChoice, quantity;
    char continueOrdering = 'y';

    while (1) {
        printf("\nWelcome to Sardar ka Dhaba\n\n");
        printf("1. Order food\n");
        printf("2. Deliver the order list\n");
        printf("3. Display the order list\n");
        printf("4. Clear the order list\n");
        printf("5. Time taken to prepare order list\n");
        printf("6. Calculate total bill\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    printf("\nWhat food do you want to order?\n");
                    for (int i = 0; i < sizeof(menu) / sizeof(struct food); i++) {
                        printf("%d. %s (Cost: %d, Preparation Time: %d hours %d minutes)\n", i + 1, menu[i].name, menu[i].cost, menu[i].hours, menu[i].minutes);
                    }
                    printf("Enter item choice: ");
                    scanf("%d", &itemChoice);
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);

                    if (itemChoice >= 1 && itemChoice <= sizeof(menu) / sizeof(struct food)) {
                        pushOrder(itemChoice - 1, quantity);
                        menu[itemChoice - 1].quantity += quantity;
                        printf("Order placed successfully.\n");
                    } else {
                        printf("Invalid item choice.\n");
                    }

                    printf("Do you want to order more items? (y/n): ");
                    scanf(" %c", &continueOrdering);
                } while (continueOrdering == 'y' || continueOrdering == 'Y');
                break;

            case 2:
                if (orderStack == NULL) {
                    printf("No orders to deliver.\n");
                } else {
                    struct Order* order = dequeueDelivery();
                    if (order != NULL) {
                        printf("Delivering order: %s x %d\n", menu[order->itemIndex].name, order->quantity);
                        free(order);
                    } else {
                        printf("No orders to deliver.\n");
                    }
                }
                break;

            case 3:
                displayOrderList();
                break;

            case 4:
                clearOrderList();
                break;

            case 5: {
                int preparationTime = calculatePreparationTime();
                int hours = preparationTime / 60;
                int minutes = preparationTime % 60;
                printf("Total time taken to prepare order list: %d hours %d minutes\n", hours, minutes);
                break;
            }

            case 6:
                printf("Total bill: ₹%.2f\n", calculateTotalBill());
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
