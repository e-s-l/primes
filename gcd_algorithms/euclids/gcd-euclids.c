#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 
 * TODO
 * Use the associative property of GCD 
 * to calculate the GCD of allll the input numbers
 *
 * References:
 * https://cp-algorithms.com/algebra/euclid-algorithm.html
 * 
 * https://www.cmastery.digibeatrix.com/en/pointers-and-memory-management/c-language-swap-function-pointer-guide/
 */

typedef unsigned long long u64;

#define MAX_LINE_LENGTH 1024
#define MAX_INPUTS 24

u64 euclids_recursive(u64 x, u64 y);
u64 euclids(u64 x, u64 y);
void swap(u64 *x, u64 *y);
u64 lcm(u64 x, u64 y);

int main()
{
    char line[MAX_LINE_LENGTH];
    u64 inputs[MAX_INPUTS];
    
    int count;
    char *token, *rest;
    u64 a, b;

    rest = NULL;
    count = 0;

    fgets(line, sizeof(line), stdin);
   
    /* split input text by spaces into ints 
     * using strtok_r() and strtol() */

    for (token = strtok_r(line, " ", &rest);
        token != NULL;
        token = strtok_r(NULL, " ", &rest)) {
        inputs[count++] = strtol(token, NULL, 10);
    }

    for (int i = 1; i < count; i++) {
        a = inputs[i-1];
        b = inputs[i];
        printf("gcd(%llu, %llu) =  %llu\n", a, b, euclids_recursive(a, b));
        //printf("lcm(%llu, %llu) = %llu\n", a, b, lcm(a, b));
    }

    return 0;
}


u64 euclids_recursive(u64 x, u64 y)
{
    if (y == 0) {
        return x;
    }

    return euclids_recursive(y, x % y);
}

u64 lcm(u64 x, u64 y)
{

    return (x / euclids_recursive(x,y)) * y;

}

/* a non-recursive approach */

u64 euclids(u64 x, u64 y)
{
    while (y > 0){
        x %= y;
        swap(&x, &y);
    }

    return x;
}

void swap(u64 *x, u64 *y)
{
    u64 temp = *x;
    *x = *y;
    *y = temp;
}

/* 
 * some alternatives
 * untested
 */
u64 euclids_2(u64 x, u64 y)
{
    u64 t;

    while (y > 0) {
        t = y;
        y = x % y;
        x = t;
    }

    return x;
}

void swap_no_temp(u64 *x, u64 *y)
{
    if (x != y) {
        *x = *x^*y;
        *y = *x^*y;
        *x = *x^*y;
    }
}

void swap_no_temp_2(u64 *x, u64 *y)
{
    if (x != y) {
        *x = *x + *y;
        *y = *x - *y;
        *x = *x - *y;
    }
}
