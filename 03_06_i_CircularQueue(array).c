#include <stdio.h>
#define SIZE 5  // maximum size of the queue

int queue[SIZE];
int front = -1, rear = -1;

// Check if queue is full
int isFull() {
    return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
}

// Check if queue is empty
int isEmpty() {
    return front == -1;
}

// Insert element in queue
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is FULL!\n");
        return;
    }
    if (front == -1)  // first element
        front = 0;
    rear = (rear + 1) % SIZE;
    queue[rear] = value;
    printf("Inserted %d\n", value);
}

// Delete element from queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Deleted %d\n", queue[front]);
    if (front == rear) { // only one element left
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
}

// Display elements
void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display();

    dequeue();
    dequeue();
    display();

    enqueue(60);
    enqueue(70);
    display();

    return 0;
}
