#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void SearchOrder();
int ChangeOrder();
int BillCalculation();
int Delivery();
void registration();
void Order();
void DisplayOrder();
int CancelOrder();
int recursiveSum(int arr[], int index, int n);

int main() {
    int view, Yes, yes, bill = 0, again = 1;

    printf("============================================================\n");
    printf("                          Welcome!                          \n");
    printf("============================================================\n\n");

    while (again == 1) {
    	
    	
    	getchar();
    	
        registration();
        Order();

        printf("\nDo you want to view your the order? Press 1: ");
        scanf("%d", &view);
        if (view == 1) DisplayOrder();

        printf("\nDo you want to search any order? If yes, press 1: ");
        scanf("%d", &Yes);
        if (Yes == 1) SearchOrder();

        printf("\nDo you want to change your order? If yes, press 1: ");
        scanf("%d", &yes);
        if (yes == 1) ChangeOrder();

        printf("\nDo you want to calculate your bill? Press 1: ");
        int billChoice;
        scanf("%d", &billChoice);
        if (billChoice == 1) bill = BillCalculation();

        bill = Delivery(bill);
        printf("\n");
        printf("============================================================\n");
        printf("                Final total amount: %d RS                   \n", bill);
        printf("============================================================\n");
		printf("\n");
		
        CancelOrder();
        printf("\nNext customer please, press 1 to order: ");
        scanf("%d", &again);
    }

    printf("============================================================\n");
    printf("               Thank you for using the system!              \n");
    printf("============================================================\n");

    return 0;
}



void SearchOrder() {
    FILE *ptr = fopen("OrderFile.txt", "r");
    if (!ptr) {
        printf("Error opening file!\n");
        return;
    }

    char search[50];
    printf("Enter OrderID: ");
    scanf("%49s", search);

    char line[200];
    char block[5000] = "";   
    int found = 0;

    while (fgets(line, sizeof(line), ptr)) {

        
        if (strncmp(line, "Name:", 5) == 0) {
            block[0] = '\0'; 
        }

        strcat(block, line); 

      
        char fileOrderID[50];
        if (sscanf(line, "OrderID: %49s", fileOrderID) == 1) {

            if (strcmp(fileOrderID, search) == 0) {
            	
				printf("============================================================\n");
                printf("                          Order Found                       \n");
                printf("============================================================\n");
                printf("%s", block);

                found = 1;
                break;
            }
        }
    }

    if (!found)
        printf("\nOrder NOT found!\n");

    fclose(ptr);
}



void registration() {
    srand(time(NULL));
    char Name[100], Email[100];
    int Number;

    printf("\nTo proceed with your order you need to register first!\n");
    
	getchar(); 
    printf("Enter your name: ");
    
    fgets(Name, 100, stdin);

    printf("Enter your email: ");
    fgets(Email, 100, stdin);

    printf("Enter your Number: ");
    scanf("%d", &Number);
    getchar();

    FILE *ptr = fopen("OrderFile.txt", "a");
    if (!ptr) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(ptr, "Name: %s", Name);
    fprintf(ptr, "Email: %s", Email);
    fprintf(ptr, "Number: %d\n", Number);

    int r = rand() ; 
    fprintf(ptr, "OrderID: %d\n", r);
    printf("Your OrderID is: %d\n", r);

    fclose(ptr);
    printf("Registration saved successfully!\n");
}

void Order() {
	
    int items, menu;
    
    printf("============================================================\n");
    printf("                   Here is the Menu:                      \n");
    printf("============================================================\n");
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
    printf("============================================================\n");

    printf("How many items you want to buy?: ");
    scanf("%d", &items);

    while (items > 0) {
        printf("Enter the item you want to order: ");
        scanf("%d", &menu);

        FILE *ptr = fopen("OrderFile.txt", "a");
        if (!ptr) { printf("Error opening file!\n"); return; }

        if (menu == 1)      fprintf(ptr, "Item: Vegetable Chowmein\n");
        else if (menu == 2) fprintf(ptr, "Item: Chicken Chowmein\n");
        else if (menu == 3) fprintf(ptr, "Item: Mongolian Chicken\n");
        else if (menu == 4) fprintf(ptr, "Item: Kung Pao Chicken\n");
        else if (menu == 5) fprintf(ptr, "Item: Red Dragon Chicken\n");
        else if (menu == 6) fprintf(ptr, "Item: Dynamite Prawns\n");
        else if (menu == 7) fprintf(ptr, "Item: Mongolian Veal Ribs\n");
        else if (menu == 8) fprintf(ptr, "Item: Beef Steak with Pepper Sauce\n");
        else if (menu == 9) fprintf(ptr, "Item: Chocolate Lava Cake\n");
        else if (menu == 10) fprintf(ptr, "Item: Beef Steak\n");
        else {
            printf("Invalid item! Try again.\n");
            fclose(ptr);
            continue;
        }

        fclose(ptr);
        items--;
    }
}


void DisplayOrder() {
    FILE *ptr = fopen("OrderFile.txt", "r");

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

    printf("============================================================\n");
    printf("                        ORDER DETAILS                       \n");
    printf("============================================================\n");
    printf("%s", orderLines);
	printf("============================================================\n\n");
	
    fclose(ptr);
}


int CancelOrder() {
    char cancelID[50];
    int cancel;
    
    printf("Press 1 if you want to cancel your order: ");
    scanf("%d" , &cancel);
    
    if (cancel == 1) {
    	
    	printf("Enter the OrderID to cancel: ");
    scanf("%s", cancelID);

    FILE *ptr = fopen("OrderFile.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!ptr || !temp) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[200];
    char fileOrderID[50];
    int skip = 0; 
    int found = 0;

    while (fgets(line, sizeof(line), ptr)) {
        if (sscanf(line, "OrderID: %s", fileOrderID) == 1) {
            if (strcmp(fileOrderID, cancelID) == 0) {
                found = 1;
                skip = 1; 
                continue; 
            } else {
                skip = 0; 
            }
        }

        if (!skip) {
            fprintf(temp, "%s", line);
        }
    }

    fclose(ptr);
    fclose(temp);

    remove("OrderFile.txt");
    rename("temp.txt", "OrderFile.txt");

    if (found) {
    	
    	printf("============================================================\n");
        printf("           Order %s cancelled successfully!       \n", cancelID);
        printf("============================================================\n");
        return 1;
    } else {
        printf("OrderID not found!\n");
        return 0;
    }
    	
	}
	
	else{
		
		printf("Order is not cancelled!");
	}
    
}



int ChangeOrder() {
    FILE *ptr, *temp;
    char line[200];
    char searchID[50];
    int found = 0;

    printf("Enter OrderID to change: ");
    scanf("%s", searchID);

    ptr = fopen("OrderFile.txt", "r");
    temp = fopen("temp.txt", "w");

    if (!ptr || !temp) {
        printf("Error opening file!\n");
        return 0;
    }

    char fileOrderID[50];

    while (fgets(line, sizeof(line), ptr)) {
        if (sscanf(line, "OrderID: %s", fileOrderID) == 1 &&
            strcmp(fileOrderID, searchID) == 0) {

            found = 1;
            fprintf(temp, "%s", line);

            printf("Order found! Enter new order details.\n");
            printf("============================================================\n");
            printf("            Here is the Menu for your reference:            \n");
            printf("============================================================\n");
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
            printf("============================================================\n");

            int items, menu;
            printf("How many items in new order? ");
            scanf("%d", &items);

            while (items--) {
                printf("Enter new item number: ");
                scanf("%d", &menu);

                if (menu == 1) fprintf(temp, "Item: Vegetable Chowmein\n");
                else if (menu == 2) fprintf(temp, "Item: Chicken Chowmein\n");
                else if (menu == 3) fprintf(temp, "Item: Mongolian Chicken\n");
                else if (menu == 4) fprintf(temp, "Item: Kung Pao Chicken\n");
                else if (menu == 5) fprintf(temp, "Item: Red Dragon Chicken\n");
                else if (menu == 6) fprintf(temp, "Item: Dynamite Prawns\n");
                else if (menu == 7) fprintf(temp, "Item: Mongolian Veal Ribs\n");
                else if (menu == 8) fprintf(temp, "Item: Beef Steak with Pepper Sauce\n");
                else if (menu == 9) fprintf(temp, "Item: Chocolate Lava Cake\n");
                else if (menu == 10) fprintf(temp, "Item: Beef Steak\n");
            }

            
            while (fgets(line, sizeof(line), ptr)) {
                if (strncmp(line, "Name:", 5) == 0) break;
            }

            if (!feof(ptr))
                fprintf(temp, "%s", line);
        }
        else {
            fprintf(temp, "%s", line);
        }
    }

    fclose(ptr);
    fclose(temp);

    remove("OrderFile.txt");
    rename("temp.txt", "OrderFile.txt");

    if (found)
        printf("Order updated successfully!\n");
    else
        printf("OrderID not found!\n");

    return found;
}


int Delivery(int bill) {
    int choice;
    char address[200];

    printf("\nSelect Order Collection Method\n");
    printf("1. Delivery\n2. Pickup\nEnter your choice: ");
    scanf("%d", &choice);


    if (choice == 1) {
        getchar();
        printf("Enter your delivery address: ");
        gets(address);

        printf("Collection Method: Home Delivery\n");
        

        bill += 50;
        printf("\n");
        printf("Your bill now is %d RS including 50 RS delivery charges.\n", bill);
        printf("Your order will be delivered shortly!\n");
    } else {
        printf("Collection Method: Pickup\n");
        printf("You selected Pickup.\n");
    }

    return bill;
}

int BillCalculation() {
    FILE *ptr = fopen("OrderFile.txt", "r");
    char line[200];
    int price[200], count = 0;

    if (!ptr) { printf("Error opening file!\n"); return 0; }

    int lastOrder = 0;

    while (fgets(line, sizeof(line), ptr)) {
        if (strncmp(line, "OrderID:", 8) == 0) {
            count = 0;
            lastOrder = 1;
        }
        if (!lastOrder) continue;

        if (strncmp(line, "Item: Vegetable Chowmein", 24) == 0) price[count++] = 500;
        else if (strncmp(line, "Item: Chicken Chowmein", 22) == 0) price[count++] = 750;
        else if (strncmp(line, "Item: Mongolian Chicken", 23) == 0) price[count++] = 520;
        else if (strncmp(line, "Item: Kung Pao Chicken", 22) == 0) price[count++] = 820;
        else if (strncmp(line, "Item: Red Dragon Chicken", 23) == 0) price[count++] = 700;
        else if (strncmp(line, "Item: Dynamite Prawns", 21) == 0) price[count++] = 580;
        else if (strncmp(line, "Item: Mongolian Veal Ribs", 24) == 0) price[count++] = 780;
        else if (strncmp(line, "Item: Beef Steak with Pepper Sauce", 33) == 0) price[count++] = 540;
        else if (strncmp(line, "Item: Chocolate Lava Cake", 25) == 0) price[count++] = 880;
        else if (strncmp(line, "Item: Beef Steak", 16) == 0) price[count++] = 750;
    }

    fclose(ptr);
    int total = recursiveSum(price, 0, count);
    printf("Your total bill is: %d RS\n", total);
    return total;
}


int recursiveSum(int arr[], int index, int n) {
    if (index == n) return 0;
    return arr[index] + recursiveSum(arr, index + 1, n);
}

