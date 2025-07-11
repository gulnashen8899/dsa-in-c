#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

struct CircularQueue {
    char *data[MAX];
    int front, rear, size;
};

struct CircularQueue* initQueue() {
    struct CircularQueue *q = (struct CircularQueue *)malloc(sizeof(struct CircularQueue));
    (*q).front = 0;
    (*q).rear = -1;
    (*q).size = 0;
    for (int i = 0; i < MAX; i++) {
        (*q).data[i] = NULL;
    }
    return q;
}

void enqueue(struct CircularQueue *q, const char *subject) {
    if ((*q).size == MAX) {
        printf("Queue is full.\n");
        return;
    }
    (*q).rear = ((*q).rear + 1) % MAX;
    (*q).data[(*q).rear] = malloc(strlen(subject) + 1);
    strcpy((*q).data[(*q).rear], subject);
    (*q).size++;
}

void dequeue(struct CircularQueue *q) {
    if ((*q).size == 0) {
        printf("Queue is empty.\n");
        return;
    }
    free((*q).data[(*q).front]);
    (*q).data[(*q).front] = NULL;
    (*q).front = ((*q).front + 1) % MAX;
    (*q).size--;
}

void rotateQueue(struct CircularQueue *q) {
    if ((*q).size <= 1) {
        printf("Queue is too small to rotate.\n");
        return;
    }
    char *temp = (*q).data[(*q).front];
    for (int i = 0; i < (*q).size - 1; i++) {
        (*q).data[((*q).front + i) % MAX] = (*q).data[((*q).front + i + 1) % MAX];
    }
    (*q).data[((*q).front + (*q).size - 1) % MAX] = temp; // Place the old front at the end
    (*q).rear = ((*q).rear + 1) % MAX;
}

void displayQueue(struct CircularQueue *q) {
    if ((*q).size == 0) {
        printf("Queue is empty.\n");
        return;
    }
    int i = (*q).front;
    for (int count = 0; count < (*q).size; count++) {
        printf("%s ", (*q).data[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    struct CircularQueue *q = initQueue();
    int choice;
    char sub[100];

    do {
        printf("\nMenu:\n");
        printf("1. Add Subject\n");
        printf("2. Remove Subject\n");
        printf("3. Rotate Queue\n");
        printf("4. Display Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                if ((*q).size < MAX) {
                    printf("Enter subject: ");
                    fgets(sub, sizeof(sub), stdin);
                    sub[strcspn(sub, "\n")] = 0; 
                    enqueue(q, sub);
                } else {
                    printf("Queue is full.\n");
                }
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                rotateQueue(q);
                break;
            case 4:
                displayQueue(q);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    } while (choice != 5);
    
}