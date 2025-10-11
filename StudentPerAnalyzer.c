#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Student  {
  int roll;
  char name[100];
  int sub1, sub2, sub3;
}Student;


int validRollNum(int roll, int rollNum[], int n) {
  if(roll < 1) {
    printf("\nEnter any positive value");
    return 0;
  }

  for(int i = 0;i < n;i++)  {
    if(rollNum[i] == roll)  {
      printf("\nRoll number already exists");
      return 0;
    }
  }

  return 1;
}

int validName(char name[])  {
  for(int i = 0;name[i] != '\n';i++)  {
    if(!isalpha(name[i])) {
      printf("\nThere should be only letters in name");
      printf("\nPress Enter:");
      return 0;
    }
  }

  if(!isupper(name[0])) {
    printf("\nFirst letter should be capital");
    printf("\nPress Enter:");
    return 0;
  }
  for(int i = 1;name[i] != '\n';i++)  {
    if(isupper(name[i]))  {
      printf("\nOnly first letter should be capital");
      printf("\nPress Enter:");
      return 0;
    }
  }

  return 1;
}

int validMarks(int marks) {
  if(marks < 0 || marks >100) {
    printf("\nEnter number between 0 - 100");
    return 0;
  }
  return 1;
}



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

void takeInput(Student stud[], int n, int rollNum[]) {
  for(int i = 0;i < n;i++)  {

    do
    {
      printf("\nEnter student roll number: ");
    scanf("%d", &stud[i].roll);
    }while (!validRollNum(stud[i].roll, rollNum, n));
    
    
    do
    {
      getchar();
      printf("\nEnter student name: ");
      // scanf("%s", );
      fgets (stud[i].name, 1000, stdin);
    } while (!validName(stud[i].name));
    
    
    do
    {
      printf("\nEnter marks for first subject: ");
      scanf("%d", &stud[i].sub1);
    } while (!validMarks(stud[i].sub1));
    
    
    do
    {
      printf("\nEnter marks for second subject: ");
      scanf("%d", &stud[i].sub2);
    } while (!validMarks(stud[i].sub2));
    
    

    do
    {
      printf("\nEnter marks for third subject: ");
      scanf("%d", &stud[i].sub3);
    } while (!validMarks(stud[i].sub3));
    
    
    rollNum[i] = stud[i].roll;
  }

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

  takeInput(stud, n, rollNum);

  giveOutput(stud, n, rollNum);

  return 0;
}