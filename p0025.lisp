#|
Project Euler: Problem 25

The Fibonacci sequence is defined by the recurrence relation:

Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
Hence the first 12 terms will be:

F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
The 12th term, F12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?


2016.08.24
----------

Brute force computation: represent a number as a list and run the fibonacci
calculations forward until you get a 1000 digit number



2016.08.24
----------

The largest carry you can get is 1
You will get a carry if sum of digits >= 10
You may get a carry if sum of digits = 9, depending on if you had a carry previously




2015.11.17
----------
Trying non brute force method. Starting with the idea of digit cascade: what are the conditions under which D(Fn) > max(D(Fn-1), D(Fn-2)) where D(x) is the number of digits in the number x. Also, is D(Fn) - max(D(Fn-1), D(Fn-2)) always less than 2?

Is D(.) equivalent to ceil(log10(.))? Yes it is, from the definition of log and our ten based numbering system. I don’t think this helps us, but it’s interesting.

Say
Fn-1 = 10^q.a(n-1, q) + 10^(q-1).a(n-1, q-1) + ... + a(n-1, 0)
Fn-2 = 10^p.a(n-2, p) + 10^(q-1).a(n-2, q-1) + ... + a(n-2, 0)

Then
Fn =

|#
(load "lisp-unit")
(use-package :lisp-unit)

(defun get-digit (x)
  (if x x 0)) ; Exploits the fact that '() = nil = false -> 0

(define-test test-get-digit
  (assert-equal (get-digit 9) 9)
  (assert-equal (get-digit '()) 0))

(defun long-add (x y &optional (carry 0) (z '()))
  ;; Given two numbers represented as lists, add them to return another list
  (cond
    ( (and (not x) (not y)) (append z (if (= carry 1) '(1) '())) )
    ( t
         (multiple-value-bind
          (q r) (floor (+ carry (get-digit (car x)) (get-digit (car y))) 10)
          (long-add (cdr x) (cdr y) q (append z (list r)))))))

(define-test test-long-add
  (assert-equal '() (long-add '() '()))
  (assert-equal '(1) (long-add '(1) '()))
  (assert-equal '(1) (long-add '() '(1)))
  (assert-equal '(2) (long-add '(1) '(1)))
  (assert-equal '(3) (long-add '(1) '(1) 1))
  (assert-equal '(0 0 0 0 1) (long-add '(9 9 9 9) '(1)))
  )

; Return us the term which first crosses k digits
(defun fib-digits (k &optional (fib-n-1 '(1)) (n-1 2) (fib-n-2 '(1)) (n-2 1))
  ; (print (length fib-n-1))
  (cond
    ((>= (length fib-n-1) k) n-1)
    (t (fib-digits k (long-add fib-n-1 fib-n-2) (+ n-1 1) fib-n-1 (+ n-2 1)))))

(define-test test-fib-digits
  (assert-equal 7 (fib-digits 2))
  (assert-equal 12 (fib-digits 3))
 )

(setq *print-failures* t)
(run-tests :all)

(print (fib-digits 1000))
