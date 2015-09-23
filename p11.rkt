#|
Largest product in a grid
Given a grid of 20 x 20 numbers whats the largest product of 4 consecutive numbers in horizontal
vertical or diagonal configurations?

This wasn't that much fun the way I solved it. It was an exercise in learning how to do I/O in Racket
and Racket's Array data structure (which has mutability)
|#
#lang racket
(require math)

; in -> port (file)
; rows, cols -> size of matrix
; l (not needed by initial caller)
; We could automatically figure out rows and columns, but the code becomes more ugly
(define (load-matrix-from-file in rows cols [l `()])
  (define line (read-line in))
  (if (eof-object? line)
      (list->matrix rows cols l)
      (load-matrix-from-file in rows cols (append l (map string->number (string-split line))))))

; Maximum product in sub array
(define (recurse-mat mat [start-row 0] [start-col 0] [current-max 0])
  (if (= start-row -1) ; This means we are done with the matrix
      current-max
      (recurse-mat mat (next-row start-row start-col) (next-col start-row start-col)
                   (max current-max (max-prod-sub-array mat start-row start-col)))))

; We've hard coded the size
(define (next-row start-row start-col)
  (if (< start-col 16)
      start-row
      (if (> (+ start-row 1) 16)
          -1
          (+ start-row 1))))

(define (next-col start-row start-col)
  (if (< start-col 16)
      (+ start-col 1)
      0))

; Find the maximum from a 4x4 sub array of mat with start-row and start-col as top left
(define (max-prod-sub-array mat start-row start-col)
  (define s (submatrix mat (:: start-row (+ start-row 4)) (:: start-col (+ start-col 4))))
  (max (h-prod s 0) (h-prod s 1) (h-prod s 2) (h-prod s 3)
       (v-prod s 0) (v-prod s 1) (v-prod s 2) (v-prod s 3)
       (diag-prod s) (rev-diag-prod s)))
  
; Horizontal product
(define (h-prod s offset)
  (for/product ([y (matrix->list (matrix-row s offset))]) y))

; Vertical product
(define (v-prod s offset)
  (for/product ([y (matrix->list (matrix-col s offset))]) y))

; Diagonal product
(define (diag-prod s)  
  (for/product ([i `(0 1 2 3)] [j `(0 1 2 3)]) (matrix-ref s i j)))

(define (rev-diag-prod s)  
  (for/product ([i `(0 1 2 3)] [j `(3 2 1 0)]) (matrix-ref s i j)))

; (define x (load-matrix-from-file (open-input-file "p11_data.txt") 20 20))

(time (let ([max-prod (recurse-mat (load-matrix-from-file (open-input-file "p11_data.txt") 20 20))])
        max-prod)) ; -> cpu time: 1345 real time: 1435 gc time: 263
