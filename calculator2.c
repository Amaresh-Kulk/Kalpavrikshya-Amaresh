#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int precedence(char c)  {
  if(c == '+' || c == '-')  return 1;
  else if(c == '*' || c == '/') return 2;
  return -1;
}

int evaluation(int a, int b, char c)  {
  if(c == '+')  return a + b;
  else if(c == '-') return a - b;
  else if(c == '*') return a * b;
  else if(c == '/') {
    if(b == 0)  {
      printf("Error: Division by Zero");
      exit(0);
    }
    return a / b;
  }
}

int isDigit(char c)  {
  if(c == '0' || c == '1' || c == '2' || c == '3' || 
    c == '4' || c == '5' || c == '6' || c == '7' ||
    c == '8' || c == '9') return 1;
  return 0;
}

int evalExpresion(char exp[])  {
  int values[1000];
  int vTop = -1;
  char operators[1000];
  int oTop = -1;

  for(int i = 0;exp[i] != '\n';i++) {
    //ignore whitespaces
    if(exp[i] == ' ') continue;
    // store numbers in values[] stack
    else if(isDigit(exp[i]))  {
      int num = 0;  
      //take the single digits and merge them to form the number
      while(isDigit(exp[i]))  {
        int digit = exp[i] - '0';
        num = num * 10 + digit;
        i++;
      }
      values[++vTop] = num;
      i--;// we will not skip the non-digits like spaces
    }
    //check for the operators
    else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '/' || exp[i] == '*') {
      if(oTop != -1 && precedence(exp[i]) < precedence(operators[oTop]))  {
        int b = values[vTop--];// First take second value
        int a = values[vTop--];//then take first value
        char oper = operators[oTop--];
        int res = evaluation(a, b, oper);
        values[++vTop] = res; //store the result in top of values stack 
      }
      operators[++oTop] = exp[i];
    }

    else  {
      printf("Error: Invalid Expression!!");
      exit(0);
    }
  }
// Now I will evaluate the rest of the expression
  while(oTop != -1) {
    int b = values[vTop--];
    int a = values[vTop--];
    char oper = operators[oTop--];
    int res = evaluation(a, b, oper);
    values[++vTop] = res;
  }
  return values[vTop];
}

int main()  {
  char exp[1000];
  printf("\nEnter the expression: ");
  //below statement is taken from https://stackoverflow.com/questions/6282198/reading-string-from-input-with-space-character
  fgets (exp, 1000, stdin);

  printf("The result : %d", evalExpresion(exp));
  return 0;
}