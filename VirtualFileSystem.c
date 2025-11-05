#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define BLOCK_SIZE 512
#define NUM_BLOCKS 5000
#define NAME_SIZE 50

char virtualDisk[NUM_BLOCKS][BLOCK_SIZE];


typedef struct freeBlock  {
  int index;
  struct freeBlock *prev;
  struct freeBlock *next;
}freeBlock;

freeBlock *freeListHead = NULL;

void insertFreeBlockBeginning() {

  for(int i = 0;i < NUM_BLOCKS;i++) {
    freeBlock * temp = (freeBlock *)malloc(sizeof(freeBlock));
    temp->index = i;
    temp->next = NULL;
    temp->prev = NULL;

    if(freeListHead == NULL)  {
      freeListHead = temp;
      freeListHead->next = freeListHead;
      freeListHead->prev = freeListHead;
    }
    else  {
      freeListHead->prev->next = temp;
      temp->next = freeListHead;
      temp->prev = freeListHead->prev;
      freeListHead->prev = temp;
    } 
    freeListHead = temp;
  }
}

typedef struct fileNode  {
  char name[NAME_SIZE];
  int isDirectory;

  struct fileNode *prev;
  struct fileNode *next;
  
  struct fileNode *parent;
  
  //for directory  
  struct fileNode *child;

  //for file
  int size;
  int numBlocks;
  int *blockPointers;
}fileNode;

fileNode *root;
fileNode *currDir;
void addRootDirectory()  {
  root = (fileNode *)malloc(sizeof(fileNode));
  strcpy(root->name, "/");
  root->isDirectory = 1;
  root->parent = NULL;
  root->child = NULL;

  root->next = root;
  root->prev = root;

  currDir = root;
}

char * cwd()  {
  return currDir->name;
}


fileNode * findChild(char name[50])  {
  fileNode * temp = currDir->child;
  if(temp == NULL)  {
    return NULL;
  }
  do  {
    
    if(strcmp(temp->name, name) == 0) {
      // printf("\nhello\n");
      return temp;
    } 
    temp = temp->next;
  }while(temp != currDir->child);
  return NULL;
}

void mkdir(char name[])  {
  if(findChild(name) != NULL)  {
    printf("\nThe directory with name %s exists already!", name);
    return;
  }

  fileNode * temp = (fileNode *)malloc(sizeof(fileNode));
  strcpy(temp->name, name);
  temp->isDirectory = 1;
  
  temp->parent = currDir;
  temp->child = NULL;
  
  
  temp->next = temp;
  temp->prev = temp;

  if(currDir->child == NULL)  {
    currDir->child = temp;
  } else  {
    fileNode *head = currDir->child;
    fileNode *tail = head->prev;

    head->prev = temp;
    temp->next = head;
    temp->prev = tail;
    tail->next = temp;
  }
  printf("Directory '%s' created successfully.\n", name);
}

void create(char name[])  {
  if(findChild(name) != NULL) {
    printf("\nThe name %s already exists!", name);
    return;
  }

  fileNode * temp = (fileNode *)malloc(sizeof(fileNode));
  strcpy(temp->name, name);
  temp->size = 0;
  temp->numBlocks = 0;
  temp->isDirectory = 0;
  temp->blockPointers = NULL;

  temp->parent = currDir;
  temp->child = NULL;

  temp->next = temp;
  temp->prev = temp;

  if(currDir->child == NULL)  {
    currDir->child = temp;
  } else  {
    fileNode * head = currDir->child;
    fileNode *tail = head->prev;

    temp->next = head;
    temp->prev = tail;
    tail->next = temp;
    head->prev = temp;
  }
  printf("File '%s' created successfully.\n", name);

}

int findLength(char * name) {
  int i = 0;
  while(name[i] != '\0')  i++;
  return i;
}

int getIndex()  {
  if(freeListHead == NULL)  {
    printf("\nError: there is no enough space!");
    return -1;
  }

  int index = freeListHead->index;

  if(freeListHead->next == freeListHead)  {
    free(freeListHead);
    freeListHead = NULL;
    return index;
  }

  freeBlock *temp = freeListHead; 
  freeBlock *head = freeListHead->next;
  freeBlock *tail = freeListHead->prev;

  head->prev = tail;
  tail->next = head;
  freeListHead = head;

  free(temp);
  return index;
}

void write(char name[50], char *text) {
  fileNode *temp = findChild(name);
  if(temp == NULL)  {
    printf("\nFile name %s not found", name);
    return;
  }

  if (temp->isDirectory) {
    printf("Error: '%s' is a directory, not a file.\n", name);
    return;
  }

  int len = findLength(text);
  
  int i = 0;
  
  while(i < len)  {
    
    int index = getIndex();
    if(index == -1) {
      return;
    }

    int k = 0;
    char word[BLOCK_SIZE];

    while(i < len && k < BLOCK_SIZE)  {
      virtualDisk[index][k++] = text[i++];
    }

    temp->size += k;
    temp->numBlocks += 1;
    temp->blockPointers = (int *)realloc(temp->blockPointers, temp->numBlocks * sizeof(int));
    temp->blockPointers[temp->numBlocks - 1] = index;
  }
  printf("Data written successfully (size=%d, blocks=%d)\n", temp->size, temp->numBlocks);
}

void read(char name[])  {
  fileNode *temp = findChild(name);
  if(temp == NULL)  {
    printf("\nCouldn't found file with %s name", name);
    return;
  }

  printf("\nData in %s file: \n ", name);
  int remaining = temp->size;
  for(int i = 0;i < temp->numBlocks;i++)  {
    int index = temp->blockPointers[i];
    int toPrint = (remaining > BLOCK_SIZE) ? BLOCK_SIZE : remaining;

    for(int j = 0;j < toPrint;j++)  {
      putchar(virtualDisk[index][j]);
    }
    remaining -= toPrint;
  }
  printf("\n");
}

void rmdir(char name[])  {
  if(strcmp(name, "/") == 0)  {
    printf("\nCan't delete root directory");
    return;
  } 
  fileNode *temp = findChild(name);
  if(temp == NULL)  {
    printf("\nDirectory %s not found", name);
    return;
  }

  if(temp->child == NULL) {
      if(temp->parent->child == temp) {
        if(temp->next == temp)  {
          temp->parent->child = NULL;
        } else  {
          temp->parent->child = temp->next;
        }
      }

      if(temp->next == temp) {
        free(temp);
        temp = NULL;
      } else  {
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        free(temp);
        temp = NULL;
      }
    } else  {
      printf("\nCan't delete directory if there are elements in it.");
      return;
    }
    printf("\nDirectory %s deleted successfully", name);
}

void restoreFreeBlocks(int index)  {
  if(freeListHead == NULL)  {
    freeBlock *head = (freeBlock *)malloc(sizeof(freeBlock));
    head->index = index;
    head->next = head;
    head->prev = head;
    freeListHead = head;
    return;
  }


  freeBlock * head = freeListHead;
  freeBlock *tail = freeListHead->prev;

  freeBlock *temp = (freeBlock *)malloc(sizeof(freeBlock));
  temp->index = index;

  head->prev = temp;
  tail->next = temp;
  temp->prev = tail;
  temp->next = head;
}

void deleteFile(fileNode *temp) {
  char name[50];
  strcpy(name, temp->name);
  if(temp == NULL)  return;


  if(temp->parent->child == temp) {
    if(temp->next == temp)  temp->parent->child = NULL;
    else  temp->parent->child = temp->next;
  }

  for(int i = 0;i < temp->numBlocks;i++)  {
    int index = temp->blockPointers[i];
    restoreFreeBlocks(index);
  }
  free(temp->blockPointers);

  if(temp->next == temp)  {
    free(temp);
    temp = NULL;
  } else  {
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    free(temp);
    temp = NULL;
  }
  
  printf("\nFile %s deleted successfully!", name);
}

void delete(char name[])  {
  if(strcmp(name, "/") == 0)  {
    printf("\nCan't delete root directory");
    return;
  } 
  fileNode *temp = findChild(name);
  if(temp == NULL)  return;

  if(!temp->isDirectory) {  
    deleteFile(temp);
  }
}

void ls() {
  fileNode *temp = currDir->child;
  printf("\n");
  if(temp == NULL)  {
    printf("(empty directory)");
    return;
  }
  do
  {
    printf("%s ", temp->name);
    temp = temp->next;
  } while (temp != currDir->child);
}

void cd(char name[50]) {
  if(strcmp(name, "..") == 0) {
    if(currDir->parent == NULL) {
      printf("\nCan't exit from root");
      return;
    }
    currDir = currDir->parent;
    printf("\nMoved to %s directory", currDir->name);
    return;
  }

  if (currDir->child == NULL) {
    printf("\nNo subdirectories in the current directory");
    return;
  }

  fileNode * temp = currDir->child;
  do
  {
    if(strcmp(temp->name, name) == 0) {
      currDir = temp;
      printf("\nMoved to %s directory", name);
      return;
    }
    temp = temp->next;
  } while (temp != currDir->child);
  printf("\nCannot find the directory");
}

void pwd(fileNode *temp) {
  if(strcmp(temp->name, "/") == 0) {
    return;
  } 
  pwd(temp->parent);
  printf("/%s", temp->name);
}

void df() {
  int count = 0;
  int usedBlocks = 0;
  float diskUsage = 0.0;

  if(freeListHead != NULL)  {
    freeBlock *temp = freeListHead;
    do
    {
      count++;
      temp = temp->next;
    } while (temp != freeListHead);

    usedBlocks = NUM_BLOCKS - count;
    diskUsage = ((float)usedBlocks / NUM_BLOCKS) * 100.0;
  } else  {
    usedBlocks = NUM_BLOCKS;
    count = 0;
    diskUsage = 100.0;
  }

  printf(" \nTotal Blocks: %d", NUM_BLOCKS);
  printf("\nUsed Blocks: %d", usedBlocks);
  printf("\nFree Blocks: %d", count);
  printf("\nDisk Usage: %.2f%%", diskUsage);
}


void freeVirtualMemory()  {
  freeBlock * head = freeListHead;
  
  if(freeListHead == NULL)  return;
  
  head->prev->next = NULL;
  
  while(head != NULL) {
    freeBlock *temp = head;
    head = head->next;
    free(temp);
    temp = NULL;
  }
  
  freeListHead = NULL;
}

void freeFileNode(fileNode *temp) {
  if(temp == NULL) return;

  if(temp->child != NULL)  {

    fileNode *head = temp->child;
    fileNode *curr = head;

    head->prev->next = NULL;

    while(curr != NULL) {
      fileNode *next = curr->next;
      freeFileNode(curr);
      curr = next;
    }
    temp->child = NULL;

  }
  

  free(temp);
}

void Exit() {
  freeFileNode(root);
  root = NULL;

  freeVirtualMemory();
  freeListHead = NULL;

  printf("\nExiting and freed memory!");
  exit(0);
}

void parseString(char *str, char parse[3][1000]) {
  int i = 0, j = 0;

  
  for (int x = 0; x < 3; x++)
      parse[x][0] = '\0';

  while (str[i] != '\0' && str[i] != '\n' && j < 3) {
      while (str[i] == ' ') i++;  
      if (str[i] == '\0' || str[i] == '\n') break;

      int k = 0;
      if (str[i] == '"') {
          i++; 
          while (str[i] != '"' && str[i] != '\0' && str[i] != '\n' && k < 999) {
              parse[j][k++] = str[i++];
          }
          if (str[i] == '"') i++; 
      } else {
          while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n' && k < 999) {
              parse[j][k++] = str[i++];
          }
      }
      parse[j][k] = '\0';
      j++;
  }
}

int main()  {
  insertFreeBlockBeginning();
  addRootDirectory();
  while(1)  {
    printf("\n%s > ", cwd());
    char str[10000];
    fgets(str, sizeof(str), stdin);

    char parse[3][1000];
    parseString(str, parse);

    if(strcmp(parse[0], "mkdir") == 0)  mkdir(parse[1]);
    else if(strcmp(parse[0], "create") == 0)  create(parse[1]);
    else if(strcmp(parse[0], "write") == 0) write(parse[1], parse[2]);
    else if(strcmp(parse[0], "read") == 0)  read(parse[1]);
    else if(strcmp(parse[0], "delete") == 0)  delete(parse[1]);
    else if(strcmp(parse[0], "rmdir") == 0) rmdir(parse[1]);
    else if(strcmp(parse[0], "ls") == 0)  ls();
    else if(strcmp(parse[0], "cd") == 0)  cd(parse[1]);
    else if(strcmp(parse[0], "pwd") == 0) pwd(currDir);
    else if(strcmp(parse[0], "df") == 0)  df();
    else if(strcmp(parse[0], "exit") == 0)  Exit();
  }
  
  return 0;
}