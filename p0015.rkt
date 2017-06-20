#|
Euler problem 15
Lattice paths.

Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down,
there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?

My first instinct was to use a depth-first tree search through all possible moves. 
|#
#lang racket
(require rackunit)

; A location on the grid
(struct pos (x y) #:inspector #f)

;; The two legal moves
(define (move-right p0)
  (struct-copy pos p0 [x (+ (pos-x p0) 1)])) 

(define (move-down p0)
  (struct-copy pos p0 [y (+ (pos-y p0) 1)])) 

;; Two terminations for a path
(define (exit-pos p0 grid-size)
  (if (and (= (pos-x grid-size) (pos-x p0)) (= (pos-y grid-size) (pos-y p0))) #t #f))

(define (off-grid p0 grid-size)
  (if (or (> (pos-x p0) (pos-x grid-size)) (> (pos-y p0) (pos-y grid-size))) #t #f))


;; Use recursion to explore all possible moves.
;; Return 1 if we reach the bottom right corner of the grid, 0 if we fall off the grid
; p0 - initial position (pos struct)
; grid-size - size of grid (pos struct)
(define (count-paths grid-size [p0 (pos 0 0)])
  (cond
    [(exit-pos p0 grid-size) 1]
    [(off-grid p0 grid-size) 0]
    [(+ (count-paths grid-size (move-right p0)) (count-paths grid-size (move-down p0)))])) 

(test-case "Recursive"
           (check-equal? (count-paths (pos 2 2)) 6)
           (check-equal? (count-paths (pos 1 3)) 4)
           )

(time (let ([k (count-paths (pos 10 10))]) (display k)))


#| As you can imagine this blows up pretty fast.
I let the 20x20 grid run for a few minitues and lost patience.
I realized that I could reduce the number of paths I needed to visit by noting when
I hit the grid boundary. Once I hit a boundary, there was really only one path from there on
- straight down, or straight right. Here is the modified code. This makes it faster,
but it's still the same order of complexity.
|#

(define (boundary-pos p0 grid-size)
  (if (or (= (pos-x grid-size) (pos-x p0)) (= (pos-y grid-size) (pos-y p0))) #t #f))


;; Use recursion to explore all possible moves, but prune search once we get to a boundary
;; we know what happens next
;; Return 1 when we reach a grid boundary 
; p0 - initial position (pos struct)
; grid-size - size of grid (pos struct)
(define (count-paths2 grid-size [p0 (pos 0 0)])
  (cond
    [(boundary-pos p0 grid-size) 1]
    [(+ (count-paths2 grid-size (move-right p0)) (count-paths2 grid-size (move-down p0)))])) 

(test-case "Recursive 2"
           (check-equal? (count-paths2 (pos 2 2)) 6)
           (check-equal? (count-paths2 (pos 1 3)) 4)
           )

(time (let ([k (count-paths2 (pos 10 10))]) (display k)))

#|
After that debacle, I tried a different tack. Say I knew how many paths (k) there were from
some node N. During my traversal, if I ended up at node N, I would not need to traverse
any further: the number of paths from there on is known - k. This would allow a top-down, dynamic
programming approach using Memoization
|#

(require memoize)

;; This memoizes (!) the elementary computation
;; The boards were guaranteed to be square, we could also cut computation in half by
;; noting that the problem is symmetric about the diagonal. But we skip that
(define/memo* (count-paths-m grid-size p0)
  (cond
    [(boundary-pos p0 grid-size) 1]
    [(+ (count-paths-m grid-size (move-right p0)) (count-paths-m grid-size (move-down p0)))])) 

(test-case "Memoize"
           (check-equal? (count-paths-m (pos 2 2) (pos 0 0)) 6)
           (check-equal? (count-paths-m (pos 1 3) (pos 0 0)) 4)
           )

; (time (let ([k (move-m (pos 10 10) (pos 0 0))]) (display k)))

(time (let ([k (count-paths-m (pos 20 20) (pos 0 0))]) (display k)))