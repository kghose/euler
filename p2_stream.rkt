#lang racket
(require test-engine/racket-tests)
(require racket/stream)
 
; A recursive definition of the Fibonacci sequence, giving us the mth number
; This is elegant and closely mirrors the mathematical definition, though computationally
; wasteful. 
(define (fib m)
  (match m
    [1 1]
    [2 1]
    [_ (+ (fib (- m 1)) (fib (- m 2)))]))

; I learned how to write tests in Racket!
(check-expect (fib 1) 1)
(check-expect (fib 2) 1)
(check-expect (fib 3) 2)
(check-expect (fib 6) 8)


; Proc to use for foldl to get running sum of only even items in a list/stream
; functional pattern match using ? operator. Nice!
(define (+even x n)
  (match n
    [(? even?) (+ x n)]
    [_         x]))


; A lazily evaluated stream of Fibonacci numbers
(define (str-fib-first n n-1) (+ n n-1))
(define (str-fib-rest n n-1 m)
  (define n+1 (str-fib-first n n-1))
  (if (< (str-fib-first n+1 n) m)
    (stream-cons (str-fib-first n+1 n) (str-fib-rest n+1 n m))
    empty-stream
  ))
(define (stream-fib m)
  (stream-cons (str-fib-first 0 1) (str-fib-rest 0 1 m))) 

(check-expect (stream->list (stream-fib 10)) `(1 1 2 3 5 8))


; Sum of the even Fibonacci numbers less than m
(define (fib-even-sum m)
  (stream-fold +even 0 (stream-fib m)))

(check-expect (fib-even-sum 10) 10)


(test)

; Project Euler's question
(time (fib-even-sum 4000000)) 

;(stream->list (stream-fib 10))
;(define s (stream-fib 4))
;(define s (stream-fib 8))
;(stream->list s)