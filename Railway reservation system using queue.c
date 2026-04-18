#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 5
#define MAX_WAITING 100

struct Passenger {
    int id;
    char name[50];
};

struct Queue {
    struct Passenger passengers[MAX_WAITING];
    int front;
    int rear;
};

struct Passenger seats[MAX_SEATS];
int seatCount = 0;

// Queue functions
void initQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct Queue *q) {
    return (q->front == -1);
}

int isFull(struct Queue *q) {
    return (q->rear == MAX_WAITING - 1);
}

void enqueue(struct Queue *q, struct Passenger p) {
    if (isFull(q)) {
        printf("Waiting list is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->passengers[q->rear] = p;
    printf("Passenger added to waiting list.\n");
}

struct Passenger dequeue(struct Queue *q) {
    struct Passenger p = {-1, ""};

    if (isEmpty(q)) {
        printf("Waiting list is empty!\n");
        return p;
    }

    p = q->passengers[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }

    return p;
}

// Seat booking
void bookSeat(struct Queue *q) {
    struct Passenger p;

    printf("Enter Passenger ID: ");
    scanf("%d", &p.id);
    printf("Enter Passenger Name: ");
    scanf("%s", p.name);

    if (seatCount < MAX_SEATS) {
        seats[seatCount++] = p;
        printf("Seat booked successfully!\n");
    } else {
        enqueue(q, p);
    }
}

// Cancel seat
void cancelSeat(struct Queue *q) {
    int id, found = 0;

    printf("Enter Passenger ID to cancel: ");
    scanf("%d", &id);

    for (int i = 0; i < seatCount; i++) {
        if (seats[i].id == id) {
            found = 1;

            for (int j = i; j < seatCount - 1; j++) {
                seats[j] = seats[j + 1];
            }

            seatCount--;
            printf("Seat cancelled.\n");

            if (!isEmpty(q)) {
                struct Passenger p = dequeue(q);
                seats[seatCount++] = p;
                printf("Passenger from waiting list added: %s\n", p.name);
            }
            break;
        }
    }

    if (!found) {
        printf("Passenger not found.\n");
    }
}

// Display seats
void displaySeats() {
    printf("\nConfirmed Seats:\n");
    for (int i = 0; i < seatCount; i++) {
        printf("ID: %d, Name: %s\n", seats[i].id, seats[i].name);
    }
}

// Display waiting list
void displayWaiting(struct Queue *q) {
    if (isEmpty(q)) {
        printf("\nWaiting list is empty.\n");
        return;
    }

    printf("\nWaiting List:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("ID: %d, Name: %s\n", q->passengers[i].id, q->passengers[i].name);
    }
}

// Main function
int main() {
    struct Queue q;
    initQueue(&q);

    int choice;

    while (1) {
        printf("\n--- Reservation System ---\n");
        printf("1. Book Seat\n");
        printf("2. Cancel Seat\n");
        printf("3. View Seats\n");
        printf("4. View Waiting List\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookSeat(&q);
                break;
            case 2:
                cancelSeat(&q);
                break;
            case 3:
                displaySeats();
                break;
            case 4:
                displayWaiting(&q);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
