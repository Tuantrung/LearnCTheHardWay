#include <stdio.h>
void crash(/* arguments */) {
  char *test = NULL;
  int i = 0;

  for(i=0;i<1000000;i++){
    printf("c",test[i]);
  }
}
int main(void)
{
  int age; //10
  int height = 72;
  // printf(NULL); //age
  printf("I am %d inches tall.\n", height);
  crash();
  
  return 0;
}
