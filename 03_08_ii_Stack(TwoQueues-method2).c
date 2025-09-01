#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure
struct Queue {
    int arr[MAX];
    int front, rear;
};

// Initialize queue
void init(struct Queue* q) {
    q->front = q->rear = -1;
}

// Check if empty
int isEmpty(struct Queue* q) {
    return q->front == -1;
}

// Check if full
int isFull(struct Queue* q) {
    return q->rear == MAX - 1;
}

// Enqueue operation
void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (isEmpty(q))
        q->front = 0;
    q->arr[++(q->rear)] = value;
}

// Dequeue operation
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

// Peek front element
int front(struct Queue* q) {
    if (isEmpty(q))
        return -1;
    return q->arr[q->front];
}

// Stack using two queues
struct Stack {
    struct Queue q1, q2;
};

// Initialize stack
void initStack(struct Stack* s) {
    init(&s->q1);
    init(&s->q2);
}

// Push operation (efficient)
void push(struct Stack* s, int value) {
    enqueue(&s->q1, value);
    printf("Pushed %d\n", value);
}

// Pop operation (costly)
void pop(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is EMPTY!\n");
        return;
    }

    // Leave last element in q1, move others to q2
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Last element (the stack top)
    int popped = dequeue(&s->q1);
    printf("Popped %d\n", popped);

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

// Top element
void top(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is EMPTY!\n");
        return;
    }

    // Leave last element in q1, move others to q2
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    int topElement = front(&s->q1);
    printf("Top element: %d\n", topElement);

    // Move it to q2 as well
    enqueue(&s->q2, dequeue(&s->q1));

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

// Display stack
void display(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is EMPTY!\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = s->q1.front; i <= s->q1.rear; i++) {
        printf("%d ", s->q1.arr[i]);
    }
    printf("\n");
}

// Driver code
int main() {
    struct Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    display(&s);

    pop(&s);
    display(&s);

    top(&s);
    push(&s, 40);
    display(&s);

    return 0;
}
