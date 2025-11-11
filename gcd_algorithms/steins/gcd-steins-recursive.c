#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Steins is just Euclids optimised by
 * halving using bit-wise operations.
 * 
 * First published 1967 by Josef Stein.
 *
 * References
 * https://www.blackwasp.co.uk/steinsalgorithm.html
 * https://medium.com/@m.langer798/stein-vs-stein-on-the-jvm-c911809bfce1
 */

typedef unsigned long long u64;

#define MAX_LINE_LENGTH 1024
#define MAX_INPUTS 24

u64 get_gcd(u64 x, u64 y);
void swap(u64 *x, u64 *y);

int main()
{
    char line[MAX_LINE_LENGTH];
    u64 inputs[MAX_INPUTS];
    
    int count;
    char *token, *rest;
    u64 a, b;

    /* 
     * Split input text by spaces  and convert into ints 
     * using strtok_r() and strtol() 
     */

    rest = NULL;
    count = 0;

    fgets(line, sizeof(line), stdin);

    for (token = strtok_r(line, " ", &rest);
        token != NULL;
        token = strtok_r(NULL, " ", &rest)) {
        inputs[count++] = strtoull(token, NULL, 10);
    }

    if (count == 0 || count > 2) {
        /* no input or too much input */
        printf("this version only accepts two inputs.\n");
        return 1;
    }
    else if (count > 0) {
        for (int i = 0; i+1 < count; i+=2) {
            a = inputs[i];
            b = inputs[i+1];
            printf("gcd(%llu, %llu) =  %llu\n", a, b, get_gcd(a, b));
        }
    }

    return 0;
}


u64 get_gcd(u64 x, u64 y)
{
    int x0s, y0s, k;

    /* 
     * case 1 & 2: one is zero
     * or the other is zero 
     * or they are equal
     */

    if (x == 0) return y;
    if (y == 0) return x;
    if (x == y) return x;

    /* 
    * the number of trailing zeros
    * expresses by what k the number can be divided by 2**k
    */

    /* get the trailing zeros of an unsigned long long... */
    x0s = __builtin_ctzll(x);
    y0s = __builtin_ctzll(y);

    // debug
    // printf("trailing zeros... %d, %d\n", x0s, y0s);

    /*
    * case 3: both are even
    * 2 is the lowest common divisor, so factor is out
    * and try again
    */
    if (x0s > 0 && y0s > 0) {
        // get which ever is the min.
        k = (x0s < y0s) ? x0s : y0s;
        /* NOTE
        * we could've OR'ed x and y before counting the trailing zeros
        * to the same effect as the line above.
        */

        return (get_gcd(x >> k, y >> k) << k);

    /*
    * case 4: one of the numbers is even
    * if X is even but Y is odd
    * then 2 is not a common divisor
    * so the GCD is the GCD(x/2,y)
    */
    } else if (x0s > 0 && y0s <= 0) {
        return get_gcd(x >> x0s, y);
    }
    else if (y0s > 0 && x0s <= 0) {
        return get_gcd(x, y >> y0s);
    } else {
        /*
        * case 5: both are odd
        * use euclids (ie the difference of the larger - smaller)
        * & also apply case 4 (since odd - odd = even)
        */

        if (x < y) {
            return get_gcd(x, y-x);
        }
        else if (y < x) {
            return get_gcd(x-y,y);
        }
        else {
            return x;
        }
    }
}

/*
 * TODO
 * do the non-recursive approach
 * as read somewhere it runs faster
 * e.g. using the below
 * c.f. the euclid implementation
 */

void swap(u64 *x, u64 *y)
{
    if (x != y) {
        *x = *x^*y;
        *y = *x^*y;
        *x = *x^*y;
    }
}
