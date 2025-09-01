#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 100

char stack[MAX];
int top = -1;

int valStack[MAX];
int valTop = -1;

// Precedence: / > * > + > -
int preced(char op) {
    if (op == '/')
        return 4;   // highest
    else if (op == '*')
        return 3;
    else if (op == '+')
        return 2;
    else if (op == '-')
        return 1;   // lowest
    else
        return 0;
}

// Operator stack
void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}
char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}
char peek() {
    if (top >= 0) {
        return stack[top];
    }
    return '\0';
}

// Infix -> Postfix (multi-digit numbers supported)
void infixtopostfix(char infix[], char postfix[]) {
    int k = 0;
    char c;

    for (int i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        if (isdigit(c)) {  
            // read full number
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' '; // separator
            i--; // adjust index
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            pop(); // remove '('
        }
        else { // operator
            while (top != -1 && preced(peek()) >= preced(c)) {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[k++] = pop();
        postfix[k++] = ' ';
    }

    postfix[k] = '\0'; // null terminate
}

// Value stack
void pushVal(int val) {
    if (valTop < MAX - 1) {
        valStack[++valTop] = val;
    }
}
int popVal() {
    if (valTop >= 0) {
        return valStack[valTop--];
    }
    return 0;
}

// Evaluate postfix (multi-digit numbers supported)
int evaluatePostfix(char postfix[]) {
    int i = 0;
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushVal(num);
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || 
                 postfix[i] == '*' || postfix[i] == '/') {
            int val2 = popVal();
            int val1 = popVal();
            int res = 0;

            switch (postfix[i]) {
                case '+': res = val1 + val2; break;
                case '-': res = val1 - val2; break;
                case '*': res = val1 * val2; break;
                case '/': res = val1 / val2; break;
            }
            pushVal(res);
        }
        i++;
    }
    return popVal();
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter the Expression : ");
    scanf("%[^\n]s", infix);   // allows spaces too

    infixtopostfix(infix, postfix);
    printf("\nThe postfix Expression : %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result = %d\n", result);

    return 0;
}
