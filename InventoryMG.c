#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Product  {
  int ID;
  char name[50];
  float price;
  int quantity;
}Product;

void printDetails(int id, char name[], float price, int quantity);
int getValidateProductID(Product *prod, int n);
void getValidateProductName(char *name);
float getValidateProductPrice();
int getValidateProductQuantity();
int getValidInitialNumber();
void addProduct(int *n, Product **prod);
void viewProducts(int n, Product *prod);
void updateQuantity(int n, Product *prod);
void searchByID(int n, Product *prod);
void searchByName(int n, Product *prod);
void searchByPriceRange(int n, Product *prod);
void deleteProduct(Product *prod, int *n);
int findLength(char txt[]);
void calculateLPS(int lps[], char pat[], int m);
int kmp(char pat[], char txt[]);

int findProductIndexByID(Product *prod, int n, int id) {
    for (int i = 0; i < n; i++) {
        if ((prod + i)->ID == id) {
            return i;
        }
    }
    return -1;
}


int getValidateProductID(Product *prod, int n) {
    int id, valid;
    do {
        valid = 1;
        printf("\nEnter Product ID: ");
        scanf("%d", &id);

        if (id < 1 || id > 10000) {
            printf("Enter valid ID \n");
            valid = 0;
            continue;
        }

        for (int i = 0; i < n; i++) {
            if ((prod + i)->ID == id) {
                printf("This ID already exists.\n");
                valid = 0;
                break;
            }
        }
    } while (!valid);

    return id;
}

int isValidProductName(char *name) {
    int len = strlen(name);
    if (len == 0 || len > 50)
        return 0;

    
    if (!isupper(name[0]))
        return 0;

    for (int i = 0; i < len; i++) {
        char c = name[i];
        if (!(isalpha(c) || isdigit(c) || c == ' ' || c == '-' || c == '.' || c == '\'')) {
            return 0;
        }
    }

    return 1;
}

void getValidateProductName(char *name) {
    do {
        printf("\nEnter Product Name: ");
        scanf(" %[^\n]", name);  // Reads spaces too

        if (!isValidProductName(name)) {
            printf("Invalid Product Name.\n");
            printf("Rules:\n");
            printf("1. Must start with a capital letter.\n");
            printf("2. Can include letters, numbers, spaces, hyphens (-), apostrophes ('), and dots (.).\n");
            printf("3. Length must be between 1 and 50 characters.\n");
        }

    } while (!isValidProductName(name));
}


float getValidateProductPrice() {
    float price;
    do {
        printf("\nEnter Product Price: ");
        scanf("%f", &price);
        if (price < 0 || price > 100000)
            printf("Enter valid price \n");
        else
            return price;
    } while (1);
}

int getValidateProductQuantity() {
    int quantity;
    do {
        printf("\nEnter Product Quantity: ");
        scanf("%d", &quantity);
        if (quantity < 0 || quantity > 1000000)
            printf("Enter valid quantity \n");
        else
            return quantity;
    } while (1);
}

int getValidInitialNumber() {
    int n;
    do {
        printf("\nEnter initial number of products: ");
        scanf("%d", &n);
        if (n < 1 || n > 100)
            printf("Invalid number of products.\n");
        else
            return n;
    } while (1);
}

void addProduct(int *n, Product **prod) {
    *n = *n + 1;
    *prod = (Product *)realloc(*prod, (*n) * sizeof(Product));
    if (*prod == NULL) {
        printf("\nMemory allocation failed!");
        exit(1);
    }

    printf("\nEnter details of new Product %d:\n", *n);

    (*prod + (*n - 1))->ID = getValidateProductID(*prod, *n - 1);
    getValidateProductName((*prod + (*n - 1))->name);
    (*prod + (*n - 1))->price = getValidateProductPrice();
    (*prod + (*n - 1))->quantity = getValidateProductQuantity();

    printf("\nProduct added successfully!\n");
}

void viewProducts(int n, Product *prod) {
    if (n == 0) {
        printf("\nThere aren't any products available.");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\nDetails of Product %d:", i + 1);
        printDetails((prod + i)->ID, (prod + i)->name, (prod + i)->price, (prod + i)->quantity);
        printf("\n----------------------------\n");
    }
}
//
void printDetails(int id, char name[], float price, int quantity) {
    printf("\nProduct ID: %d", id);
    printf("\nProduct Name: %s", name);
    printf("\nProduct Price: %.2f", price);
    printf("\nProduct Quantity: %d", quantity);
}

void updateQuantity(int n, Product *prod) {
    if (n == 0) {
        printf("\nNo products available to update.\n");
        return;
    }

    int id;
    printf("\nEnter Product ID to update quantity: ");
    scanf("%d", &id);

    int index = findProductIndexByID(prod, n, id);
    if (index == -1) {
        printf("\nProduct with ID %d not found.\n", id);
        return;
    }

    printf("\nCurrent quantity of '%s' is %d", (prod + index)->name, (prod + index)->quantity);
    (prod + index)->quantity = getValidateProductQuantity();

    printf("\nQuantity updated successfully!\n");
    printDetails((prod + index)->ID, (prod + index)->name, (prod + index)->price, (prod + index)->quantity);
}




void searchByID(int n, Product *prod) {
    if (n == 0) {
        printf("\nNo products available to search.\n");
        return;
    }

    int id;
    printf("\nEnter Product ID to search (1–10000): ");
    scanf("%d", &id);

    int index = findProductIndexByID(prod, n, id);
    if (index == -1) {
        printf("\nProduct with ID %d not found.\n", id);
    } else {
        printf("\nProduct found!\n");
        printDetails((prod + index)->ID, (prod + index)->name, (prod + index)->price, (prod + index)->quantity);
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


void searchByName(int n, Product *prod) {
    if (n == 0) {
        printf("\nNo products available to search.\n");
        return;
    }

    char name[50];
    getValidateProductName(name); 

    int found = 0;
    printf("\nSearching for products matching '%s'...\n", name);

    for (int i = 0; i < n; i++) {
        if (kmp(name, (prod + i)->name)) {
            if (!found) {
                printf("\nMatching product found:\n");
            }
            found = 1;
            printDetails((prod + i)->ID, (prod + i)->name, (prod + i)->price, (prod + i)->quantity);
            printf("\n----------------------------\n");
        }
    }

    if (!found)
        printf("\nNo product found with name '%s'.\n", name);
}

int getValidateLowHighPrice(float low_price, float high_price) {
    if (low_price < 0 || high_price < 0 || high_price > 100000 || low_price > high_price) {
        printf("Invalid price range!\n");
        return 0;
    }
    return 1;
}

void searchByPriceRange(int n, Product *prod) {
    if (n == 0) {
        printf("\nNo products available to search.\n");
        return;
    }

    float low_price, up_price;

    do {
        printf("\nEnter lower range of Price: ");
        scanf("%f", &low_price);

        printf("Enter upper range of Price: ");
        scanf("%f", &up_price);
    } while (!getValidateLowHighPrice(low_price, up_price));

    int found = 0;

    

    for (int i = 0; i < n; i++) {
        if ((prod + i)->price >= low_price && (prod + i)->price <= up_price) {
            if (!found)
                printf("\nMatching product(s) found:\n");
            found = 1;
            printDetails((prod + i)->ID, (prod + i)->name, (prod + i)->price, (prod + i)->quantity);
            printf("\n----------------------------\n");
        }
    }

    if (!found)
        printf("\nNo products found in the given price range.\n");
}


void deleteProduct(Product *prod, int *n) {
    if (*n == 0) {
        printf("\nNo products available to delete.\n");
        return;
    }

    int id;
    printf("\nEnter the Product ID to delete: ");
    scanf("%d", &id);

    int index = findProductIndexByID(prod, *n, id);
    if (index == -1) {
        printf("\nProduct with ID %d not found.\n", id);
        return;
    }

    printf("\nProduct found:\n");
    printDetails((prod + index)->ID, (prod + index)->name, (prod + index)->price, (prod + index)->quantity);

    for (int j = index; j < *n - 1; j++) {
        *(prod + j) = *(prod + j + 1);
    }
    (*n)--;

    printf("\nProduct deleted successfully.\n");
}

int main() {
    int n = getValidInitialNumber();
    Product *prod = (Product *)calloc(n, sizeof(Product));

    printf("\nEnter initial product details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProduct %d:\n", i + 1);
        (prod + i)->ID = getValidateProductID(prod, i);
        getValidateProductName((prod + i)->name);
        (prod + i)->price = getValidateProductPrice();
        (prod + i)->quantity = getValidateProductQuantity();
    }

    int choice;
    do {
        printf("\n========= PRODUCT MANAGEMENT SYSTEM =========\n");
        printf("1. Add Product\n");
        printf("2. Update Quantity\n");
        printf("3. Search by ID\n");
        printf("4. Search by Name\n");
        printf("5. Search by Price Range\n");
        printf("6. Delete Product\n");
        printf("7. Display All Products\n");
        printf("8. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(&n, &prod);
                break;

            case 2:
                updateQuantity(n, prod);
                break;

            case 3:
                searchByID(n, prod);
                break;

            case 4:
                searchByName(n, prod);
                break;

            case 5:
                searchByPriceRange(n, prod);
                break;

            case 6:
                deleteProduct(prod, &n);
                break;

            case 7:
                viewProducts(n, prod);
                break;

            case 8:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }

    } while (choice != 8);

    free(prod);
    return 0;
}