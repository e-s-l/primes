#include <limits.h>
#include <stdio.h>

/*
 * prints maximum number and the number of digits of this.
 * ```
 * cat $(echo '#include <limits.h>' | gcc -H -E - 2>&1 | head -n 1 | awk '{ print $NF }')
 * ```
 */

void print_digit_count(long long int n);
unsigned long long int count_digits(unsigned long long int n);

int main()
{
    printf("%*s\n", 12, "---");
    /* signed ints */
    printf("The value of INT_MIN: %d\n", INT_MIN);
    printf("Number of bits: %zu\n", sizeof(int)*CHAR_BIT);
    print_digit_count(INT_MIN);

    printf("The value of INT_MAX: %d\n", INT_MAX);
    print_digit_count(INT_MAX);

    /* unsigned ints */
    printf("The value of UINT_MAX: %u\n", UINT_MAX);
    printf("Number of bits: %zu\n", sizeof(unsigned int)*CHAR_BIT);
    print_digit_count(UINT_MAX);

    printf("%*s\n", 12, "---");
    /* signed longs */
    printf("The value of LONG_MIN: %ld\n", LONG_MIN);
    printf("Number of bits: %zu\n", sizeof(long)*CHAR_BIT);
    print_digit_count(LONG_MIN);

    printf("The value of LONG_MAX: %ld\n", LONG_MAX);
    print_digit_count(LONG_MAX);

    /* unsigned longs */
    printf("The value of ULONG_MAX: %lu\n", ULONG_MAX);
    printf("Number of bits: %zu\n", sizeof(unsigned long)*CHAR_BIT);
    print_digit_count(ULONG_MAX);

    printf("%*s\n", 12, "---");
    /* signed long longs */
    printf("The value of LLONG_MIN: %lld\n", LLONG_MIN);
    printf("Number of bits: %zu\n", sizeof(long long)*CHAR_BIT);
    print_digit_count(LLONG_MIN);

    printf("The value of LLONG_MAX: %lld\n", LLONG_MAX);
    print_digit_count(LLONG_MAX);

    /* unsigned longs longs */
    printf("The value of ULLONG_MAX: %llu\n", ULLONG_MAX);
    printf("Number of bits: %zu\n", sizeof(unsigned long long)*CHAR_BIT);
    print_digit_count(ULLONG_MAX);

    printf("%*s\n", 12, "---");

    return 0;
}

void print_digit_count(long long int n)
{
    printf("Number of digits: %lld\n", count_digits(n));
}

unsigned long long int count_digits(unsigned long long int n)
{
    if (n < 0) return count_digits(-1*(n));
    if (n < 10) return 1;
    return (1 + count_digits(n/10));
}
