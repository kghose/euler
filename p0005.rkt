#|
  2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any
  remainder.
 
  What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 
  This one was funny because I first worked it out by hand. Since the number has to be evenly
  divisible and by 20, the number, N, takes the form of 20 * 2n (were n is a positive integer)
  so N = 2 x 2 x 2 x 5 x n
  Now, we just go down the list of numbers from 1 to 20 and see what are the numbers we MUST include
  in the product to work.
 
   2  - in list
   3  * need this
   4  - in list
   5  - in list
   6  - in list (2 x 3)
   7  * need this
   8  - in list (2 x 2 x 2)
   9  * need another 3 (3 x 3)
  10  - in list
  11  * need this
  12  - in list (2 x 2 x 2 x 3)
  13  * need this
  14  - in list (2 x 7)
  15  - in list (3 x 5)
  16  * need another 2 (2 x 2 x 2 x 2)
  17  * need this
  18  - in list (2 x 3 x 3)
  19  * need this
  20  - in list
 
  So we are now:
 
  N = 2 x 2 x 2 x 5 x 3 x 7 x 3 x 11 x 13 x 2 x 17 x 19 = 232792560
 
  For the code, I decided to do a simple brute force search of all n
 
|#
#lang racket

; Test if a given number is divisible by each of a list of given numbers
; Return #t if so, #f otherwise
(define (each-div? n l)
  (match l
    [`() #t]
    [_ (if (> (remainder n (car l)) 0) #f (each-div? n (cdr l)))]))


(define (p-5 [n 1] [l `(7 9 11 13 16 17 18 19)])
  (if (each-div? (* 40 n) l) (* 40 n) (p-5 (+ n 1) l)))

(time (p-5))