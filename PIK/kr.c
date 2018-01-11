#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool func1(void);
bool func2(void);
bool func3(void);
bool func4(void);

void reading(FILE *file);

int counter_loop = 0;

int counter_symbol = 0;

int main() {
  int option;

  printf("Enter number 1 for reading the program from file and save the result in another file.\n");
  printf("Enter number 2 for reading the program from file and print the result in the screen.\n");
  printf("Enter number 3 for writing the program from the console and print the result in file.\n");
  printf("Enter number 4 for writing the program from the console and print the result in the screen.\n");
  printf("Enter option: ");

  scanf("%d", &option);

  bool success = false;

  switch(option) {
      case 1: success = func1();
        break;
      case 2: success = func2();
        break;
      case 3: success = func3();
        break;
      case 4: success = func4();
        break;
      default: printf("Invalid function. Choose number from 1 - 4!\n");
        return 1;
        break;
  }

  if(success == false) return 2;

  return 0;
}

bool func1(void) {
  char fileread[20];
  char filewrite[20];
  bool check = false;

  printf("Enter a name for a file for reading: ");

  scanf("%s", fileread);

  for(int i = 0; i < strlen(fileread); i++) {
      if(fileread[i] == '.' && fileread[i+1] == 'c') {
        check = true;
      }
  }

  if(!check) {
    printf("Error: The file must be .c format!\n");
    return false;
  }

  FILE *fpr = fopen(fileread, "r");

  if(fpr == NULL) {
    printf("Error: Cannot open file\n");
    return false;
  }

  printf("Enter a name for a file to print the result: ");

  scanf("%s", filewrite);

  FILE *fpw = fopen(filewrite, "w");

  if(fpw == NULL) {
    printf("Error: Cannot open file\n");
    return false;
  }

  reading(fpr);

  fprintf(fpw,"Number of printable characters in comments: %d\n", counter_symbol);
  fprintf(fpw,"Number of loop operators: %d\n", counter_loop);

  fclose(fpr);
  fclose(fpw);

  return true;
}

bool func2(void) {
  char fileread[20];

  printf("Enter a name for a file for reading: ");

  scanf("%s", fileread);

  bool check = false;

  for(int i = 0; i < strlen(fileread); i++) {
    if(fileread[i] == '.' && fileread[i+1] == 'c')
    check = true;
  }

  if(!check) {
    printf("Error: The file must be .c format!\n");
    return false;
  }

  FILE *fpr = fopen(fileread, "r");

  if(fpr == NULL) {
    printf("Error: Cannot open file\n");
    return false;
  }

  reading(fpr);

  printf("Number of printable characters in comments: %d\n", counter_symbol);
  printf("Number of loop operators operations: %d\n", counter_loop);

  fclose(fpr);

  return true;
}

bool func3(void) {
  char filewrite[20];

  printf("Enter a name for a file to print the result: ");
  scanf("%s", filewrite);

  FILE *fpw = fopen(filewrite, "w");

  if(fpw == NULL) {
    printf("Error: Cannot open file\n");
    return false;
  }

  printf("Enter programm here (if you want to stop enter Cntl+D):\n");

  reading(stdin);

  fprintf(fpw,"Number of printable characters in comments: %d\n", counter_symbol);
  fprintf(fpw,"Number of loop operators operations: %d\n", counter_loop);

  fclose(fpw);

  return true;
}

bool func4(void) {
  printf("Enter programm here (if you want to stop enter Cntl+D):\n");

  reading(stdin);

  printf("Number of printable characters in comments: %d\n", counter_symbol);
  printf("Number of loop operators operations: %d\n", counter_loop);

  return true;
}

void reading(FILE* file) {
  bool flag1 = false;
  bool flag2 = false;

  char c = fgetc(file);

  while(c!=EOF) {
    char string_var[100] = { 0 };

    for(int i = 0; (c!='\n' && c!='\t' && c!=' '); i++) {
        string_var[i]=c;

        if(c == '/') {
          c = fgetc(file);

          if(c == EOF) break;

          if(c == '/') {
            flag1 = true;

            c = fgetc(file);

            if(c == EOF) break;
          }
          if(c == '*') {
            flag2 = true;

            c = fgetc(file);
          }
        }
        if(flag2 && c == '*') {
          c = fgetc(file);

          if(c == EOF) break;

          if(c == '/') flag2 = false;

          else counter_symbol++;
        }
        if((flag1 || flag2) && isprint(c)) counter_symbol++;

        c = fgetc(file);
    }

    if(c == '\n') flag1 = false;

    if(strstr(string_var, "for") != NULL) counter_loop++;

    if(strstr(string_var, "while") != NULL) counter_loop++;

    c = fgetc(file);
  }
}
