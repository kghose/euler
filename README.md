Project Euler problems
----------------------

![](https://projecteuler.net/profile/kghose.png)


Just me working through the [project Euler] problems. I often try out different
languages and paradigms as I go so the code reflects that. It reflects a short
flirtation with functional programming (programs in racket and Haskell), a short
foray into Common Lisp and then a regression back to C++. There are rarely any
Python programs as I use that extensively during the day.


[Project Euler]:https://projecteuler.net/


Interesting algorithms/implementations
--------------------------------------
- `p0024.cpp` - "forward backward" algorithm for generating permutations
  `p0024.recursive.cpp` - implemented as a recursive calls. 
                        Trades off readability and elegance for speed and memory
  also `p0032.cpp`


Notes on the problems
---------------------
- p34 Interesting that there are only two such numbers ever: 145 and 40585




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



C++
---

All code can be compiled with `g++ --std=c++14 pXXXX.cpp -o current`


### [`const` member function](https://stackoverflow.com/a/21492333/2512851)

`p0032.cpp`, `p0034.cpp`

> To be able to call a function on a const object, you need to promise the compiler that the function will not modify the object. To do that, you mark the function with the keyword const after its argument list.

