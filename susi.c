#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Attendance {
    char studentID[20];
    char date[15];
    char status[10]; // "Present" or "Absent"
    struct Attendance *next;
} Attendance;

// Function Prototypes
Attendance* addRecord(Attendance *head);
Attendance* deleteRecord(Attendance *head);
void searchRecord(Attendance *head);
void displayByDate(Attendance *head);
void displayReverse(Attendance *head);
Attendance* cloneList(Attendance *head);
void displayAll(Attendance *head);
void freeList(Attendance *head);

int main() {
    Attendance *head = NULL;
    Attendance *adminCopy = NULL;
    int choice;

    do {
        printf("\n=== Student Attendance Monitoring System ===\n");
        printf("1. Add Attendance Record\n");
        printf("2. Delete Incorrect Entry\n");
        printf("3. Search Attendance by Student ID and Date\n");
        printf("4. Display Attendance List for a Date\n");
        printf("5. Reverse Attendance Display\n");
        printf("6. Clone for Admin Review\n");
        printf("7. Display All Records\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch(choice) {
            case 1:
                head = addRecord(head);
                break;
            case 2:
                head = deleteRecord(head);
                break;
            case 3:
                searchRecord(head);
                break;
            case 4:
                displayByDate(head);
                break;
            case 5:
                printf("\nReversed Attendance List:\n");
                displayReverse(head);
                break;
            case 6:
                adminCopy = cloneList(head);
                printf("\nAdmin clone created successfully!\n");
                printf("Displaying cloned list:\n");
                displayAll(adminCopy);
                break;
            case 7:
                displayAll(head);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);

    freeList(head);
    freeList(adminCopy);
    return 0;
}

// ---------------- Function Definitions ----------------

Attendance* addRecord(Attendance *head) {
    Attendance *newNode = (Attendance*)malloc(sizeof(Attendance));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return head;
    }

    printf("Enter Student ID: ");
    fgets(newNode->studentID, sizeof(newNode->studentID), stdin);
    newNode->studentID[strcspn(newNode->studentID, "\n")] = '\0';

    printf("Enter Date (DD-MM-YYYY): ");
    fgets(newNode->date, sizeof(newNode->date), stdin);
    newNode->date[strcspn(newNode->date, "\n")] = '\0';

    printf("Enter Status (Present/Absent): ");
    fgets(newNode->status, sizeof(newNode->status), stdin);
    newNode->status[strcspn(newNode->status, "\n")] = '\0';

    newNode->next = head;
    head = newNode;

    printf("Attendance record added successfully!\n");
    return head;
}

Attendance* deleteRecord(Attendance *head) {
    if (head == NULL) {
        printf("No records to delete.\n");
        return NULL;
    }

    char studentID[20], date[15];
    printf("Enter Student ID to delete: ");
    fgets(studentID, sizeof(studentID), stdin);
    studentID[strcspn(studentID, "\n")] = '\0';

    printf("Enter Date (DD-MM-YYYY): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';

    Attendance *temp = head, *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->studentID, studentID) == 0 && strcmp(temp->date, date) == 0) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Record deleted successfully!\n");
            return head;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Record not found!\n");
    return head;
}

void searchRecord(Attendance *head) {
    if (head == NULL) {
        printf("No records available.\n");
        return;
    }

    char studentID[20], date[15];
    printf("Enter Student ID: ");
    fgets(studentID, sizeof(studentID), stdin);
    studentID[strcspn(studentID, "\n")] = '\0';

    printf("Enter Date (DD-MM-YYYY): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';

    Attendance *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->studentID, studentID) == 0 && strcmp(temp->date, date) == 0) {
            printf("Record Found: %s | %s | %s\n", temp->studentID, temp->date, temp->status);
            return;
        }
        temp = temp->next;
    }
    printf("Record not found!\n");
}

void displayByDate(Attendance *head) {
    if (head == NULL) {
        printf("No records available.\n");
        return;
    }

    char date[15];
    printf("Enter Date (DD-MM-YYYY): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';

    Attendance *temp = head;
    int found = 0;
    printf("\nAttendance List for %s:\n", date);
    printf("----------------------------------------\n");
    while (temp != NULL) {
        if (strcmp(temp->date, date) == 0) {
            printf("Student ID: %s | Status: %s\n", temp->studentID, temp->status);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("No records found for this date.\n");
}

void displayReverse(Attendance *head) {
    if (head == NULL) return;
    displayReverse(head->next);
    printf("%s | %s | %s\n", head->studentID, head->date, head->status);
}

Attendance* cloneList(Attendance *head) {
    if (head == NULL) return NULL;

    Attendance *cloneHead = NULL, *cloneTail = NULL;
    Attendance *temp = head;

    while (temp != NULL) {
        Attendance *newNode = (Attendance*)malloc(sizeof(Attendance));
        strcpy(newNode->studentID, temp->studentID);
        strcpy(newNode->date, temp->date);
        strcpy(newNode->status, temp->status);
        newNode->next = NULL;

        if (cloneHead == NULL)
            cloneHead = cloneTail = newNode;
        else {
            cloneTail->next = newNode;
            cloneTail = newNode;
        }
        temp = temp->next;
    }
    return cloneHead;
}

void displayAll(Attendance *head) {
    if (head == NULL) {
        printf("No records available.\n");
        return;
    }

    printf("\nAll Attendance Records:\n");
    printf("----------------------------------------\n");
    Attendance *temp = head;
    while (temp != NULL) {
        printf("%s | %s | %s\n", temp->studentID, temp->date, temp->status);
        temp = temp->next;
    }
}

void freeList(Attendance *head) {
    Attendance *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
