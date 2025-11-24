# 961. Removing digits

The zeros are the key feature of this game, since the actual digit doesn't
matter for wins and losses.

e.g. you will win if, on your turn, the pattern is `X0` or `X` (`X` being 1-9)

Let us enumerate some starting positions and mark if they are winning or not

Digits | Pattern |Win/Lose | Sequence
-------|---------|---------|---------
1      | X       | W       |
2      | X0      | W       | X0   -> 0
2      | XY      | L       | XY   -> X
3      | XYZ     | W       | XYZ  -> XY -> X
3      | XY0     | W       | XY0  -> XY -> X
3      | X0Y     | W       | X0Y  -> XY -> X
4      | WXYZ    | L       | WXYZ -> XYZ ...
4      | XYZ0    | L       | XYZ0 -> XYZ 
...

We have a brute force way to enumerate if a pattern of D digits is a win for us:

1. Start with D=1 (which is trivial) 
1. Iterate through all the patterns. These are binary numbers with D digits, but
   without leading zeros. So they start with b1, b10, b100, b1000
1. For each pattern remove a digit and see if that lands us on a winning
   pattern. That number if then winnable.

This gives us the answer in terms of our patterns. We now have to find the
numbers each pattern represents which are less than N.

Say N = 100 then we see that our winning patterns are b1 and b10

b1 corresponds to 9 numbers
b10 also corresponds to 9 numbers, so the answer is 18

For N = 10^4 (10000) we have to search all the way up to b1111, which is 2^4 - 1

How intensive is this search? If N = 10^m then we need to search 2^m patterns.
That's O(N). 

Is there a way we can cut down the search space?

A pattern with no zeros (b1, b11, b111, ...) will only result in a win if D is
odd.

A pattern with a zero at the end and an odd number of digits will be a loss. If
we remove the zero, we hand our opponent an odd number of digits. If we remove
something else, our opponent will remove the zero and hand us back an even
number of digits.

