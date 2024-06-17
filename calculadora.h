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

// Estrutura da pilha para strings
typedef struct
{
    char **data;
    int top;
    int capacity;
} StringStack;

// Funções da pilha
Stack *createStack(int capacity);
int isFull(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, double item);
double pop(Stack *stack);
double peek(Stack *stack);

// Funções da pilha de strings
StringStack *createStringStack(int capacity);
int isStringStackFull(StringStack *stack);
int isStringStackEmpty(StringStack *stack);
void pushString(StringStack *stack, const char *item);
char *popString(StringStack *stack);

// Funções para operações
int isOperator(char c);
double performOperation(double a, double b, char operator);
double performSpecialOperation(const char *operation, double operand);
double evaluatePostfix(const char *expression);

// Função para imprimir a expressão pós-fixa em notação infixada
void printInfix(const char *expression);

#endif // CALCULADORA_H
