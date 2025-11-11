# Stein's Algorithm a.k.a. Binary GCD Algorithm

another way of finding the gcd, better suited to binary operations.

Tests:
```
 echo "48 18" | ./a.out
 echo "192 270" | ./a.out
```
or
```
./a.out < test-input
```

## notes

when checking somethings here stumbled upon this method of converting between 
reprensentations using the command line
```
echo "obase=2; ibase=10; 20" | bc
```

## references

https://cp-algorithms.com/algebra/euclid-algorithm.html

https://medium.com/@m.langer798/stein-vs-stein-on-the-jvm-c911809bfce1

https://www.blackwasp.co.uk/steinsalgorithm.html
