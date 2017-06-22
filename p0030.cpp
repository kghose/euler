/*

Digit fifth powers
Problem 30 
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

A rough bounds calculation

The largest sum we can generate for a D digit number is D * 9 ^ 5 (a number with D 9s)
The smallest D digit number is 10 ^ (D - 1). So we have the following table

D   10^(D-1)   D*9^5
1   1          59049
2   10         118098
3   100        177147
4   1000       236196
5   10000      295245
6   100000     354294 <-
7   1000000    413343
So the largest number where this operation is possible is less than 354294  (= 64497 incidentally). 

Also note that with D digits the smallest sum we can get is D (1,10, 100 etc.) so this does not rule
out anything 

Let's just do the brute force search ...
*/
#include <iostream>
#include <stdlib.h>


int sum_of_fifth_power_of_digits(int n) {
    int sum_of_digit_powers = 0;
    div_t dvres;
    dvres.quot = n;
    while( dvres.quot != 0) {
        dvres = div(dvres.quot, 10);
        sum_of_digit_powers += dvres.rem * dvres.rem * dvres.rem * dvres.rem * dvres.rem;
    }
    return sum_of_digit_powers;
}


int main(int argc, char *argv[]) {
    int sum = 0;
    for(int i = 10; i < 354294; i++) {
        if (i == sum_of_fifth_power_of_digits(i)) {
            std::cout << i << std::endl;
            sum += i;
        }
    }
    std::cout << "Sum is " << sum << std::endl;
}


