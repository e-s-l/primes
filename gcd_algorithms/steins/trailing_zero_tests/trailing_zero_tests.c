#include <stdio.h>
#include <math.h>

typedef unsigned long long u64;

int main()
{

    u64 a, a0s, n, res;
    int k;

    a = 1023024216;

    a0s = __builtin_ctzll(a);
    printf("trailing zeros of %llu = %llu\n", a, a0s);

    /**
    number n is divisble by (2**k)
    iff
    k trailing digits of n are 0
    */

    /*
    let n = a (=10)
    k = 1 (2**k = 2)
    */

    n = a;
    k = 1;

    for (int k = 0; k < 5; k++){

        if (a0s >= k) {

            printf("%llu is divisible by 2^%d = %.0f\n", n, k, pow(2,k));


            /**
            multiplication of n by (2**k)
            is equivalent to 
            left shifting  the digits of n k times,
            conversely for division:
            */

            res = (n >> k);

            printf("result of division: %llu\n", res);


        }
        else {
            printf("%llu is NOT divisible by 2^%d\n", n, k);
        }
        
    }
    return 0;
}
