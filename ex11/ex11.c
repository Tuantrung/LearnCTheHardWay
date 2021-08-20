#include "stdio.h"
#include <string.h>

int main(int argc, char *argv[]) {
  /* code */
  int numbers[4] = { 0 };
  char name[4] = { '\0', '!' };

  // first print them out raw
  printf("numbers: %d %d %d %d\n",
          numbers[0], numbers[1], numbers[2], numbers[3]);

  printf("name each: %c %c %c %c\n",
          name[0], name[1], name[2], name[3]);

  printf("name: %s\n", name);

  // set up the numbers
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;

  // set up the names
  name[0] = 'Z';
  name[1] = 'e';
  name[2] = 'd';
  name[3] = '\0';

  int name_int;

  printf("name: %c %c %c %c\n",
          name[0], name[1], name[2], name[3]);

  printf("0x%x \n", (*(int*)name) );

  printf("%d \n", (*(int*)name) );

  memcpy(&name_int, &name, sizeof name_int);

  // then print them out initialized
  printf("numbers: %d %d %d %d\n",
          numbers[0], numbers[1], numbers[2], numbers[3]);

  printf("name: %c %c %c %c\n",
          name[0], name[1], name[2], name[3]);

  // print the name like a string
  printf("int of name: %d\n", name_int);

  // another way to use names
  char *another = "Zed";

  printf("another: %s\n", another);

  printf("another each: %c %c %c %c\n",
          another[0], another[1], another[2], another[3]);

  return 0;
}
