# Prime Number Finder in FORTRAN

## About

How quick will it be?

## Note

OMP operative seems to slow down the operations. Maybe inappropriate place for it.

## Set-up

Compile using gfortran:
```
gfortran -O3 -march=native -mtune=native -funroll-loops -floop-block -fopenmp --free-form utilities.f90 prime_finder.f90
```

Run with:
```
time ./a.out
```

## Sources

https://www.baeldung.com/cs/prime-number-algorithms
