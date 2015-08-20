#lang racket
(define N 999)
(define (div-by-3-or-5? x)
  (or
   (if (= (remainder x 3) 0) #t #f)
   (if (= (remainder x 5) 0) #t #f) ))

(for/sum ([i (filter div-by-3-or-5? (build-list N add1))]) i)
