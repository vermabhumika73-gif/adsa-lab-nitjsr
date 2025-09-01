#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

struct Node *front = NULL, *rear = NULL;

// Enqueue operation
void enqueue(int value) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {  // First node
        front = rear = newNode;
        rear->next = front;  // circular link
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;  // maintain circular link
    }
    printf("Inserted %d\n", value);
}

// Dequeue operation
void dequeue() {
    if (front == NULL) {
        printf("Queue is EMPTY!\n");
        return;
    }

    struct Node* temp = front;

    if (front == rear) {  // only one element
        printf("Deleted %d\n", front->data);
        front = rear = NULL;
    } else {
        printf("Deleted %d\n", front->data);
        front = front->next;
        rear->next = front;  // maintain circular link
    }
    free(temp);
}

// Display operation
void display() {
    if (front == NULL) {
        printf("Queue is EMPTY!\n");
        return;
    }
    struct Node* temp = front;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();

    dequeue();
    dequeue();
    display();

    enqueue(50);
    enqueue(60);
    display();

    return 0;
}
