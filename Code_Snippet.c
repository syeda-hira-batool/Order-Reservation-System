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

    return 0;
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
    long long Number;

    printf("\nTo proceed with your order you need to register first!\n");
    
	getchar(); 
    printf("Enter your name: ");
    
    fgets(Name, 100, stdin);

    printf("Enter your email: ");
    fgets(Email, 100, stdin);

    printf("Enter your Number: ");
    scanf("%lld", &Number);
    getchar();

    FILE *ptr = fopen("OrderFile.txt", "a");
    if (!ptr) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(ptr, "Name: %s", Name);
    fprintf(ptr, "Email: %s", Email);
    fprintf(ptr, "Number: +92%lld\n", Number);

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



