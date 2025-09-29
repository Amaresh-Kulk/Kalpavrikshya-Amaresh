#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct User {
  int id;
  char fname[30], mname[30], lname[30];
  int age;
}User;


void createUser()  {
  User user;
  FILE *fp = fopen("users.txt", "a+");
  if(!fp) {
    printf("Error opening file!");
    return;
  }

  printf("Enter User ID: ");
  scanf("%d", &user.id);

  User temp;
  while(fscanf(fp, "%d %s %s %s %d", &temp.id, temp.fname, temp.mname, temp.lname, &temp.age) != EOF)  {
    if(temp.id == user.id)  {
      printf("Error: Student with this ID already exists!\n");
      fclose(fp);
      return;
    }
  }

  
  printf("Enter First name: ");
  scanf("%s", user.fname);

  printf("Enter Middle Name: ");
  scanf("%s", user.mname);

  printf("Enter Last Name: ");
  scanf("%s", user.lname);




  while(1)  {
    printf("Enter user age: ");
    scanf("%d", &user.age);
    if(user.age > 122 || user.age < 0)  {
      printf("Please enter a valid age!\n");
      continue;
    }
    break;
  }

  fprintf(fp, "%d %s %s %s %d\n", user.id, user.fname, user.mname, user.lname, user.age);

  fclose(fp);

  printf("User added successfully!!\n");
  
}

void readUsers()  {
  User user;
  FILE *fp = fopen("users.txt", "r");
  if(!fp) {
    printf("Error: File doesn't have data.");
    return;
  }

  printf("******  Users list  ******\n");
  while(fscanf(fp, "%d %s %s %s %d", &user.id, user.fname, user.mname, user.lname, &user.age) != EOF) {
    printf("ID: %d, Full Name: %s %s %s, Age: %d\n", user.id, user.fname, user.mname, user.lname, user.age);
  }
  fclose(fp);
}

void updateUser() {
  int id, found = 0;
  User user;
  FILE *fp = fopen("users.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if(!fp || !temp)  {
    printf("Error opening one of the files!");
    return;
  }

  printf("\nEnter the User ID:");
  scanf("%d", &id);

  while(fscanf(fp, "%d %s %s %s %d", &user.id, user.fname, user.mname, user.lname, &user.age) != EOF)  {
    if(user.id == id) {
      printf("Enter new First name: ");
      scanf("%s", user.fname);

      printf("Enter new Middle Name: ");
      scanf("%s", user.mname);

      printf("Enter new Last Name: ");
      scanf("%s", user.lname);

      while(1)  {
        printf("Enter user age: ");
        scanf("%d", &user.age);
        if(user.age > 122 || user.age < 0)  {
          printf("Please enter a valid age!\n");
          continue;
        }
        break;
      }
      


      found = 1;
    }

    fprintf(temp, "%d %s %s %s %d\n", user.id, user.fname, user.mname, user.lname, user.age);
  }

  fclose(fp);
  fclose(temp);

  if (remove("users.txt") != 0) {
      perror("Error deleting users.txt");
  }
  if (rename("temp.txt", "users.txt") != 0) {
      perror("Error renaming file");
  }

  if(found) {
    printf("User details updated successfully!!\n");
  }
  else  printf("User not found!\n");
}

void deleteUser()  {
  int id, found = 0;
  User user;

  FILE *fp = fopen("users.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if(!fp || !temp)  {
    printf("Error opening one of the file!\n");
    return;
  }

  printf("Enter the user id: ");
  scanf("%d", &id);

  while(fscanf(fp, "%d %s %s %s %d", &user.id, user.fname, user.mname, user.lname, &user.age) != EOF)  {
    if(user.id == id) {
      found = 1;
      continue; //neglecting this data
    }
    fprintf(temp, "%d %s %s %s %d\n", user.id, user.fname, user.mname, user.lname, user.age);
  }
  fclose(fp);
  fclose(temp);

  if (remove("users.txt") != 0) {
      perror("Error deleting users.txt");
  }
  if (rename("temp.txt", "users.txt") != 0) {
      perror("Error renaming file");
  }

  if(found) printf("User removed successfully!!\n");
  else  printf("User not found!!\n");
}

int main()  {
  int op;
  while(1)  {
    printf("\n\n******* User Operations *******\n\n");
    printf("1.          Create User\n");
    printf("2.          Read Users\n");
    printf("3.          Update User\n");
    printf("4.          Delete User\n");
    printf("5.          Exit\n");
    printf("Enter operation to perform: ");
    scanf("%d", &op);

    switch(op)  {
      case 1: createUser(); break;
      case 2: readUsers(); break;
      case 3: updateUser(); break;
      case 4: deleteUser(); break;
      case 5: 
              //printf("Exiting....");
              exit(0);
      default: printf("Invalid choice\n");
    }
  }

  return 0;
}