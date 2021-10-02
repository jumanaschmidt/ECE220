#include <stdlib.h>
#include <stdio.h>

/*
    The two errors are the return values in the int is_prime, so I just switched them.
    to return 1 when there is a semiprime. The second error that you need a break to get out of the for 
    loop because you don't need to keep incrementing j to find semiprime. Then it lets you increment
    i. The third error is k = i%j because it needs to be k = i/j since it takes the number from your
    input and divides it by the counter to then check if it it prime. This follows what a semiprime
    number is, since it's checking if k and j are both prime and their product is semiprime number
    i.

    Partner: macraew2

*/


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1;
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
