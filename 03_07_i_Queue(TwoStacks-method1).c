#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
struct Stack {
    int arr[MAX];
    int top;
};

// Initialize stack
void init(struct Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

// Push into stack
void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

// Pop from stack
int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

// Peek top element
int peek(struct Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->arr[s->top];
}

// Queue using two stacks
struct Queue {
    struct Stack s1, s2;
};

// Initialize queue
void initQueue(struct Queue* q) {
    init(&q->s1);
    init(&q->s2);
}

// Enqueue operation (costly)
void enqueue(struct Queue* q, int value) {
    // Move all elements from s1 to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Push new element into s1
    push(&q->s1, value);

    // Move everything back to s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }

    printf("Enqueued %d\n", value);
}

// Dequeue operation (efficient)
void dequeue(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is EMPTY!\n");
        return;
    }
    int x = pop(&q->s1);
    printf("Dequeued %d\n", x);
}

// Display queue
void display(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = 0; i <= q->s1.top; i++) {
        printf("%d ", q->s1.arr[i]);
    }
    printf("\n");
}

int main() {
    struct Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);

    dequeue(&q);
    display(&q);

    enqueue(&q, 40);
    display(&q);

    return 0;
}
