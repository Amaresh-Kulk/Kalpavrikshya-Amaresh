#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>


int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}


int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
          if(b == 0)  {
            printf("Error: Division by Zero");
            exit(0);
          }
          return a / b;  
    }
    return 0;
}

int evalExp(char* exp) {
    int valStack[100];   
    char opsStack[100];     
    int vTop = -1, oTop = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        
        if(exp[i] == ' ') continue;
        
        
        else if (isdigit(exp[i])) {
            int val = 0;
            while (isdigit(exp[i])) {
                val = val * 10 + (exp[i] - '0');
                i++;
            }
            valStack[++vTop] = val;
            i--; 
        }
        else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '/' || exp[i] == '*'){
            // Operator
            while (oTop != -1 && precedence(opsStack[oTop]) >= precedence(exp[i])) {
                int b = valStack[vTop--];
                int a = valStack[vTop--];
                char op = opsStack[oTop--];
                valStack[++vTop] = applyOperation(a, b, op);
            }
            opsStack[++oTop] = exp[i];
        }
        else  {
          if(exp[i] == '\n')  break;
          
          printf("Error: Invalid Expression");
          exit(0);
        }
    }

    
    while (oTop != -1) {
        int b = valStack[vTop--];
        int a = valStack[vTop--];
        char op = opsStack[oTop--];
        valStack[++vTop] = applyOperation(a, b, op);
    }

    return valStack[vTop];
}

int main() {
    char exp[100];
    printf("Enter expression (no spaces): ");
    fgets(exp, sizeof(exp), stdin);

    int res = evalExp(exp);
    printf("The result is : %d\n", res);
    return 0;
}
