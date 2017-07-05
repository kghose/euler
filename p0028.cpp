/*

Number spiral diagonals
Problem 28 
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is 
formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

43 44 45 46 47 48 49 
42 21 22 23 24 25 26
41 20  7  8  9 10 27
40 19  6  1  2 11 28
39 18  5  4  3 12 29
38 17 16 15 14 13 30
37 36 35 34 33 32 31

- Top right hand corner is n ^ 2 where n is the side of the square 
  (because it's how many numbers are enclosed)

- From there we can surmise that the top left is n ^ 2 - n + 1
- Bottom left is n ^ 2 - 2 * n + 2
- Bottom right is n ^ 2 - 3 * n + 3

n is 1, 3, 5, ... 

generated from k = 1, 2, 3, ... (N + 1) / 2 
n = 2 * k - 1

The only trick is the first number (1) contributes 1 number, not 4 to the 
diagonal totals

*/
#include <iostream>


int main(int argc, char *argv[]) {
    int N = 1001, diagonal_sum = 1, n;
    for (int k = 2; k <= ( N + 1 ) / 2; k++) {
        n = 2 * k - 1;
        diagonal_sum += (n * n) + (n * n - n + 1) + (n * n - 2 * n + 2) + (n * n - 3 * n + 3);
    }
    std::cout << diagonal_sum << std::endl;
}


