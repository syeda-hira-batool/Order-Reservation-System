#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
 
void SearchOrder(); 
int ChangeOrder(); 
void BillCalculation(); 
void Delivery();
void registration();
void Order();
void DisplayOrder();
int CancelOrder();

int main() {
    int view, Yes, yes;

    printf("Welcome!\n");

    registration();
    Order();

    printf("\nDo you want to view your order? Press 1: ");
    scanf("%d", &view);
    if (view == 1) DisplayOrder();

    printf("\nDo you want to search your order? If yes, press 1: ");
    scanf("%d", &Yes);
    if (Yes == 1) SearchOrder();

    printf("\nDo you want to change your order? If yes, press 1: ");
    scanf("%d", &yes);
    if (yes == 1) ChangeOrder();

    printf("\nDo you want to calculate your bill? Press 1: ");
    int billChoice;
    scanf("%d", &billChoice);
    if (billChoice == 1) BillCalculation();

    Delivery();
    CancelOrder();

    return 0;
}


void registration() {
    srand(time(NULL));

    char Name[100];
    char Email[100];
    int Number;

    printf("\nTo proceed with your order you need to register\n");

    getchar();
    printf("Enter your name: ");
    fgets(Name, 100, stdin);

    printf("Enter your email: ");
    fgets(Email, 100, stdin);

    printf("Enter your Number: ");
    scanf("%d", &Number);

    FILE *ptr = fopen("OrderFile.txt", "a");

    fprintf(ptr, "Name: %s", Name);
    fprintf(ptr, "Email: %s", Email);
    fprintf(ptr, "Number: %d\n", Number);

    int r = rand() % 90000 + 10000;
    fprintf(ptr, "OrderID: %d\n", r);
    printf("Your OrderID is: %d\n", r);

    fclose(ptr);

    printf("Registration saved successfully!\n");
}

void Order() {
    int items, menu;

    printf("Here is the Menu:\n");
    printf("1. Vegetable Chowmein------------------------------ 500RS\n");
    printf("2. Chicken Chowmein-------------------------------- 750RS\n");
    printf("3. Mongolian Chicken------------------------------- 520RS\n");
    printf("4. Kung Pao Chicken-------------------------------- 820RS\n");
    printf("5. Red Dragon Chicken------------------------------ 700RS\n");
    printf("6. Dynamite Prawns--------------------------------- 580RS\n");
    printf("7. Mongolian Veal Ribs----------------------------- 780RS\n");
    printf("8. Beef Steak with Pepper Sauce-------------------- 540RS\n");
    printf("9. Chocolate Lava Cake----------------------------- 880RS\n");
    printf("10. Beef Steak------------------------------------- 750RS\n");

    printf("How many items you want to buy?: ");
    scanf("%d", &items);

    FILE *ptr = fopen("OrderFile.txt", "a");

    while (items > 0) {
        printf("Enter the item you want to order: ");
        scanf("%d", &menu);

        if (menu == 1) fprintf(ptr, "Item: Vegetable Chowmein\n");
        else if (menu == 2) fprintf(ptr, "Item: Chicken Chowmein\n");
        else if (menu == 3) fprintf(ptr, "Item: Mongolian Chicken\n");
        else if (menu == 4) fprintf(ptr, "Item: Kung Pao Chicken\n");
        else if (menu == 5) fprintf(ptr, "Item: Red Dragon Chicken\n");
        else if (menu == 6) fprintf(ptr, "Item: Dynamite Prawns\n");
        else if (menu == 7) fprintf(ptr, "Item: Mongolian Veal Ribs\n");
        else if (menu == 8) fprintf(ptr, "Item: Beef Steak with Pepper Sauce\n");
        else if (menu == 9) fprintf(ptr, "Item: Chocolate Lava Cake\n");
        else if (menu == 10) fprintf(ptr, "Item: Beef Steak\n");
        else { printf("Invalid item! Try again.\n"); items++; continue; }

        items--;
    }

    fclose(ptr);
}


void DisplayOrder() {
    FILE *ptr = fopen("OrderFile.txt", "r");
    if (!ptr) { printf("Error opening file!\n"); return; }

    char line[500];
    char lastOrderID[50] = "";
    char orderLines[2000] = "";

    while (fgets(line, sizeof(line), ptr)) {
        if (strncmp(line, "OrderID:", 8) == 0) {
            strcpy(lastOrderID, line);
            orderLines[0] = '\0'; 
        }
        if (lastOrderID[0] != '\0') {
            strcat(orderLines, line);
        }
    }

    printf("\n--- YOUR ORDER DETAILS ---\n");
    printf("%s", orderLines);

    fclose(ptr);
}

int CancelOrder() {
    int Cancel;
    printf("Do you want to cancel the order? Press 1 for Yes and 0 for No: ");
    scanf("%d", &Cancel);

    if (Cancel == 1) {
        printf("Your order is cancelled.\n");
        return 1;
    } else {
        printf("Your order is NOT cancelled.\n");
        return 0;
    }
}


