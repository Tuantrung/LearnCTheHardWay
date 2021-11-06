#include "stdio.h"

int main(int argc, char *argv[])
{
<<<<<<< HEAD
  /* code */
=======
>>>>>>> aa98a06e84b1d0000db8f2a8a284c004ba61de0e
  int areas[] = { 10, 12, 13, 14, 20 };
  char name[] = "Zed";
  char full_name[] = {
       'Z', 'e', 'd',
       ' ', 'A', '.', ' ',
       'S', 'h', 'a', 'w', '\0'
  };

  /* WARNING: On some systems you may have to change the
  %ld in this code to a %u since it will use unsigned int */
  printf("The size of an int: %ld\n", sizeof(int));
  printf("The size of areas (int[]): %ld\n", sizeof(areas));
  printf("The numbers of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
<<<<<<< HEAD
  printf("The first area is %d, the 2nd is %d.\n\n", areas[0], areas[1]);
=======
  printf("The first area is %c, the 2nd is %c.\n\n", (char)areas[0], (char)areas[1]);
>>>>>>> aa98a06e84b1d0000db8f2a8a284c004ba61de0e

  printf("The size of a char: %ld\n", sizeof(char));
  printf("The size of name (char[]): %ld\n", sizeof(name));
  printf("The number of chars: %ld\n\n", sizeof(name)/sizeof(char));
<<<<<<< HEAD

  printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
  printf("The number of chars: %ld\n", sizeof(full_name)/sizeof(char));
  printf("name=\"%s\" and full_name=\"%s\"\n\n", name, full_name);
=======
  
  printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
  printf("The number of chars: %ld\n", sizeof(full_name)/sizeof(char));
  printf("name=\"%s\" and full_name=\"%s\"\n\n", name, full_name);

>>>>>>> aa98a06e84b1d0000db8f2a8a284c004ba61de0e
  return 0;
}
