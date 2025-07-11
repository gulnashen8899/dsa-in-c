#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char subject[50];
    char tasks[200];
    struct Node* next;
} Node;

void addSubject(Node** head, const char* subject, const char* tasks) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Failed to allocate memory");
    }
    strncpy(newNode->subject, subject, sizeof(newNode->subject) - 1);
    strncpy(newNode->tasks, tasks, sizeof(newNode->tasks) - 1);
    newNode->next = *head;
    *head = newNode;
}

void removeSubject(Node** head, const char* subject) {
    Node* temp = *head;
    Node* prev = NULL;

    if (temp != NULL && strcmp(temp->subject, subject) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->subject, subject) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void displaySubjects(Node* node) {
    while (node != NULL) {
        printf("\nSubject: %sTasks: %s", node->subject, node->tasks);
        node = node->next;
    }
}

int main() {
    Node* head = NULL;
    int choice;
    char subject[50];
    char tasks[200];

    while (1) {
        printf("Menu:\n");
        printf("1. Add Subject\n");
        printf("2. Remove Subject\n");
        printf("3. Display Subjects\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                printf("Enter subject name: ");
                if (fgets(subject, sizeof(subject), stdin) != NULL) {
                    size_t len = strlen(subject);
                    if (len > 0 && subject[len - 1] == '\n') {
                    }
                }

                printf("Enter tasks: ");
                if (fgets(tasks, sizeof(tasks), stdin) != NULL) {
                    size_t len = strlen(tasks);
                    if (len > 0 && tasks[len - 1] == '\n') {
                    }
                }

                addSubject(&head, subject, tasks);
                break;

            case 2:
                printf("Enter subject name to remove: ");
                if (fgets(subject, sizeof(subject), stdin) != NULL) {
                    size_t len = strlen(subject);
                    if (len > 0 && subject[len - 1] == '\n') {
                    }
                }

                removeSubject(&head, subject);
                break;

            case 3:
                printf("Subjects and Tasks:\n");
                displaySubjects(head);
                break;

            case 4:
                while (head != NULL) {
                    Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}