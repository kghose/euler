#|
Problem 14
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers
finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.

|#

#lang racket
(require rackunit)

#| Just a warm up |#
;; Given a number n use recurse to forward generate the Collatz sequence
(define (generate-collatz n [l `()])
  (match n
    [1 (append l `(1))]
    [_ (if (even? n)
           (generate-collatz (/ n 2) (append l (list n)))
           (generate-collatz (+ (* 3 n) 1) (append l (list n))) )]))


#|
Algorithm: We use reverse recursion: we pass in the number we are testing and recurse down the
children. I have not tested this implementation for correctness because it quickly runs out of
memory - even for n-max as low as 15 - and I abandoned it
|#

; Seemed much more sensible to have a struct for this
(struct node (depth number parent) #:inspector #f)

; A terminating conditon is if the node is 1 or the node is illegal or out o 
(define (end-node? p-node)
  (or (< (node-number p-node) 1) (and (= (node-number p-node) 1) (> (node-depth p-node) 1))))

(define (end-node parent)
  (node -1 -1 parent))

; Return the node with greater depth
(define (deeper-node node1 node2)
  (if (or (end-node? node2) (> (node-depth node1) (node-depth node2)))
      (struct-copy node node1)
      (struct-copy node node2)))

; The two child nodes
(define (odd-child p-node)
  (define odd-p (/ (- (node-number p-node) 1) 3))
  (if (integer? odd-p) (node (+ (node-depth p-node) 1) odd-p p-node) (end-node p-node)))

(define (even-child p-node n-max)
  (define even-p (* (node-number p-node) 2))
  (if (<= (node-number p-node) n-max) (node (+ (node-depth p-node) 1) even-p p-node) (end-node p-node)))
  
  
;; Use a backward search tree, starting from 1, to recreate possible start sequences. Use DFS.
;; Terminate a branch if the number goes above n_max.  Keep track of the number that has given us the
;; longest depth so far
(define (rev-traverse-collatz p-node [n-max 100])
  ;; (display p-node)
  (if (end-node? p-node)
      (node-parent p-node)
      (deeper-node (rev-traverse-collatz (odd-child p-node) n-max)
               (rev-traverse-collatz (even-child p-node n-max) n-max))))


;; (rev-traverse-collatz (node 1 1 0) 15)


#|
Algorithm: Generate the forward sequence. Keep a set* of all the numbers visited during the traverse.
If at any point in the traverse we visit a number we have previously seen, use past information to
infer the length of the rest of the sequence, there by saving compute time.
*OK, it's a hash
|#

;; Given a number n use recursion to forward generate the Collatz sequence and return it's length
; If we run into an already computed number, use that to skip the calculations
; The depths in the hash table have to be one less than the length
(define (length-collatz n [h (hash)] [depth 1])
  (match n
    [1 depth]
    [(? (lambda (x) (hash-ref h x #f))) (+ depth (hash-ref h n))]
    [_ (if (even? n)
           (length-collatz (/ n 2) h (+ depth 1))
           (length-collatz (+ (* 3 n) 1) h (+ depth 1)) )]))

(test-case "generate"
           (check-equal? (length-collatz 10) 7)
           (check-equal? (length-collatz 1) 1)
           (check-equal? (length-collatz 5) 6)
           )

(test-case "generate with hash"
           (define h (hash 10 6 5 5))
           (check-equal? (length-collatz 10 h) 7)
           (check-equal? (length-collatz 1 h) 1)
           (check-equal? (length-collatz 5 h) 6)
           (check-equal? (length-collatz 16 h) 5)
           )

(define (search-collatz n [max-n 100] [h (hash)] [depth-max 0] [n-max 0])
  (if (>= n max-n)
      (values n-max depth-max)
      (search-collatz2 n max-n h depth-max n-max)))

(define (search-collatz2 n max-n h depth-max n-max)
  (define depth (length-collatz n h))
  (define new-h (hash-set h n (- depth 1)))  ; In the hash table the length has to be 1 less
  (let-values ([(new-depth-max new-n-max) (if (> depth depth-max)
                                              (values depth n)
                                              (values depth-max n-max))])
    (search-collatz (+ n 1) max-n new-h new-depth-max new-n-max))) 

(search-collatz 2 1000000)