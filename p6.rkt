#|
Euler problem 6.

The sum of the squares of the first ten natural numbers is,
1^2 + 2^2 + ... + 10^2 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)^2 = 552 = 3025

Hence the difference between the sum of the squares of the first ten natural numbers and the square
of the sum is 3025 - 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the
square of the sum.

I used this as an excuse to use stream-fold
|#

#lang racket
(define (square x)
  (* x x))

(- (square (stream-fold + 0 (in-range 1 101))) (stream-fold + 0 (stream-map square (in-range 1 101))))