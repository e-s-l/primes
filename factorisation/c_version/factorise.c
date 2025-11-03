#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>         // for getopt (simple)
#include <stdlib.h>         // for strtol (string to long int)
#include <math.h>           // for ceil, round, &c

/*
 *
 * This program takes a naive approach to the two main components 
 * (these being the primality test and Fermat's factorisation scheme).
 * Later work would e.g. adopt the seive form of Fermat's scheme.
 *
 * Moved on from this before finishing it up properly.
 * Earlier versions proably better.
 * See "decomposer.c" for complete version.
 */

/* unsigned long long int*/
typedef __uint64_t u64;

void print_help();
void print_help_and_die(int x);
bool is_prime(u64 n);
bool is_prime_min(u64 n);
u64 fermat(u64 n);
u64 trial_division(u64 n);
u64 factorise_naive(u64 n);
u64 factorise(u64 n);

int main(int argc, char *argv[])
{
    int opt;
    bool debug = false;
    u64 n = 0;

    while((opt = getopt(argc, argv, "n:dh")) != -1) {
        switch(opt) {
            // help
            case 'h':
                printf("Help requested:\n");
                print_help_and_die(0);
            // debug
            case 'd':
                debug = 1;
                break;
            // get input number
            case 'n':
                if(!optarg) {
                    printf("Please specify the number to factorise.\n");
                    print_help_and_die(1);
                }
                n = strtol(optarg, NULL, 10);
                break;
        }
    }

    if (n == 0) {
        printf("Invalid input: %lld\n", n);
        print_help_and_die(1);
    }
    // method only works for composite numbers
    if (is_prime(n)) {
        printf("The number %lld is not composite.\n", n);
        print_help_and_die(0);
    }

    factorise(n);

    return 0;
}

/*
 * function: fermat
 * ----------------
 *  uses naive form of fermat's difference of squares factorisation
 *
 *  n: the odd, composite integer we want to find factors of
 *  
 *  returns: a - b, one of the factors... FIXME
 *
 *  ref:
 *  https://cp-algorithms.com/algebra/factorization.html
 *
 */
u64 fermat(u64 n)
{
    u64 a = ceil(sqrt(n));
    u64 b2 = a*a - n;
    u64 b = round(sqrt(b2));
    
    while (b * b != b2) {
        a = a + 1;
        b2 = a*a - n;
        b = round(sqrt(b2));
    }

   // two factors: a+b, a-b
    return a - b;
}

/*
 * function: is_prime
 * ------------------
 *  a basic primality test
 *  checking possible divisors
 *
 *  x: the number to test
 *
 *  returns: boolean result of test
 *
 *  ref:
 *  https://cp-algorithms.com/algebra/primality_tests.html
 *
 */

bool is_prime(u64 x)
{
    if (x <= 1) return false;
    if (x == 2) return true;
    if (x % 2 == 0 ) return false;

    return trial_division(x) == 1;
}

/*
 * function: trial_division
 * ------------------------
 *
 * x: the integer to test for factors
 *
 * returns: a found factor
 */
u64 trial_division(u64 x)
{

    if (x <= 1) return 1;
    if (x % 2 == 0) return 2;

    for (u64 d = 3; d * d <= x; d += 2) {
        if (x % d == 0) {
            return d;
        }
    }

    return 1;
}

u64 factorise(u64 n)
{
    u64 d = 1;

    do {
        /*
        * we use fermat's factorisation when odd
        * and simple trial division when even.
        */

        if (n % 2 == 0) {
            d = trial_division(n);
        }
        else {
            d = fermat(n);
        }

        n /= d;
        if (d != 1) printf("n = %lld, d = %lld\n", n, d);

    } while (d != 1);

    return 1;
}


/*
 * function: print_help_and_die
 * ----------------------------
 *  calls print_help and exits with the passed exit code
 *
 *  x: the exit status, recall 0 is normal in C.
 *
 */
void print_help_and_die(int x)
{
    print_help();
    exit(x);
}

/*
 * function: print_help
 * --------------------
 *  prints the usage message
 *
 */
void print_help()
{
    printf("HELP!\n");
}
