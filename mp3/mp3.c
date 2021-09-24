// MP3
/*

For this MP we focused on turning the binomial equation into then, and then 
we figured out how each of the parts must iterate over a loop. Initially we
thought we'd need to use factorial, so we made an external recursive function.
Though we realized that by just using the equation provided, we wouldn't
need that. We used a for loop to increment a counter i (same as i in the binomial equation)
until it was more than the number of rows provided.

Partners: jumanas2, macraew2

*/

#include <stdio.h>
#include <stdlib.h>


int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here

  unsigned long out;

  int i;
  for(i = 0; i<=row; i++){
    if(i == 0){
      out = 1;
    }
    else{
      out = ((row + 1 - i)*out) / i;
    }
    printf("%lu ",out);
  }
  

  return 0;
}
/*
unsigned long binomial(unsigned long i, unsigned long n){
  if(i == 0){
    return 1;
  }
  unsigned long out = (n + 1 - i)*n / i;
  return out * binomial(i, n);

}
*/
/*
unsigned long factorial(unsigned long x){

  if(x == 0){
    return 1;
  }
  else{
    return x * factorial(x-1);
  }
}
*/

/*
unsigned long pow(unsigned long base, int exp){
  if(exp == 0){
    return 1;
  }
  else if(exp == 1){
    return base;
  }
  else{
    return base * pow(base, exp-1);
  }
}
*/

