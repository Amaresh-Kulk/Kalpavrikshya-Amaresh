#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int validInput(int a) {
  if(a < 0 || a > 255)  {
    printf("\nEnter value between 0 and 255:");
    return 0;
  }
  return 1;
}

int validNValue(int n)  {
  if(n < 2 || n > 10) {
    printf("\nEnter value between 2 and 10: ");
    return 0;
  }
  return 1;
}

void  takeInput(int n, int (*matrix)[n]) {
  printf("\nEnter the values of %d * %d matrix:\n", n, n);

  for(int i = 0;i < n;i++)  {
    for(int j = 0;j < n;j++)  {
      do
      {
        scanf("%d", (*(matrix + i) + j));
      } while (!validInput(*(*(matrix + i) + j)));
    }
  }
}

void printInput(int n, int (*matrix)[n]) {

  //printf("\n\nOriginal Matrix:\n");
  for(int i = 0;i < n;i++)  {
    for(int j = 0;j < n;j++)  {
      printf("%d ", *(*(matrix + i) + j));
    }
    printf("\n");
  }
}

void rotateMatrix(int n, int (*matrix)[n])  {

  //transpose
  for(int i = 0;i < n;i++)  {
    for(int j = i;j < n;j++) {
      int temp = *(*(matrix + i) + j);
      *(*(matrix + i) + j) = *(*(matrix + j) + i);
      *(*(matrix + j) + i) = temp; 
    }
  }
  //printf("\nTransposed:\n");
  //printInput(n, matrix);

  //row swap
  for(int i = 0;i < n;i++)  {
    int start = 0, end = n - 1;
    while(start < end)  {
      int temp = *(*(matrix + i) + start);
      *(*(matrix + i) + start) = *(*(matrix + i) + end);
      *(*(matrix + i) + end) = temp;
      start++;
      end--;
    }
  }
  printf("\nRotated:\n");
  printInput(n, matrix);
}

void filterMatrix(int n, int (*matrix)[n])  {

}

int main()  {

  int n;

  do
  {
    printf("\nEnter the N value:");
    scanf("%d", &n);
  } while (!validNValue(n));
  


  int matrix[n][n];

  takeInput(n, matrix);

  printf("\nOriginal:\n");
  printInput(n, matrix);
  
  rotateMatrix(n, matrix);
  //printInput(n, matrix);

  filterMatrix(n, matrix);
  printf("\nFiltered matrix:\n");
  printInput(n, matrix);
  return 0;
}