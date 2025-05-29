#include <stdio.h>
#include <stdlib.h>

// Common Node structure for both Queue and Stack
struct Node {
    int token;
    struct Node* next;
};

// Queue structure
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Stack structure
struct Stack {
    struct Node* top;
};

// Initialize Queue
void initQueue(struct Queue* q) {
    q->front = q->rear = NULL;
}

// Initialize Stack
void initStack(struct Stack* s) {
    s->top = NULL;
}

// Enqueue (add to queue)
void enqueue(struct Queue* q, int token) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->token = token;
    newNode->next = NULL;

    if (q->front == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("Token %d added to queue.\n", token);
}

// Dequeue (serve customer)
int dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty! No customers to serve.\n");
        return -1;
    }

    struct Node* temp = q->front;
    int token = temp->token;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return token;
}

// Push to stack (record served token)
void push(struct Stack* s, int token) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->token = token;
    newNode->next = s->top;
    s->top = newNode;
}

// Pop from stack (undo last serve)
int pop(struct Stack* s) {
    if (s->top == NULL) {
        printf("No served customers to undo.\n");
        return -1;
    }

    struct Node* temp = s->top;
    int token = temp->token;
    s->top = s->top->next;
    free(temp);
    return token;
}

// Display Queue
void displayQueue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = q->front;
    printf("Current Queue: ");
    while (temp) {
        printf("%d ", temp->token);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Queue q;
    struct Stack s;
    int choice, token = 1, servedToken;

    initQueue(&q);
    initStack(&s);

    printf("\nBanking Token System\n");
    printf("1. New Customer (Enqueue)\n");
    printf("2. Serve Customer (Dequeue)\n");
    printf("3. Undo Last Serve (Pop from Stack)\n");
    printf("4. Display Queue\n");
    printf("5. Exit\n");

    while (choice != 5) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue(&q, token++);
                break;
            case 2:
                servedToken = dequeue(&q);
                if (servedToken != -1) {
                    printf("Served Token: %d\n", servedToken);
                    push(&s, servedToken);
                }
                break;
            case 3:
                servedToken = pop(&s);
                if (servedToken != -1) {
                    printf("Undo Serve: Token %d is back in queue.\n", servedToken);
                    enqueue(&q, servedToken);
                }
                break;
            case 4:
                displayQueue(&q);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}