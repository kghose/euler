#|
Euler P18 (also works for P67)
(I found P17 boring, so I skipped to p18)
By starting at the top of the triangle below and moving to adjacent numbers on the row below,
the maximum total from top to bottom is 23.

3
7 4
2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

(We need to right shift each row, so it looks more like a binary tree)

Let's set up some nomenclature. Let n_l be the set of nodes at level l of the
tree. Let v_l be the set of value of these nodes. Let m_l be the set of values
of the larger child of every node.

We can't use a top-down greedy algorithm for this.
If you sit at an arbitrary node - even if you are given that it is the
optimum solution upto this point, there is no gurantee that this node
is part of the global optimum path.

However, if you consider every node at level l (n_l), you can tell which
would be the optimum path choice at each node (left or right) given the nodes
at level l+1, (n_(l+1)). Let the sum of the value of the


By indicating the sum value of the optimum choice at each node we can
proceed upwards on the tree, and finally end up with the value of the
optimum path. With a juidcious storage system we could also note the
optimum path, but we don't need that here.

An easy way to achieve this is to store the tree as a series of lists,
one list for every level. We go through each list reducing it by one by
picking the larger of each pair of elements considered. We then add this
list element-wise to the list above, before repeating this process.

We should, simultaneously, end with one number and end at the last list
when this process is done

|#

#lang racket
(require rackunit)

;; Load the tree from file as a list of lists
; in-file -> open input file
; l -> current list of lists (used internally)
(define (load-tree in-file [l `()])
  (define line (read-line in-file))
  (if (eof-object? line)
      l
      (load-tree in-file (append l (list (map string->number (string-split line)))))))

(test-case "File load"
           (check-equal? (load-tree (open-input-file "p18_data1.txt")) `((3) (7 4) (2 4 6) (8 5 9 3))))


;; Given a list, create another list from the maximum of adjacent pairs
; l -> list of numbers
(define (adjacent-pair-max l)
  (cond
    [(= (length l) 1) l]
    [(= (length l) 2) (list (max (first l) (second l)))]
    [else (append (list (max (first l) (second l))) (adjacent-pair-max (rest l)))]))

(test-case "List pair max"
           (check-equal? (adjacent-pair-max `(4)) `(4))
           (check-equal? (adjacent-pair-max `(4 1 10 3)) `(4 10 10))
           (check-equal? (adjacent-pair-max `(10 9 8)) `(10 9)))


;; Add two equal length lists together
(define (list-sum l1 l2)
  (match l1
    [`() `()]
    [_ (append (list (+ (first l1) (first l2))) (list-sum (rest l1) (rest l2)))]))

(test-case "List sum"
           (check-equal? (list-sum `(1 2 3) `(3 2 1)) `(4 4 4)))


;; Tree is represented as a list of lists, starting with the root
;; For each level of the tree, we find the adjacent-pair-max, add it to
;; the level above and keep collapsing the tree until we end up at the root
(define (max-traverse tree)
  (cond
    [(= (length tree) 1) (adjacent-pair-max (first tree))] ;; leaves
    [else (adjacent-pair-max (list-sum (first tree) (max-traverse (rest tree))))]))

(test-case "Tree traverse"
           (check-equal? (max-traverse `((1))) `(1))
           (check-equal? (max-traverse `((1) (2 3))) `(4))
           (check-equal? (max-traverse `((1) (2 3) (4 5 6))) `(10))
           (check-equal? (max-traverse `((3) (7 4) (2 4 6) (8 5 9 3))) `(23)))


(time (let ([k (max-traverse (load-tree (open-input-file "p18_data2.txt")))]) (display k)))
(let ([tree (load-tree (open-input-file "p18_data2.txt"))])
  (time (let ([k (max-traverse tree)]) (display k))))

(let ([tree (load-tree (open-input-file "p067_triangle.txt"))])
  (time (let ([k (max-traverse tree)]) (display k))))
