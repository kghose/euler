# P828: Number's challenge

https://projecteuler.net/problem=828

## Brute force solving


```
make tests_main && ./tests_main
```

Given a list of numbers, and a target

1. Sort them in ascending order 
1. Start with the fewest, smallest numbers
1. Look for an expression that resolves to the target until all combinations and
   numbers are exhausted

## Constructing expressions

1. Each expression is a binary tree.
1. Each node is an operation (+,-,/,* )
1. Each child is either a leaf node (an integer) or another expression
1. Expressions with + and * are symmetric e.g. a + b = b + a

## Implementation

Given n operands we have n-1 nodes (operations). 

Generate binary trees using recursion. Pick a node, each child can be either a
leaf or another node. Do this until leaves and nodes are exhausted. Only complete
trees are accepted (i.e. all leaves and nodes must exhaust at the same time)


1. The shape of the expression is given by a binary tree 
1. For a given shape, we can have many expressions by permuting the operators
   and the operands





So
1. For a given list of operators, and operands
1. Pick a subset of operands
1. Construct the different expression shapes
1. Permute the operations and the operands until we find the target or have
   exhausted all permutations, then redo with a larger list


## How many combinations could we have?

Working backwards, the target is the result of two numbers with an operator in
between. Each of those numbers could, intern, be the result of two numbers with
and operator in between, or one of the original numbers.

We can pair the six numbers as

```
1. ((a,b),(c,d),(e,f))
2. (((a,b),c),((d,e),f))
3. ((((((a,b),c),d),e),f)
```

There are four operators, so we have

4 x 4 x 4 x 4 x 4 operators and then 6! ways of picking, so we have 4^5 * 6!
 combinations.

## Brute force generation of expressions

We can explore the whole space for N numbers as follows:

1. For each node we can have
  1. lhs is leaf or node
  1. rhs is lead or node
  1. Except for + and * we generate an extra combination by swapping lhs and rhs
1. Once a tree has exactly N leaves, it is complete
1. Once we have a complete tree we now assign numbers to the leaves. We can do
   this in N! ways. 


## C++ learning notes

1. Visitor pattern (lib.h)
1. [doctest](https://github.com/doctest/doctest) framework for tests.


## Appendix: Binary tree leaves and nodes

A binary tree with N leaves has N-1 nodes.
We have two basic structures: 

A node and two leaves
```
  o
 / \
.   .
```

A node, one leaf and another node
``o`
 / \
o   .
```
This latter pattern either ends in two leaves or one node and a leaf.

In either case we end up with n leaves and n-1 nodes. 

If we now attach either of these
peripheral structures to a parent node we end up with 2n leaves and 2(n-1) + 1
nodes = 2n - 1, and so on, proved by induction. 

## Appendix: Binary tree combinations




