#|
Summation of primes
Problem 10
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
|#
#lang racket

(require rackunit)

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

(define (prime<n n [m 5] [l `(2 3)])
  (if (< m n)
      (if (prime? m l (ceiling (sqrt m)))
          (prime<n n (+ m 2) (append l (list m)))
          (prime<n n (+ m 2) l))
      (apply + l)))

(test-case "prime < n"
           (check-eq? (prime<n 10) 17))

(time (prime<n 2000000)) ; -> cpu time: 275008 real time: 275238 gc time: 175389

#|
Now, let's see if a sieve works more efficiently. We're going beyond pure functional
now by using vectors and mutability
|#

; Set up an empty sieve with 0 and 1 flagged as non-prime
(define (initialize-sieve n)
  (define v (make-vector n 1))
  (for ([i `(0 1)]) (vector-set! v i 0)) ; Unset 0 and 1 which are not prime
  v)

; Given a vector of size n set all odd multiples of m > m^2 to zero
(define (set-sieve v n m)
  (for ([i (in-range (* m m) n m)]) (vector-set! v i 0)))

(define (prime-sieve n)
  (define v (initialize-sieve n))
  (set-sieve v n 2)
  (for ([i (in-range 3 (sqrt n) 2)]) (set-sieve v n i))
  v)  

; Given a vector corresponding to a filled sieve, return a list of primes
(define (prime-list v)
  (for/list ([i (in-range 0 (vector-length v))] #:when (= (vector-ref v i) 1)) i))

(test-case "prime-vec"
           (check-equal? (prime-list (prime-sieve 20)) `(2 3 5 7 11 13 17 19)))

(define (sum-of-primes<n n)
  (foldl + 0 (prime-list (prime-sieve n))))

(test-case "prime-sum"
           (check-eq? (sum-of-primes<n 10) 17))

(time (sum-of-primes<n 2000000)) ; -> 106 real time: 106 gc time: 2
