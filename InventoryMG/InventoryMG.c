#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Product  {
  int productID;
  char prodName[50];
  float price;
  int quantity;
}Product;

int validateProductID(int id) {
  if(id < 1 || id > 10000)  {
    printf("\nEnter valid ID");
    return 0;
  }
  return 1;
}

int validateProductName(char name[])  {
  if(!isupper(name[0])) {
    printf("\nFirst character should be capital");
    return 0;
  }
  for(int i = 1;name[i] != '\0';i++)  {
    if(isupper(name[i]))  {
      printf("\n Only first character should be capital.");
      return 0;
    }
  }

  for(int i = 0;name[i] != '\0';i++)  {
    if(!isalpha(name[i])) {
      printf("\nName should not have non-characters");
      return 0;
    }
  }
  return 1;
}

int validProductPrice(int price)  {
  if(price < 0 || price > 100000)  {
    printf("\nEnter valid price");
    return 0;
  }
  return 1;
}

int validProductQuantity(int quantity)  {
  if(quantity < 0 || quantity > 1000000)  {
    printf("\nEnter valid quantity");
    return 0;
  }
  return 1;
}

void addProduct(int *n, Product ** prod)  {
  
  *n = *n + 1;
  *prod = (Product *)realloc(*prod, (*n) * sizeof(Product));

  printf("\nEnter details of new Product: ");
  printf("\nEnter Details of Product %d: ", *n);

  do  {
    printf("\nProduct ID: ");
    scanf("%d", &((*prod + (*n - 1))->productID));
  }while(!validateProductID((*prod + (*n - 1))->productID));
  
  do
  {
    printf("\nProduct Name: ");
    scanf("%s", ((*prod + (*n - 1))->prodName));
  } while (!validateProductName((*prod + (*n - 1))->prodName));
  
  
  do
  {
    printf("\nProduct Price: ");
    scanf("%f", &((*prod + (*n - 1))->price));
  } while (!validProductPrice((*prod + (*n - 1))->price));
  
  do
  {
    printf("\nProduct Quantity: ");
    scanf("%d", &((*prod + (*n - 1))->quantity));
  } while (!validProductQuantity((*prod + (*n - 1))->quantity));
  
}

void viewProducts(int n, Product * prod)  {
  if(n == 0)  {
    printf("\nThere arn't any products available.");
    return;
  }

  for(int i = 0;i < n;i++)  {
    printf("\nDetails of Product %d: ", i + 1);
    printf("\nProduct ID: ");
    printf("%d", ((prod + i)->productID));

    printf("\nProduct Name: ");
    printf("%s", ((prod + i)->prodName));

    printf("\nProduct Price: ");
    printf("%f", ((prod + i)->price));

    printf("\nProduct Quantity: ");
    printf("%d", ((prod + i)->quantity));
    printf("\n*******************\n");
  }
}

void updateQuantity(int n, Product * prod)  {
  int id;
  
  do
  {
    printf("\nEnter Product ID to update quantity: ");
    scanf("%d", &id);
  } while (!validateProductID(id));
  

  int i = 0, flag = 0;
  while(i < n)  {
    if(id == (prod + i)->productID) {
      flag = 1;
      break;
    }
    i++;
  }

  if(flag)  {
    do  {
      printf("\nEnter new Quantity: ");
      scanf("%d", &(prod + i)->quantity);
    }while(!validProductQuantity((prod + i)->quantity));
    printf("\nQuantity updated successfully! ");
  } else  {
    printf("\nItem not found");
  }
}


void printDetails(int id, char name[], float price, int quantity) {
  printf("\nProduct ID: %d", id);
  printf("\nProduct Name: %s", name);
  printf("\nProduct Price: %f", price);
  printf("\nProduct Quantity: %d", quantity);
}

void searchByID(int n, Product * prod)  {
  int id, flag = 0;
  
  do
  {
    printf("\nEnter Product ID to be searched: ");
    scanf("%d", &id);
  } while (!validateProductID(id));
  
  int i;
  for(i = 0;i < n;i++)  {
    if(id == (prod + i)->productID) {
      flag = 1;
      break;
    }
  }
  if(flag)  {
    printf("\nProduct with ID %d is found.", id);
    printDetails((prod + i)->productID, (prod + i)->prodName, (prod + i)->price, (prod + i)->quantity);
  } else  {
    printf("\nCouldn't found the product.");
  }
}


int findLength(char txt[]) {
    int i = 0;
    while (txt[i] != '\0')
        i++;
    return i;
}

void calculateLPS(int lps[], char pat[], int m) {
  int i = 1, len = 0;
  lps[0] = 0;
  while(i < m)  {
    if(pat[i] == pat[len])  {
      len++;
      lps[i] = len;
      i++;
    } else  {
      if(len != 0)  {
        len = lps[len - 1];
      } else  {
        lps[i] = 0;
        i++;
      }
    }
  }
}

int kmp(char pat[], char txt[])  {
  int m = findLength(pat);
  int n = findLength(txt);

  int *lps = (int *)calloc(m, sizeof(int));

  calculateLPS(lps, pat, m);

  int i = 0, j = 0;
  while(i < n)  {
    if(pat[j] == txt[i])  {
      i++;
      j++;
    } 

    if(j == m)  {
      free(lps);
      return 1;
    }

    if(i < n && pat[j] != txt[i]) {
      if(j != 0)  {
        j = lps[j - 1];
      } else  {
        i++;
      }
    }
  }
  free(lps);
  return 0;
}


void searchByName(int n, Product * prod)  {
  char name[50];
  int flag = 0;

  do
  {
    printf("\nEnter product name to be searched: ");
    scanf("%s", name);
  } while (!validateProductName(name));
  
  int i;
  for(i = 0;i < n;i++)  {
    if(kmp(name, (prod + i)->prodName)) {
      flag = 1;
      break;
    } 
  }

  if(flag)  {
    printf("\nProduct with name %s is found.", name);
    printDetails((prod + i)->productID, (prod + i)->prodName, (prod + i)->price, (prod + i)->quantity);
  } else  printf("\nProduct is not found");

}

void searchByPriceRange(int n, Product * prod)  {
  int low_price, up_price;
  printf("\nEnter lower range of Price: ");
  scanf("%d", &low_price);

  printf("\nEnter upper price of Price: ");
  scanf("%d", &up_price);
  int flag = 0;
  int i;
  for(i = 0;i < n;i++)  {
    if(low_price <= (prod + i)->price && up_price >= (prod + i)->price) {
      flag = 1;
      break;
    }
  }

  if(flag)  {
    printf("\nThe product is found");
    printDetails((prod + i)->productID, (prod + i)->prodName, (prod + i)->price, (prod + i)->quantity);
  } else  printf("\nCouldn't found product");
}

void delateProduct(int *n, Product *prod) {

  if(*n == 0) {
    printf("\nThere aren't any products available");
    return;
  }

  int id, flag = 0;

  printf("\nEnter id of the product to be deleted: ");
  scanf("%d", &id);
  int i;
  for(i = 0;i < *n;i++) {
    if(id == (prod + i)->productID)  {
      flag = 1;
      break;
    }
  }

  if(!flag) {
    printf("\nCouldn't found the product.");
    return;
  }

  for(;i < *n - 1;i++) {
    (prod + i)->price = (prod + i + 1)->price;
    strcpy((prod + i)->prodName, (prod + i + 1)->prodName);
    (prod + i)->productID = (prod + i + 1)->productID;
    (prod + i)->quantity = (prod + i + 1)->quantity;
  }

  *n = *n - 1;
  prod = (Product *)realloc(prod, (*n) * sizeof(Product));

  printf("\nSuccessfully Deleted the product");
}


int main()  {

  int n;
  printf("\nEnter initial number of products: ");
  scanf("%d", &n);

  Product * prod = (Product *)calloc(n, sizeof(Product));

  for(int i = 0;i < n;i++)  {
    printf("\nEnter Details of Product %d: ", i + 1);
    do
    {
      printf("\nProduct ID: ");
      scanf("%d", &((prod + i)->productID));
    } while (!validateProductID((prod + i)->productID));
    

    do
    {
      printf("\nProduct Name: ");
      scanf("%s", ((prod + i)->prodName));
    } while (!validateProductName((prod + i)->prodName));
    
    do
    {
      printf("\nProduct Price: ");
      scanf("%f", &((prod + i)->price));
    } while (!validProductPrice((prod + i)->price));
    
    do
    {
      printf("\nProduct Quantity: ");
      scanf("%d", &((prod + i)->quantity));
    } while (!validProductQuantity((prod + i)->quantity));
    
  }


  while(1)  {
    printf("\n========= INVENTORY MENU ========="
       "\n1. Add New Product"
       "\n2. View All Products"
       "\n3. Update Quantity"
       "\n4. Search Product by ID"
       "\n5. Search Product by Name"
       "\n6. Search Product by Price Range"
       "\n7. Delete Product"
       "\n8. Exit\n");


    
    int choice;
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch(choice)  {
      case 1: addProduct(&n, &prod);
          break;
      case 2:  viewProducts(n, prod);
          break;
      case 3:  updateQuantity(n, prod);
          break;
      case 4:  searchByID(n, prod);
          break;
      case 5:  searchByName(n, prod);
          break;
      case 6:  searchByPriceRange(n, prod);
          break;
      case 7: delateProduct(&n, prod);
          break;
      case 8:  exit(0);
      default: printf("\nPlease enter valid choice");
    }

  }
  free(prod);
  return 0;
}