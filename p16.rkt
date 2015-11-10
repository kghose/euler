#|
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
|#
#lang racket
(require rackunit)

;; Given a list of digits of a number (lsd first) multiply by two and
;; return the list of digits (lsd first)
; d0 - original digits
; carry - any carry
; d1 new list of digits being built
(define (digits*2 d0 [carry 0] [d1 `()])
  (match d0
    [`() (if (> carry 0) (append d1 (list carry)) d1)]
    [_ (let-values ([(q r) (quotient/remainder (+ (* 2 (first d0)) carry) 10)])
         (digits*2 (rest d0) q (append d1 (list r))) )]))

(test-case "Multiply by 2"
           (check-equal? (digits*2 `(1)) `(2))
           (check-equal? (digits*2 `(8)) `(6 1))
           (check-equal? (digits*2 `(4 2 0 1)) `(8 4 0 2))
           (check-equal? (digits*2 `(8 4 0 2)) `(6 9 0 4))           
           (check-equal? (digits*2 `(4 8 3 6 1)) `(8 6 7 2 3))           
           )

;; Given a power n, return a list of the digits (lsd first) of 2 ^ n
(define (power-2 n [d0 `(1)])
  (match n
    [0 d0]
    [_ (power-2 (- n 1) (digits*2 d0))]))

(test-case "Digits of power of 2"
           (check-equal? (power-2 10) `(4 2 0 1))
           (check-equal? (power-2 15) `(8 6 7 2 3))           
           )

(time (let ([k (apply + (power-2 1000))]) (display k)))
;-> 1366 cpu time: 335 real time: 340 gc time: 156