#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book {
  char ID[20];
  char title[80];
  char author[50];
  double price;
  int year;
  char press[80];
  struct Book*next;
};

struct Book* head = NULL;
struct Book* current = NULL;

void Menu();
void Load();
void Save();
void InsertNewBook();
void Update();
void SearchID();
void SearchAuthor();
void ShowAll();

int main() {
  Menu();
  Load();
  
  return 0;
}

void Menu() {
  int choice = 0;

  for(;;) {
    printf("\n  |x|-----------------------------------------------------------------|");
    printf("\n  |0|- Exit                                                           |");
    printf("\n  |-|-----------------------------------------------------------------|");
    printf("\n  |1|- Add new book                                                   |");
    printf("\n  |-|-----------------------------------------------------------------|");
    printf("\n  |2|- Update data                                                    |");
    printf("\n  |-|-----------------------------------------------------------------|");
    printf("\n  |3|- Search with ID                                                 |");
    printf("\n  |-|-----------------------------------------------------------------|");
    printf("\n  |4|- Search with author                                             |");
    printf("\n  |-|-----------------------------------------------------------------|");
    printf("\n  |5|- Show all books                                                 |");
    printf("\n  |x|-----------------------------------------------------------------| \n");

  do {
    printf("Enter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);
  } while(!(choice >= 0 && choice <= 5));
      printf("%d\n", choice);
    switch(choice) {
      case 1: {
        // Load();
        InsertNewBook();
        // Save();
        head = NULL;
        break;
      }
      case 2: {
        // Load();
        Update();
        // Save();
        head = NULL;
        break;
      }
      case 3: {
        // Load();
        SearchID();
        head = NULL;
        break;
      }
      case 4: {
        // Load();
        SearchAuthor();
        head = NULL;
        break;
      }
      case 5: {
        // Load();
        ShowAll();
        head = NULL;
        break;
      }
      case 0: {
        Save();
        exit(2);
      }
    }
  }
}

void Load() {
  FILE *fp;
  int flag, sizeID, sizeTitle, sizeAuthor, sizePress;
  struct Book *p;

  if((fp = fopen("books", "rb")) == NULL) {
    printf("Error opennig file!");
    exit(0);
  }
  while(1) {
    if(fread(&flag, sizeof(int), 1, fp)!=1) {
      printf("Error reading!");
      exit(4);
    }
    if(flag == -1) {
      break;
    }
    struct Book *temp = (struct Book*)malloc(sizeof(struct Book));
    if(head == NULL) {
      head = temp;
      current = head;
      current->next = NULL;
    } else {
      current->next = temp;
      current = temp;
      current->next = NULL;
    }
    if((fread(temp->ID, flag, 1, fp))!=1) {
			printf("Error reading!\n");
			exit(4);
		}
    if((fread(&sizeTitle, sizeof(int), 1, fp))!=1) {
      printf("Error reading sizeTitle!");
      exit(2);
   }
   if(fread(temp->title, sizeTitle, 1, fp)!=1) {
      printf("Error reading title!");
      exit(2);
   }
   if(fread(&sizeAuthor, sizeof(int), 1, fp)!=1) {
      printf("Error reading sizeAuthor!");
      exit(2);
   }
   if(fread(temp->author, sizeAuthor, 1, fp)!=1) {
      printf("Error reading author!");
      exit(2);
   }
   if(fread(&temp->price, sizeof(double), 1, fp)!=1) {
      printf("Error reading price!");
      exit(2);
   }
   if(fread(&temp->year, sizeof(int), 1, fp)!=1) {
      printf("Error reading year!");
      exit(2);
   }
   if(fread(&sizePress, sizeof(int), 1, fp)!=1) {
      printf("Error reading sizePress!");
      exit(2);
   }
   if(fread(temp->press, sizePress, 1, fp)!=1) {
      printf("Error reading press!");
      exit(2);
   }
  }
  fclose(fp);
}

void InsertNewBook() {
  struct Book *temp;
  temp = head;
  while(temp->next!=NULL) {
    temp = temp->next;
  }
  struct Book *n;
  n = (struct Book*)malloc(sizeof(struct Book));
  // if (head == NULL) {
  //   head = temp;
  //   current = head;
  //   current->next = NULL;
  // } else {
  //   current->next = temp;
  //   current = temp;
  //   current->next = NULL;
  // }
  printf("Your have chosen adding new book!\n");
  printf("\n  |-|----------------------------------------------------------------|");
  printf("Enter ID number (it should consist of 20 digits): \n");
  printf("\n  |-|----------------------------------------------------------------|");
  scanf("%s", temp->ID);
  printf("\n  |-|----------------------------------------------------------------|");
  printf("Enter the title of the book: \n");
  printf("\n  |-|----------------------------------------------------------------|");
  scanf("%s", temp->title);
  printf("\n  |-|----------------------------------------------------------------|");
  printf("Enter the author of the book: \n");
  printf("\n  |-|----------------------------------------------------------------|");
  scanf("%s", temp->author);
  printf("\n  |-|----------------------------------------------------------------|");
  printf("Enter the price of the book: \n");
  printf("\n  |-|----------------------------------------------------------------|");
  scanf("%lf", &temp->price);
  printf("\n  |-|----------------------------------------------------------------|");
  printf("Enter the year of publishing: \n");
  printf("\n  |-|----------------------------------------------------------------|");
  scanf("%d", &temp->year);
  printf("\n  |-|----------------------------------------------------------------|");
  printf("Enter the name of the press: \n");
  printf("\n  |-|----------------------------------------------------------------|");
  scanf("%s", temp->press);
  printf("\n  |-|----------------------------------------------------------------|");
  printf("\n\t\t\t\t\t\tSUCCESS\n");
  printf("\n  |-|----------------------------------------------------------------|");
}

void Update() {
  int flag = 0;
  char *IDnum;
  struct Book *n;
  struct Book *temp = (struct Book*)malloc(sizeof(struct Book));
  printf("Enter ID number to search: ");
  gets(IDnum);

  for(n = head; n!=NULL; n = n->next) {
    if(!(strcmp(temp->ID, IDnum))) {
      printf("ID: %s found!\n", IDnum);
      flag = 1;
    }
    printf("Enter the title of the book: \n");
    scanf("%s", temp->title);
    printf("Enter the author of the book: \n");
    scanf("%s", temp->author);
    printf("Enter the price of the book: \n");
    scanf("%lf", &temp->price);
    printf("Enter the year of publishing: \n");
    scanf("%d", &temp->year);
    printf("Enter the name of the press: \n");
    scanf("%s", temp->press);
  }
  if(flag == 0) {
    printf("ID: %s not found!\n", IDnum);
  }
}

void SearchID() {
  int flag = 0;
  char *IDnum;
  struct Book* m;
  struct Book* temp;
  IDnum = (char*)malloc(20);
  printf("Enter ID number to search: ");
  gets(IDnum);

  temp = (struct Book*)malloc(sizeof(struct Book));
  temp = head;
  while(temp != NULL) {
    if(!(strcmp(temp->ID, IDnum))) {
      printf("ID: %s found!\n", IDnum);
      printf("|title: %s|author: %s|price: %lf|year: %d|press: %s|\n", temp->title, temp->author, temp->price, temp->year, temp->press);
      flag = 1;
    }
    temp = temp->next;
  }
  if(flag == 0) {
    printf("ID: %s not found!\n", IDnum);
  }
}

void SearchAuthor() {
  int flag = 0;
  char *authorSearch;
  struct Book* m;
  struct Book* temp;
  authorSearch = (char*)malloc(50);
  printf("Enter author name to search: ");
  gets(authorSearch);

  temp = (struct Book*)malloc(sizeof(struct Book));
  temp = head;
  while(temp!=NULL) {
    if(!(strcmp(temp->author, authorSearch))) {
      printf("Author: %s found!\n", authorSearch);
      printf("|ID: %s|title: %s|price: %lf|year: %d|press: %s|\n", temp->ID, temp->title, temp->price, temp->year, temp->press);
      flag = 1;
    }
    temp = temp->next;
  }
  if(flag == 0) {
    printf("Author: %s not found!\n", authorSearch);
  }
}

void ShowAll() {
  struct Book* m;
  for(m = head; m!=NULL; m = m->next) {
    printf("|ID: %s|title: %s|author: %s|price: %lf|year: %d|press: %s|\n", m->ID, m->title, m->author, m->price, m->year, m->press);
  }
}

void Save() {
  FILE *fp;
  int flag = -1, sizeID = 0, sizeTitle = 0, sizeAuthor = 0, sizePress = 0;

  struct Book *temp;
  temp = head;

  if((fp = fopen("books", "wb")) == NULL) {
    printf("Error openning file!");
    exit(0);
  }

  // for(temp = head; temp!=NULL; temp = temp->next) {
  while(temp!=NULL) {
    sizeID = strlen(temp->ID); sizeID++;
    sizeTitle = strlen(temp->title); sizeTitle++;
    sizeAuthor = strlen(temp->author); sizeAuthor++;
    sizePress = strlen(temp->press); sizePress++;
    // if((fwrite(&flag, sizeof(int),1, fp))!=1) {
    //   printf("Error writing flag!\n");
    //   fclose(fp);
    // }
    if((fwrite(temp->ID, sizeID, 1, fp))!=1) {
			printf("Error writing!\n");
			exit(1);
		}
    if(fwrite(&sizeTitle, sizeof(int), 1, fp)!=1) {
      printf("Error writing sizeTitle");
      exit(1);
   }
   if(fwrite(temp->title, sizeTitle, 1, fp)!=1) {
      printf("Error writing title!");
      exit(1);
   }
   if(fwrite(&sizeAuthor, sizeof(int), 1, fp)!=1) {
      printf("Error writing sizeAuthor!");
      exit(1);
   }
   if(fwrite(temp->author, sizeAuthor, 1, fp)!=1) {
      printf("Error writing author!");
      exit(1);
   }
   if(fwrite(&temp->price, sizeof(double), 1, fp)!=1) {
      printf("Error writing price!");
      exit(1);
   }
   if(fwrite(&temp->year, sizeof(int), 1, fp)!=1) {
      printf("Error writing year!");
      exit(1);
   }
   if(fwrite(&sizePress, sizeof(int), 1, fp)!=1) {
      printf("Error writing sizePress");
      exit(1);
   }
   if(fwrite(temp->press, sizePress, 1, fp)!=1) {
      printf("Error writing press");
      exit(1);
   }
   temp = temp->next;
  }
  if((fwrite(&flag, sizeof(int), 1, fp))!=1) {
    printf("Error writing flag!");
    exit(1);
  }
  fclose(fp);
}
