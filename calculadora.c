#include "calculadora.h"

// Funções da pilha
Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (double *)malloc(stack->capacity * sizeof(double));
    return stack;
}

int isFull(Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, double item)
{
    if (isFull(stack))
        return;
    stack->data[++stack->top] = item;
}

double pop(Stack *stack)
{
    if (isEmpty(stack))
        return 0.0;
    return stack->data[stack->top--];
}

double peek(Stack *stack)
{
    if (isEmpty(stack))
        return 0.0;
    return stack->data[stack->top];
}

// Funções para operações
int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

double performOperation(double a, double b, char operator)
{
    switch (operator)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}

double performSpecialOperation(const char *operation, double operand)
{
    if (strcmp(operation, "raiz") == 0)
        return sqrt(operand);
    if (strcmp(operation, "sen") == 0)
        return sin(operand * M_PI / 180.0); // Converte graus para radianos
    if (strcmp(operation, "cos") == 0)
        return cos(operand * M_PI / 180.0); // Converte graus para radianos
    if (strcmp(operation, "tg") == 0)
        return tan(operand * M_PI / 180.0); // Converte graus para radianos
    if (strcmp(operation, "log") == 0)
        return log10(operand);
    return 0;
}

// Avaliação da expressão pós-fixada
double evaluatePostfix(const char *expression)
{
    Stack *stack = createStack(strlen(expression));
    char token[20];
    int i = 0, j = 0;

    while (expression[i] != '\0')
    {
        if (isspace(expression[i]))
        {
            i++;
            continue;
        }

        if (isdigit(expression[i]) || expression[i] == '.')
        {
            while (isdigit(expression[i]) || expression[i] == '.')
            {
                token[j++] = expression[i++];
            }
            token[j] = '\0';
            push(stack, atof(token));
            j = 0;
        }
        else if (isOperator(expression[i]))
        {
            double b = pop(stack);
            double a = pop(stack);
            double result = performOperation(a, b, expression[i]);
            push(stack, result);
            i++;
        }
        else if (isalpha(expression[i]))
        {
            while (isalpha(expression[i]))
            {
                token[j++] = expression[i++];
            }
            token[j] = '\0';
            double operand = pop(stack);
            double result = performSpecialOperation(token, operand);
            push(stack, result);
            j = 0;
        }
    }

    double result = pop(stack);
    free(stack->data);
    free(stack);
    return result;
}
