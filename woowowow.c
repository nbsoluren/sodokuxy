#include <stdio.h>

void hello (int *i){
  int b = *i;
  printf("wow %d\n",  b);
}

int main(){
  int i = 10;
  hello(&i);
  return 0;
}
