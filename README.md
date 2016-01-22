Project Euler problems
----------------------

Just me working through the project Euler problems, learning functional programming on the way. I started out with Racket and when I got to problem 20, I decided to try my hand at Haskell. So, 



Racket concepts and the files in which they are implemented
-----------------------------------------------------------

### Default values
`(define (foo [x 1] [y 2]) ...` eg.  p5.rkt


### Structures
freecell.rkt, p15.rkt

### Fixtures for tests
Not completely fixtures, but you can put `defines` inside a `test-case` so that you
can set up data structures and then operate on them. e.g: p13.rkt

### Reading files
`open-input-file`
`read-line`
`string-split`

e.g. p11.rkt
   
### Sum of row/column of a matrix
`array-axis-sum` e.g. p13.rkt

### Accessing multiple values returned from a function
See http://stackoverflow.com/questions/20556746/how-do-i-do-anything-with-multiple-return-values-in-racket/20556950#20556950

Use `let-values`. See p13.rkt, algorithms/merge_sort.rkt

### Conditional blocks
Use `cond`. see algorithms/sort_algorithms.rkt, p15.rkt


### Timing code
Use `(time ...)` e.g. p12.rkt p15.rkt


### Memoization
Use the `memoize` package. e.g. p15.rkt


Haskell concepts and the files in which they are implemented
------------------------------------------------------------

### File I/O
(From an introduction [here][haskio])

[haskio]: https://wiki.haskell.org/Tutorials/Programming_Haskell/String_IO

