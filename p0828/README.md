# P828: Number's challenge

https://projecteuler.net/problem=828


## How many combinations could we have?

Working backwards, the target is the result of two numbers with an operator in
between. Each of those numbers could, intern, be the result of two numbers with
and operator in between, or one of the original numbers.

We can pair the six numbers as

```
1. ((a,b),(c,d),(e,f))
2. (((a,b),c),((d,e),f))
3. ((((((a,b),c),d),e),f)
```

There are four operators, so we have

4 x 4 x 4 x 4 x 4 operators and then 6! ways of picking, so we have 4^5 * 6!
 combinations.

# C++ learning notes

1. Visitor pattern (lib.h)
1. [doctest](https://github.com/doctest/doctest) framework for tests.
