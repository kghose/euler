#|
10001st prime
Problem 7
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10001st prime number?

Since we have to generate a lot of primes I'm going to use the trusty trial division method, but make
it a bit more effecient



|#
#lang racket
(require rackunit)
(require racket/trace)

;; Test a number n for primality given a list of primes (l) upto n. l-max is (sqrt n)
(define (prime? n l l-max)
  (match l
    ['() #t]
    [_ (if (<= (car l) l-max)
         (if (= 0 (remainder n (car l))) #f (prime? n (cdr l) l-max))
         #t)]))
  
(test-case "Primality"
           (check-eq? (prime? 13 `(2 3 5 7 11) 4) #t)
           (check-eq? (prime? 14 `(2 3 5 7 11 13) 4) #f)
           (check-eq? (prime? 15 `(2 3 5 7 11 13) 4) #f)
           (check-eq? (prime? 16 `(2 3 5 7 11 13) 4) #f)
           (check-eq? (prime? 17 `(2 3 5 7 11 13) 5) #t))

(define (nth-prime n [m 5] [l `(2 3)] [cnt 2])
  (if (< cnt n)
      (if (prime? m l (ceiling (sqrt m)))
          (nth-prime n (+ m 2) (append l (list m)) (+ cnt 1))
          (nth-prime n (+ m 2) l cnt))
      (last l)))

(test-case "n-th prime"
           (check-eq? (nth-prime 2) 3)
           (check-eq? (nth-prime 3) 5)
           (check-eq? (nth-prime 6) 13))

(time (nth-prime 10001)) ; -> cpu time: 588 real time: 588 gc time: 127