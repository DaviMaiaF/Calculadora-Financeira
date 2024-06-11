#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Defini��o da estrutura da pilha
typedef struct {
    double *data;
    int top;
    int capacity;
} Stack;

// Fun��es da pilha
Stack* createStack(int capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (double *) malloc(stack->capacity * sizeof(double));
    return stack;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, double item) {
    if (isFull(stack))
        return;
    stack->data[++stack->top] = item;
}

double pop(Stack *stack) {
    if (isEmpty(stack))
        return 0.0;
    return stack->data[stack->top--];
}

double peek(Stack *stack) {
    if (isEmpty(stack))
        return 0.0;
    return stack->data[stack->top];
}

// Fun��o para verificar se o caractere � um operador
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Fun��o para realizar as opera��es matem�ticas b�sicas
double performOperation(double a, double b, char operator) {
    switch (operator) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Fun��es especiais
double performSpecialOperation(const char *operation, double operand) {
    if (strcmp(operation, "raiz") == 0) return sqrt(operand);
    if (strcmp(operation, "sen") == 0) return sin(operand);
    if (strcmp(operation, "cos") == 0) return cos(operand);
    if (strcmp(operation, "tg") == 0) return tan(operand);
    if (strcmp(operation, "log") == 0) return log10(operand);
    return 0;
}

// Avalia��o da express�o p�s-fixada
double evaluatePostfix(const char *expression) {
    Stack *stack = createStack(strlen(expression));
    char token[20];
    int i = 0, j = 0;

    while (expression[i] != '\0') {
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (isdigit(expression[i]) || expression[i] == '.') {
            while (isdigit(expression[i]) || expression[i] == '.') {
                token[j++] = expression[i++];
            }
            token[j] = '\0';
            push(stack, atof(token));
            j = 0;
        } else if (isOperator(expression[i])) {
            double b = pop(stack);
            double a = pop(stack);
            double result = performOperation(a, b, expression[i]);
            push(stack, result);
            i++;
        } else if (isalpha(expression[i])) {
            while (isalpha(expression[i])) {
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

// Fun��o principal para leitura e avalia��o da express�o
int main() {
    char expression[256];

    while (1) {
        printf("Digite uma express�o em nota��o p�s-fixada (ou 'sair' para terminar): ");
        fgets(expression, 256, stdin);
        if (strncmp(expression, "sair", 4) == 0) {
            break;
        }
        expression[strcspn(expression, "\n")] = 0;  // Remove o newline

        printf("Digite o resultado esperado: ");
        double expected;
        scanf("%lf", &expected);
        getchar();  // Limpar o buffer de entrada

        double result = evaluatePostfix(expression);
        printf("Resultado esperado: %.8f\n", expected);
        printf("Resultado obtido: %.8f\n", result);
        printf("--------\n");
    }

    return 0;
}
	
