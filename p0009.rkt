#|
Special Pythagorean triplet
Problem 9
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a2 + b2 = c2
For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.

I got lazy and did a simple brute force search. The only special thing I did was translate the
constraints into the search space so that I'm searching only about a quarter of a million numbers
|#
#lang racket

; If a^2 + b^2 a perfect square return c = sqrt(a^2 + b^2) else return 0
(define (pythagorean-triplet a b)
  (define c (sqrt (+ (* a a) (* b b))))
  (if (= c (floor c)) c 0))

; Return #t if this satisfies a + b + c = 1000 and is a pythagorean triplet
(define (is-triplet? a b)
  (define c (pythagorean-triplet a b))
  (if (> c 0) (if (= (+ a b c) 1000) #t #f) #f))

; Rules for advancing indexes in our recursion
(define (next-a a b) (if (< b (- 998 a)) a (+ a 1)))  
(define (next-b a b) (if (< b (- 998 a)) (+ b 1) (+ a 1)))

; this has no termination condition. We are relying on the fact that this solution exists for
; termination
(define (find-triplet [a 1] [b 2])
  (if (is-triplet? a b) (list a b (pythagorean-triplet a b)) (find-triplet (next-a a b) (next-b a b))))

(time (find-triplet))) ; -> cpu time: 39 real time: 39 gc time: 18