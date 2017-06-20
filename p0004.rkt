; A palindromic number reads the same both ways. The largest palindrome made from the product
; of two 2-digit numbers is 9009 = 91 × 99.
;
; Find the largest palindrome made from the product of two 3-digit numbers.
;
; It's a little difficult to predict the order of the products of a pair of numbers. We'll just
; scan through the grid from the right hand corner. If we've already found a palindrome we compare
; the number to the current producuct and only check for palindromicity if the product is larger

#lang racket
(require rackunit)

; It would be nice if racket had a haskell like syntax for pattern matching functions
(define (palindrome? str-x i N)
  (if (< i (/ N 2))
      (if (eq? (string-ref str-x i) (string-ref str-x (- N i))) (palindrome? str-x (+ i 1) N) #f)
      #t))

(test-case "Pallindrome"
           (check-eq? (palindrome? "1221" 0 3) #t)
           (check-eq? (palindrome? "12321" 0 4) #t)
           (check-eq? (palindrome? "12331" 0 4) #f))

;; Convenient wrapper around palindrome?
(define (is-palindrome? x)
  (define n (number->string x))
  (palindrome? n 0 (- (string-length n) 1)))

;; Functions to move indecies
(define (next-i i j) (if (> j i) i (- i 1)))
(define (next-j i j) (if (> j i) (- j 1) 999))

;; This next number, is it a palindrome and is it larger than our current one?
(define (update-palindrome ij current-palindrome)
  (if (> ij current-palindrome)
      ; Potential larger palindrome, check and switch if it is
      (if (is-palindrome? ij) ij current-palindrome)
      current-palindrome))  ; keep the current one as it is larger

(test-case "Update Pallindrome"
           (check-eq? (update-palindrome 99 121) 121)
           (check-eq? (update-palindrome 121 99) 121)
           (check-eq? (update-palindrome 145 99) 99))

;; Find the largest palindrome as required in the question
(define (largest-palindrome [i 999] [j 999] [current-palindrome 0])
  (if (> i 99)
      (largest-palindrome (next-i i j) (next-j i j) (update-palindrome (* i j) current-palindrome)) ;
      current-palindrome)) ;

(time (largest-palindrome))