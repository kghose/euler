#|
Working through the Collatz sequence problem in project euler (P14) I got a hankering to plot the
sequence paths. The representation I chose renders paths like this:

value
 |                   __
 |     __           |  |
 |    |  |          |  |__
 |    |  |__        |
 |  __|     |_______|
 |_|           
 |              
---------------------------------
        sequence step

The basic algorithm is to compute the sequences for starting values n, where n = 2,3,4... We remember
the values we've previously seen and put them in a set so we can avoid computing paths already visited
|#

#lang racket
(require racket/block)

;; Given a number n use recurse to forward generate the Collatz sequence
(define (generate-collatz n [s (set)] [l `()])
  (if (set-member? s n)
      (values l s)
      (block
       (define new-s (set-add s n))
       (match n
         [1 (values (append l `(1)) new-s)]
         [_ (if (even? n)
                (generate-collatz (/ n 2) new-s (append l (list n)))
                (generate-collatz (+ (* 3 n) 1) new-s (append l (list n))) )]))))