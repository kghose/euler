#|
Large sum
Problem 13
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
|#

#lang racket
(require math)
(require rackunit)

;; Given a file, load rows x cols digits from it
; in -> port (file)
; rows, cols -> size of matrix
; l (not needed by initial caller)
(define (load-matrix-from-file in [rows 100] [cols 50] [l `()])
  (define line (read-line in))
  (if (eof-object? line)
      (list->matrix rows cols l)
      (load-matrix-from-file in rows cols
                             (append l (map string->number
                                            (remove* `("") (string-split line "")))))))


(test-case "load-matrix"
           (define mat (load-matrix-from-file (open-input-file "p13_data.txt")))
           (check-equal? (matrix-ref mat 0 0) 3)
           (check-equal? (matrix-ref mat 0 49) 0)
           (check-equal? (matrix-ref mat 99 0) 5)
           (check-equal? (matrix-ref mat 99 49) 0)
           )


; Given a number d give us a list of it's digits in lsd first order
(define (extract-digits d [l `()])
  (let-values ([(q r) (quotient/remainder d 10)])
    (match q
      [0 (append l (if (> r 0) (list r) `()))]
      [_ (extract-digits q (append l (list r)))])))

(test-case "extract digits"
           (check-equal? (extract-digits 0) `())
           (check-equal? (extract-digits 1) `(1))
           (check-equal? (extract-digits 10) `(0 1))
           (check-equal? (extract-digits 103) `(3 0 1))
           (check-equal? (extract-digits 1000) `(0 0 0 1))
           )


; Given the sums of columns of a matrix of digits (starting from lsd) recurse through them
; building a list of digits (lsd first) and apropriately taking the carry
(define (digits-r column-sums-r [carry 0] [l `()])
  (match column-sums-r
    [`() (append l (extract-digits carry))]
    [_ (let-values ([(q r) (quotient/remainder (+ (car column-sums-r) carry) 10)])
         (digits-r (cdr column-sums-r) q (append l (list r))) )]))
    
(test-case "digits from column sums"
           (check-equal? (digits-r `(1)) `(1))
           (check-equal? (digits-r `(10)) `(0 1))
           (check-equal? (digits-r `(13)) `(3 1))
           (check-equal? (digits-r `(10 32)) `(0 3 3))
           (check-equal? (digits-r `(5 23) 5) `(0 4 2))           
           )

(display (reverse (digits-r (reverse (array->list (array-axis-sum (load-matrix-from-file (open-input-file "p13_data.txt")) 0))))))

; 5537376230
; 5 5 3 7 3 7 6 2 3 0 3 9 0 8 7 6 6 3 7 3 0 2 0 4 8 7 4 6 8 3 2 9 8 5 9 7 1 7 7 3 6 5 9 8 3 1 8 9 2 6 7 2