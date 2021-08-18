#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;
  // while (i<25) {
  //   /* code */
  //   printf("%d \n", i);
  //   i++;
  // }
  // go through each string in argv
  for (i=1;i<argc;i++) {
    printf("arg %d: %s.\n", i, argv[i]);
  }
  // let make our own array of strings
  char *state[] = {"California", "Oregon", "Washington", "Texas"};
  int num_state = 4;
  for (i=0;i<num_state;i++) {
    printf("state %d: %s \n", i, state[i]);
  }
  return 0;
}
