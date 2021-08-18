/* this program covert higher charaters in a string to lower charaters */
#include <stdio.h>

int main(int argc, char *argv[])
{
  /* code */
  if ( argc != 2) {
    printf("ERROR: The argument must be one.\n");
    // this is how you abort the program
    return 1;
  }

  int i = 0;

  for (i = 0; argv[1][i] != '\0'; i++) {
    if ( argv[1][i] >= 'A' && argv[1][i] <= 'Z') {
      argv[1][i] += 32;
    } else continue ;
  }

  printf("%s.\n", argv[1]);

  return 0;
}
