#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>

#define MAX_SIZE 1000
#define MAX_PRIME 997
#define MAX_HASH_SIZE 1000

typedef struct Node {
  int key;
  char data[MAX_SIZE];

  struct Node *front;
  struct Node *rear;
}Node;

typedef struct hashNode {
  int key;
  
  Node *value;

  struct hashNode *next;
}hashNode;

hashNode *map[MAX_HASH_SIZE];


int hash = MAX_PRIME;

void initializeHash() {
  for(int i = 0;i < MAX_HASH_SIZE;i++)  {
    map[i] = NULL;
  }
}


int hashCode(int key) {
  if(key < 0) key = -key;
  return key % hash;
}

void putInMap(int key, Node *node) {
    int h = hashCode(key);
    hashNode *curr = map[h];

    while (curr != NULL) {
        if (curr->key == key) {
            curr->value = node;
            return;
        }
        curr = curr->next;
    }

    hashNode *temp = malloc(sizeof(hashNode));
    temp->key = key;
    temp->value = node;
    temp->next = map[h];
    map[h] = temp;
}


Node *getFromMap(int key) {
  int hashValue = hashCode(key);
  hashNode *node = map[hashValue];
  
  while(node != NULL) {
    if(node->key == key)  return node->value;
    node = node->next;
  } 
  

  return NULL; 
}

void removeFromMap(int key) {
  int hashValue = hashCode(key);

  hashNode * curr = map[hashValue], *prev = NULL;

  while(curr != NULL) {
    if(curr->key == key)  {
      if(prev == NULL)  map[hashValue] = curr->next;
      else  prev->next = curr->next;

      free(curr);
      curr = NULL;
      return;
    }
    prev = curr;
    curr = curr->next;
  }

}



Node *head = NULL;
Node *tail = NULL;
int capacity, count;

void createCache(int cap)  {
  capacity = cap;
  count = 0;

  initializeHash();

  head = (Node *)malloc(sizeof(Node));
  head->key = -1;
  //strcpy(head->data, "");

  tail = (Node *)malloc(sizeof(Node));
  tail->key = -1;
  //strcpy(tail->data, "");

  head->rear = NULL;
  head->front = tail;
  tail->rear = head;
  tail->front = NULL;
}

void insertAtHead(Node *node)  {
  Node *currHead = head->front;
  head->front = node;
  node->rear = head;
  currHead->rear = node;
  node->front = currHead;
}

void deleteNode(Node *node) {
  removeFromMap(node->key);

  node->rear->front = node->front;
  node->front->rear = node->rear;
  free(node);
  node = NULL;
  
}


char *get(int key) {
  Node *node = getFromMap(key);

  if(node == NULL)  return NULL;



  node->front->rear = node->rear;
  node->rear->front = node->front;


  insertAtHead(node);

  return node->data;
  
}

void put(int key, char value[]) {

  Node *node = getFromMap(key);

    if(node != NULL)  {
      
      node->front->rear = node->rear;
      node->rear->front = node->front;

      strcpy(node->data, value);
      insertAtHead(node);
      return;
    }


    if(count == capacity) {
      deleteNode(tail->rear);
    } else  {
      count++;
    }


    node = (Node *)malloc(sizeof(Node));
    node->key = key;
    strcpy(node->data, value);
    insertAtHead(node);
    putInMap(key, node); 
    
}

void exitProgram()  {
  Node * curr = head->front, *prev = NULL;
  while(curr != NULL) {
    prev = curr;
    curr = curr->front;
    deleteNode(prev);
  }

  free(head);
  head = NULL;
  free(tail);
  tail = NULL;

  exit(0);
}

void parseInput(char *input, char parse[3][MAX_SIZE]) {
  int k = 0, i = 0;
  while(input[i] != '\0' && k < 3) {
    
    while (input[i] == ' ') i++;

    int j = 0;
    while(input[i] != ' ' && input[i] != '\n' && input[i] != '\0')  {
      parse[k][j++] = input[i++];
    }
    parse[k][j] = '\0';
    k++;
  }
}

int main()  {

  char input[3 * MAX_SIZE];
  char parse[3][MAX_SIZE];

  while(1)  {
    //getchar();
    fgets(input, sizeof(input), stdin);

    int len = strlen(input);
    if(len > 0 && input[len - 1] == '\n') input[len - 1] = '\0';

    parseInput(input, parse);

    if(strcmp(parse[0], "createCache") == 0)  {
      createCache(atoi(parse[1]));
    } else if(strcmp(parse[0], "put") == 0) {
      put(atoi(parse[1]), parse[2]);
    } else if(strcmp(parse[0], "get") == 0) {
      printf("\n%s\n", get(atoi(parse[1])));
    } else if(strcmp(parse[0], "exit") == 0)  exitProgram();
  }


  return 0;
}