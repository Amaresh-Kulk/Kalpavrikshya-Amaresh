#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef struct User
{
  char fname[100], mname[100], lname[100];
  int id, age;
}User;


int checkID(int id)  {
  FILE *fp = fopen("users.txt", "r");
  if(!fp) {
    printf("Unable to OPen File.");
    exit(0);
  }
  User user;
  while(fscanf(fp, "%d %s %s %s %d\n", &user.id, user.fname, user.mname, user.lname, &user.age) != EOF)  {
    if(user.id == id) {
      printf("\nPlease enter another id.");
      fclose(fp);
      return 1;
    }
  }
  fclose(fp);
  return 0;
}

int checkAge(int age) {
  if(age < 0 || age > 122)  return 1;
  return 0;
}

int validName(char name[])  {
  for(int i = 0;name[i] != '\n';i++) {
    if(!isalpha(name[i])) return 0;
  }

  //First Letter Should be Capital
  if(!isupper(name[0])) return 0;
  for(int i = 1;name[i] != '\n';i++)  {
    if(isupper(name[i]))  return 0;
  }
  return 1;
}

void createFile()  {
   FILE *fp = fopen("users.txt", "a+");
   User user;

   if(!fp)  {
    printf("\nUnable to Open File");
    exit(0);
   }
   
   // do continues loop until user enter unique id
   do {
    printf("\nEnter the id: ");
    scanf("%d", &user.id);
   }while(checkID(user.id)); 

   printf("\nEnter first name: ");
   scanf("%s", user.fname);

   printf("\nEnter middle name: ");
   scanf("%s", user.mname);

   printf("\nEnter last name: ");
   scanf("%s", user.lname);

   do
   {
    printf("\nEnter age: ");
    scanf("%d", &user.age);
   }while(checkAge(user.age));

   fprintf(fp, "%d %s %s %s %d\n", user.id, user.fname, user.mname, user.lname, user.age);

   fclose(fp);
}

void ReadFile() {
  FILE *fp = fopen("users.txt", "r");

  if(!fp) {
    printf("\nFile was not able to access");
    exit(0);
  }
  User user;
  printf("\nShowing all Users:\n");
  while(fscanf(fp, "%d %s %s %s %d\n", &user.id, user.fname, user.mname, user.lname, &user.age) != EOF){
    printf("%d %s %s %s %d\n", user.id, user.fname, user.mname, user.lname, user.age);
  }

  fclose(fp);
}

void updateFile() {
  FILE * fp = fopen("users.txt", "r");
  FILE * tmp = fopen("temp.txt", "w");

  User user;
  if(!fp || !tmp) {
    printf("\nUnable to open the files");
    exit(0);
  }
  int id;
  printf("\nEnter id of student to be updated: ");
  scanf("%d", &id);

  int flag = 0;

  while(fscanf(fp, "%d %s %s %s %d\n", &user.id, user.fname, user.mname, user.lname, &user.age) != EOF)  {
    if(user.id == id) {
      printf("\nUpdate first name: ");
      scanf("%s", user.fname);

      printf("\nUpdate middle name: ");
      scanf("%s", user.mname);

      printf("\nUpdate last name:");
      scanf("%s", user.lname);

      printf("\nUpdate Age: ");
      scanf("%d", &user.age);

      flag = 1;
    }

    fprintf(tmp, "%d %s %s %s %d\n", user.id, user.fname, user.mname, user.lname, user.age);
  }

  if(!flag) {
    printf("\nUser not found");
  }
  fclose(fp);
  fclose(tmp);

  remove("users.txt");
  rename("temp.txt", "users.txt");
}

void deleteFile() {
  FILE * fp = fopen("users.txt", "r");
  FILE * tmp = fopen("temp.txt", "w");

  if(!fp || !tmp) {
    printf("File was unable to open");
    exit(0);
  }

  User user;

  int id;
  printf("Enter ID of user to be deleted: ");
  scanf("%d", &id);

  int flag = 0;

  while(fscanf(fp, "%d %s %s %s %d\n", &user.id, user.fname, user.mname, user.lname, &user.age) != EOF)  {
    if(user.id == id) {
      flag = 1;
      continue;
    }
    fprintf(tmp, "%d %s %s %s %d\n", user.id, user.fname, user.mname, user.lname, user.age);
  }

  if(!flag){
    printf("\nUser was not found");
  }

  fclose(fp);
  fclose(tmp);

  remove("users.txt");
  rename("temp.txt", "users.txt");
}

int main()  {
  int choice;

  while(1)  {

    printf("\n 1 : Create User");
    printf("\n 2 : Read All Users");
    printf("\n3 : update user:");
    printf("\n4: Delete user");
    printf("\n5 : exxit");

    printf("\nEnter the choice: ");
    scanf("%d", &choice);

    switch(choice)  {
      case 1 : createFile();
              break;
      case 2 : ReadFile();
              break;
      case 3 : updateFile();
                break;
      case 4 : deleteFile();
              break;
      case 5 : exit(0);
      default : printf("\nEntered invalid choice");
    }
  }

  return 0;
  
}