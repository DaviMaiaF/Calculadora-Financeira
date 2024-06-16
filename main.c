#include "calculadora.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main()
{
    char expression[256];

    while (1)
    {
        printf("Digite uma expressao em notacao pos-fixada (ou 'sair' para finalizar): ");
        fgets(expression, 256, stdin);
        if (strncmp(expression, "sair", 4) == 0)
        {
            break;
        }
        expression[strcspn(expression, "\n")] = 0; // Remove o newline

        double result = evaluatePostfix(expression);
        printf("Resultado obtido: %.2f\n", result);
        printf("--------\n");
    }

    return 0;
}
