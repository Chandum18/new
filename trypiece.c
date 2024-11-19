#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reservation {
    struct reservation *prev;
    struct reservation *next;
    int tbnum;
    char name[100];
    int reserved;
};

struct reservation* head = NULL;
char name[100];
int n;

void createreservation() {
    struct reservation *new_reservation, *temp;
    temp = head;
    while (temp != NULL) {
        if (temp->tbnum == n) {
            printf("Table %d is already reserved by %s.\n", n, temp->name);
            return;
        }
        temp = temp->next;
    }
    new_reservation = (struct reservation*)malloc(sizeof(struct reservation));
    new_reservation->tbnum = n;
    strcpy(new_reservation->name, name);
    new_reservation->reserved = 1;
    new_reservation->next = NULL;
    new_reservation->prev = NULL;
    if (head == NULL) {
        head = new_reservation;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_reservation;
        new_reservation->prev = temp;
    }
    printf("Table %d successfully reserved for %s.\n", n, name);
}

void requestTable() {
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
  //  name[strcspn(name, "\n")] = '\0';
    printf("Enter table number (1-10): ");
    scanf("%d", &n);
    getchar();
    if (n < 1 || n > 10) {
        printf("Invalid table number. Please try again.\n");
        return;
    }
    createreservation();
}

void cancelreservation() {
    int cancel_tbnum;
    struct reservation *temp = head;
    printf("Enter table number to cancel reservation (1-10): ");
    scanf("%d", &cancel_tbnum);
    getchar();
    if (cancel_tbnum < 1 || cancel_tbnum > 10) {
        printf("Invalid table number. Please try again.\n");
        return;
    }
    while (temp != NULL && temp->tbnum != cancel_tbnum) {
        temp = temp->next;
    }
    if (temp != NULL) {
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        free(temp);
        printf("Reservation for table %d canceled.\n", cancel_tbnum);
    } else {
        printf("Table %d is not reserved.\n", cancel_tbnum);
    }
}

void printreservations() {
	int i;
    struct reservation *temp = head;
    printf("Table Number   Reserved By(or)available\n");
    printf("--------------------------\n");
    for ( i = 1; i <= 10; i++) {
        temp = head;
        int found = 0;
        while (temp != NULL) {
            if (temp->tbnum == i) {
                printf("%d              %s", i, temp->name);
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            printf("%d              Available\n", i);
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nRestaurant Reservation System\n");
        printf("1. Display Tables\n");
        printf("2. Reserve Table\n");
        printf("3. Cancel Reservation\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printreservations();
                break;
            case 2:
                requestTable();
                break;
            case 3:
                cancelreservation();
                break;
            case 4:
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

