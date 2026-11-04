#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100

struct Item {
    int id;
    char type[10];
    char name[50];
    char category[30];
    char color[30];
    char brand[30];
    char location[50];
    char date[20];
    char privateClue[80];
    char status[30];
};

struct Item items[MAX_ITEMS];
int itemCount = 0;

/* Save records in file */
void saveData() {
    FILE *fp = fopen("campus_data.dat", "wb");
    if (fp == NULL) {
        printf("\nError saving data!\n");
        return;
    }
    fwrite(&itemCount, sizeof(int), 1, fp);
    fwrite(items, sizeof(struct Item), itemCount, fp);
    fclose(fp);
}

/* Load previous records */
void loadData() {
    FILE *fp = fopen("campus_data.dat", "rb");
    if (fp == NULL) {
        itemCount = 0;
        return;
    }
    int count;
    if (fread(&count, sizeof(int), 1, fp) != 1 || count < 0 || count > MAX_ITEMS) {
        itemCount = 0;
        fclose(fp);
        return;
    }
    if (fread(items, sizeof(struct Item), count, fp) != count) {
        itemCount = 0;
        fclose(fp);
        return;
    }
    itemCount = count;
    fclose(fp);
    printf("\nPrevious records loaded successfully!\n");
}

/* Read text input securely */
void readLine(char text[], int size) {
    fgets(text, size, stdin);
    text[strcspn(text, "\n")] = '\0';
}

/* Register lost or found item */
void addItem(char type[]) {
    struct Item newItem;
    if (itemCount >= MAX_ITEMS) {
        printf("\nStorage is full!\n");
        return;
    }

    // Assigning ID securely based on previous index position
    newItem.id = itemCount + 1; 
    strcpy(newItem.type, type);

    printf("\nEnter item name: ");
    readLine(newItem.name, 50);

    printf("Enter category: ");
    readLine(newItem.category, 30);

    printf("Enter colour: ");
    readLine(newItem.color, 30);

    printf("Enter brand: ");
    readLine(newItem.brand, 30);

    printf("Enter location: ");
    readLine(newItem.location, 50);

    printf("Enter date (DD-MM-YYYY): ");
    readLine(newItem.date, 20);

    if (strcmp(type, "LOST") == 0) {
        printf("Enter a private ownership clue: ");
        readLine(newItem.privateClue, 80);
    } else {
        strcpy(newItem.privateClue, "");
    }

    strcpy(newItem.status, "Reported");
    items[itemCount] = newItem;
    itemCount++;
    
    saveData();
    printf("\nItem registered successfully!\n");
    printf("Your Item ID is: %d\n", newItem.id);
}

/* Display all item reports */
void viewItems() {
    if (itemCount == 0) {
        printf("\nNo items registered yet.\n");
        return;
    }
    printf("\n========== ITEM REPORTS ==========\n");
    for (int i = 0; i < itemCount; i++) {
        printf("\nItem ID: %d\n", items[i].id);
        printf("Type: %s\n", items[i].type);
        printf("Name: %s\n", items[i].name);
        printf("Category: %s\n", items[i].category);
        printf("Colour: %s\n", items[i].color);
        printf("Brand: %s\n", items[i].brand);
        printf("Location: %s\n", items[i].location);
        printf("Date: %s\n", items[i].date);
        printf("Status: %s\n", items[i].status);
        printf("----------------------------------\n");
    }
}

/* Calculate matching score */
int calculateMatch(struct Item lost, struct Item found) {
    int score = 0;
    if (strcasecmp(lost.category, found.category) == 0) score += 20; // Used case-insensitive comparison
    if (strcasecmp(lost.name, found.name) == 0) score += 15;
    if (strcasecmp(lost.color, found.color) == 0) score += 20;
    if (strcasecmp(lost.brand, found.brand) == 0) score += 20;
    if (strcasecmp(lost.location, found.location) == 0) score += 15;
    if (strcmp(lost.date, found.date) == 0) score += 10;
    return score;
}

/* Find possible matches */
void viewMatches() {
    int foundMatch = 0;
    printf("\n========== POSSIBLE MATCHES ==========\n");
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(items[i].type, "LOST") == 0) {
            for (int j = 0; j < itemCount; j++) {
                if (strcmp(items[j].type, "FOUND") == 0) {
                    int score = calculateMatch(items[i], items[j]);
                    if (score >= 40) {
                        foundMatch = 1;
                        printf("\nLost Item ID: %d | Found Item ID: %d\n", items[i].id, items[j].id);
                        printf("Item Name: %s\n", items[i].name);
                        printf("Match Score: %d/100\n", score);
                        if (score >= 80) printf("Priority: High\n");
                        else if (score >= 60) printf("Priority: Moderate\n");
                        else printf("Priority: Low\n");
                        printf("----------------------------------\n");
                    }
                }
            }
        }
    }
    if (foundMatch == 0) printf("\nNo possible matches found yet.\n");
}

/* Verify ownership using private clue */
void verifyOwnership() {
    int id;
    char clue[80];
    printf("\n========== OWNERSHIP VERIFICATION ==========\n");
    printf("Enter your Lost Item ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid numeric entry.\n");
        while (getchar() != '\n');
        return;
    }
    getchar(); // Clear buffer newline

    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id && strcmp(items[i].type, "LOST") == 0) {
            printf("Enter your private ownership clue: ");
            readLine(clue, 80);
            if (strcmp(clue, items[i].privateClue) == 0) {
                strcpy(items[i].status, "Pending Staff Approval");
                saveData();
                printf("\nVerification successful!\n");
                printf("Claim status: Pending Staff Approval\n");
            } else {
                printf("\nVerification failed!\n");
                printf("The clue does not match.\n");
            }
            return;
        }
    }
    printf("\nInvalid Lost Item ID!\n");
}

/* Staff approval of recovery */
void approveRecovery() {
    int id;
    printf("\n========== STAFF APPROVAL ==========\n");
    printf("Enter Lost Item ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id && strcmp(items[i].type, "LOST") == 0) {
            if (strcmp(items[i].status, "Pending Staff Approval") == 0) {
                strcpy(items[i].status, "Recovered");
                saveData();
                printf("\nItem recovery approved!\n");
                printf("Status: Recovered\n");
            } else {
                printf("\nThis item is not pending approval.\n");
            }
            return;
        }
    }
    printf("\nInvalid Lost Item ID!\n");
}

int main() {
    int choice;
    loadData();
    do {
        printf("\n====================================\n");
        printf("           CAMPUS RECOVER\n");
        printf("====================================\n");
        printf("1. Report Lost Item\n");
        printf("2. Report Found Item\n");
        printf("3. View All Items\n");
        printf("4. Find Possible Matches\n");
        printf("5. Verify Item Ownership\n");
        printf("6. Staff: Approve Recovery\n");
        printf("7. Exit\n");
        printf("\nEnter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar(); // consume trailing newline

        switch (choice) {
            case 1: addItem("LOST"); break;
            case 2: addItem("FOUND"); break;
            case 3: viewItems(); break;
            case 4: viewMatches(); break;
            case 5: verifyOwnership(); break;
            case 6: approveRecovery(); break;
            case 7: saveData(); printf("\nThank you for using CampusRecover!\n"); break;
            default: printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 7);
    return 0;
}
