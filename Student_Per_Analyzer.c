#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Student  {
  int roll;
  char name[100];
  int sub1, sub2, sub3;
}Student;




char grading(float avg) {
  if(avg >= 85) return 'A';
  else if(avg >= 70)  return 'B';
  else if(avg >= 50)  return 'C';
  else if(avg >= 35) return 'D';
  else return 'F';
}

void printPattern(char grade) {
  printf("");
  if(grade == 'A')  printf("\nPerformance: *****");
  else if(grade == 'B') printf("\nPerformance: ****");
  else if(grade == 'C') printf("\nPerformance: ***");
  else if(grade == 'D') printf("\nPerformance: **");
}

int totalMarks(int sub1, int sub2, int sub3)  {
  return sub1 + sub2 + sub3;
}

float avgMarks(int total)  {
  return total / 3.0;
}



void sort(int arr[], int n) {
  for(int i = 0;i < n - 1;i++)  {
    for(int j = 0;j < n - i - 1;j++)  {
      if(arr[j] > arr[j + 1])  {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void rollNumbers(int rollNum[], int k, int i)  {
  if(k == i)  return;
  printf("%d ", rollNum[i]);
  rollNumbers(rollNum, k, i + 1);
  

  // for(int i = 0;i < k;i++)  {
  //   printf("%d ", rollNum[i]);
  // }
}

void giveOutput(Student stud[], int n, int rollNum[]) {
  for(int i = 0;i < n;i++)  {
    printf("\nRoll Number: %d", stud[i].roll);

    printf("\nName: %s", stud[i].name);

    int total = totalMarks(stud[i].sub1, stud[i].sub2, stud[i].sub3);
    printf("\nTotal: %d", total);

    float avg = avgMarks(total);
    printf("\nAverage: %f", avg);

    char grade = grading(avg);
    printf("\nGrade: %c", grade);

    printPattern(grade);

    printf("\n\n");
  }

  printf("\nList of Roll Numbers(via Recursion): ");
  sort(rollNum, n);
  rollNumbers(rollNum, n, 0);
}


int main()  {
  Student stud[100];
  int n;
  int rollNum[100];

  
  printf("\nEnter number of students: ");
  scanf("%d", &n);

  for(int i = 0;i < n;i++)  {
    printf("\nEnter student roll number: ");
    scanf("%d", &stud[i].roll);

    printf("\nEnter student name: ");
    scanf("%s", stud[i].name);

    printf("Enter marks for first subject: ");
    scanf("%d", &stud[i].sub1);

    printf("Enter marks for second subject: ");
    scanf("%d", &stud[i].sub2);

    printf("Enter marks for third subject: ");
    scanf("%d", &stud[i].sub3);

    rollNum[i] = stud[i].roll;
  }


  giveOutput(stud, n, rollNum);

  return 0;
}