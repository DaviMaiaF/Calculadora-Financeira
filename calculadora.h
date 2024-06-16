#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Estrutura da pilha
typedef struct
{
    double *data;
    int top;
    int capacity;
} Stack;

// Funções da pilha
Stack *createStack(int capacity);
int isFull(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, double item);
double pop(Stack *stack);
double peek(Stack *stack);

// Funções para operações
int isOperator(char c);
double performOperation(double a, double b, char operator);
double performSpecialOperation(const char *operation, double operand);
double evaluatePostfix(const char *expression);

#endif // STACK_H
