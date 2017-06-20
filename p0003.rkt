; The prime factors of 13195 are 5, 7, 13 and 29.
; What is the largest prime factor of the number 600851475143 ?

#lang racket
(require rackunit)

; We use simple trial division to create our list of primes.

; Test if a given number is divisible by any one of a list of given numbers
; Return the first number if divisible or return 0
; This function makes a lot of sense if the list of numbers is a consecutive list of primes
; We choose to return the perfect divisor as this will then help us in the second part of the problem
(define (div? n l)
  (match l
    [`() 0]
    [_ (if (= 0 (remainder n (car l))) (car l) (div? n (cdr l)))]))

(test-case "Division"
           (check-eq? (div? 10 `(2 3 5)) 2)
           (check-eq? (div? 15 `(2 3 5)) 3))

(define (is-prime n m lp)
  (define lp+1 (append lp (list n)))
  (append (list n) (recurse-prime (+ n 1) m lp+1)))

(define (is-not-prime n m lp)
  (recurse-prime (+ n 1) m lp))

; Return a list of primes <= m
; lp is a list of primes < n
(define (recurse-prime n m lp)
  (if (> n m) `() (if (= (div? n lp) 0) (is-prime n m lp) (is-not-prime n m lp)) ))

; Generate a list of primes up to and including m
; Wrapper around p-str
(define (primes m)
  (recurse-prime 2 m `()))

(test-case "Primes"
           (check-equal? (primes 10) `(2 3 5 7))
           (check-equal? (primes 13) `(2 3 5 7 11 13)))

(define N 600851475143)
(time (div? N (reverse (primes (sqrt N))))) ; -> 6857 cpu time: 59392 real time: 59447 gc time: 14832
