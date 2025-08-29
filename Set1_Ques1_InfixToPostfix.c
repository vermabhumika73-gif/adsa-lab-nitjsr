#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// ---------- Stack for characters (operators) ----------
char opStack[MAX];
int topOp = -1;

void pushOp(char c) {
    if (topOp < MAX - 1) {
        opStack[++topOp] = c;
    }
}

char popOp() {
    if (topOp >= 0) {
        return opStack[topOp--];
    }
    return '\0';
}

char peekOp() {
    if (topOp >= 0) {
        return opStack[topOp];
    }
    return '\0';
}

// ---------- Stack for integers (evaluation) ----------
int valStack[MAX];
int topVal = -1;

void pushVal(int v) {
    if (topVal < MAX - 1) {
        valStack[++topVal] = v;
    }
}

int popVal() {
    if (topVal >= 0) {
        return valStack[topVal--];
    }
    return 0;
}

// ---------- Precedence function ----------
int precedence(char op) {
    switch (op) {
        case '/': return 3;
        case '*': return 3;
        case '+': return 2;
        case '-': return 2;
        case '(': return 1;
    }
    return 0;
}

// ---------- Convert infix to postfix ----------
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        if (isdigit(c)) {
            postfix[k++] = c;
        }
        else if (c == '(') {
            pushOp(c);
        }
        else if (c == ')') {
            while (topOp != -1 && peekOp() != '(') {
                postfix[k++] = popOp();
            }
            popOp(); // remove '('
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (topOp != -1 && precedence(peekOp()) >= precedence(c)) {
                postfix[k++] = popOp();
            }
            pushOp(c);
        }
    }

    while (topOp != -1) {
        postfix[k++] = popOp();
    }

    postfix[k] = '\0';
}

// ---------- Evaluate postfix expression ----------
int evaluatePostfix(char postfix[]) {
    int i;
    char c;

    for (i = 0; postfix[i] != '\0'; i++) {
        c = postfix[i];

        if (isdigit(c)) {
            pushVal(c - '0');  // convert char digit to int
        } else {
            int b = popVal();
            int a = popVal();
            switch (c) {
                case '+': pushVal(a + b); break;
                case '-': pushVal(a - b); break;
                case '*': pushVal(a * b); break;
                case '/': pushVal(a / b); break;  // assume b != 0
            }
        }
    }
    return popVal();
}

// ---------- Main ----------
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"infix_expression\"\n", argv[0]);
        return 1;
    }

    char postfix[MAX];
    infixToPostfix(argv[1], postfix);

    int result = evaluatePostfix(postfix);

    printf("Infix Expression : %s\n", argv[1]);
    printf("Postfix Form     : %s\n", postfix);
    printf("Result           : %d\n", result);

    return 0;
}
