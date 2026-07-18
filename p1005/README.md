# Problem 1005: Median Prime List

If the sum is P, the sets will contain primes less than P. 
Let the list of candidate primes be P0, P1, ...

One by one pick a prime from the list until the sum is either the target or
exceeds the target.

Doing this recursively, using the sorted list will yield the lists in
lexicographic order.

## Improving on the naive implementation

The naive recursive implementation runs out of memory. We are storing all the
lists of primes as `int` arrays.

There are two things we can do

1. Drop entries that are below the current median. This will halve our memory
   usage and will only work if the storage needs are right at the edge of what
   we have (16 GB on this laptop)
1. There are 307 primes under 2026. Instead of saving the actual list of primes as
   `[]int` we could save them as `[]int16`  

## C++ version

```
cmake -B build
cmake --build build
```

Build debug version
```

```


Get time and memory usage
```
/usr/bin/time -v ./build/main 200
```
