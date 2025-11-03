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
 */

/* unsigned long long int*/
typedef __uint64_t u64;

/* surely theres some theorem constraining the number of factors... */
#define MAX_FACTORS 1024

void print_help();
void print_help_and_die(int x);
bool is_prime(u64 n);
u64 trial_division(u64 n);
void fermat(u64 n, u64 *f1, u64 *f2);
void halve(u64 n, u64 *f1, u64 *f2);
void factorise(u64 n, u64 *factors, int *count);
int comp(const void *a, const void *b);

int main(int argc, char *argv[])
{
    int opt;                    /* command line options */
    bool debug = false;
    u64 n = 0;                  /* the number to factorise */
    u64 factors[MAX_FACTORS];   /* array of factors */
    int count;                  /* count of factors */

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
        printf("Invalid input: %llu\n", n);
        print_help_and_die(1);
    }

    if (is_prime(n)) {
        printf("The number %llu is prime!\n", n);
        print_help_and_die(0);
    }

    /* get factors */
    factorise(n, factors, &count);

    qsort(factors, count, sizeof(u64), comp);

    if (count > 0) {
        u64 current = factors[0];
        int power = 1;

        for (int i = 1; i < count; i++) {
            if (factors[i] == current) {
                power++;
            }
            else {
                printf("%llu^%d ", current, power);
                current = factors[i];
                power = 1;
            }
        }
        printf("%llu^%d", current, power);
    }

    return 0;
}

/*
 * function: comp
 * --------------
 * compare two numbers for the qsort function
 *
*/
int comp(const void *a, const void *b) {
    return (*(u64 *)a - *(u64 *)b);
}

/*
 * function: factorise
 * -------------------
 * given an integer find two factors
 * and repeat on those factors
 * until prime
 *
*/
void factorise(u64 n, u64 *factors, int *c)
{
    if (n <= 1) return;

    if (is_prime(n)) {
        if (*c < MAX_FACTORS) {
            factors[*c] = n;
            (*c)++;
        }
        return;
    }

    u64 f1 = 1, f2 = 1;

    if (n % 2 == 0) {
        halve(n, &f1, &f2);
    }
    else {
        fermat(n, &f1, &f2);
    }

    factorise(f1, factors, c);
    factorise(f2, factors, c);
}

/*
 * function: fermat
 * ----------------
 * uses naive form of fermat's difference of squares factorisation
 * on an odd, composite integer
 *
 *  ref:
 *  https://cp-algorithms.com/algebra/factorization.html
 *
 */
void fermat(u64 n, u64 *f1, u64 *f2)
{
    u64 a = ceil(sqrt(n));
    u64 b2 = a*a - n;
    u64 b = round(sqrt(b2));
    
    while (b * b != b2) {
        a += 1;
        b2 = a*a - n;
        b = round(sqrt(b2));
    }

   // two factors:
    *f1 = a - b;
    *f2 = a + b;
}

/*
 * function: havle
 * ---------------
 * given an even number
 * processes two factors: 2 and half the number
 * assumes the input is even.
 * 
*/
void halve(u64 n, u64 *f1, u64 *f2) {
    *f1 = 2;
    *f2 = n/2;
}

/*
 * function: is_prime
 * ------------------
 *  a basic primality test
 *  checking possible divisors
 * which returns a boolean
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
