# p37: Truncatable primes.

## Iteration 1: Complete brute force

[Code](0.brute_force/main.go)

We use an inelegant brute force method combined with the information given that
there are eleven such primes.

We use a [precomputed list of primes](../primes_100M.txt.gz) taken from [here]
(https://github.com/srmalins/primelists)

1. Start with two digit primes.
1. For each number, remove digits from the left. If the remaining number is not
   a prime, move to the next number
1. For each number, remove digits from the right. If the remaining number is not
   prime (i.e. in the list), move to the next number.

Our run gets us:

```
Loaded 5761455 primes
23
37
53
73
313
317
373
797
3137
3797
739397
```




## Random thoughts ...

Properties

Say number is

Dn-1 .... D3 D2 D1 D0
 |                  |____ first digit
 |
 |_______________________ last digit


1. The number must be prime
1. The number must begin and end in 3,5 or 7 since we want to truncate it both directions. 
1. But a number ending in 5 isn't prime, so it can begin with 3,5,7 but must end in 3 or 7


D1 D0 has to be prime (and Dn-1 Dn-2 has to be prime too)

So D1 D0 have to be one of

13
17
23
37
43
47
53
67
73
83
97


Ideas:

1. Can we grow the number from a stable of primes?
