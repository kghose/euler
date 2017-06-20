/*

    Non-abundant sums
    Problem 23 
    
    A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
    For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means 
    that 28 is a perfect number.

    A number n is called deficient if the sum of its proper divisors is less than n and it is called 
    abundant if this sum exceeds n.

    As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be 
    written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown 
    that all integers greater than 28123 can be written as the sum of two abundant numbers. However, 
    this upper limit cannot be reduced any further by analysis even though it is known that the 
    greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

    Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.


    Solution algorithm:

    This is a generative solution with no space problems, since the upper bound number (28123) is so low

    We use a memoized function to determine if a number is abundant or not
    We loop over a half-grid of numbers from 1 to 28123
    We only consider those pairs of numbers where both are abundant. We mark the sum as checked
    (we use a simple array for this)
    At the end, we then go through the array and include all numbers that don't have a check (as
    there are numbers which could not be expressed as the sum of two abundant numbers)

*/
#include <iostream>
#include <cassert>


// Find each proper divisor and sum up
int compute_abundance(int number) {
    int sum_of_proper_divisors = 0;
    for(int div = 1; div <= number / 2; div++) {
        if ( number % div == 0) {
            sum_of_proper_divisors += div;
        }
    }
    return sum_of_proper_divisors > number ? 1 : -1 ;
}

// Memoized function to check if a number is abundant
bool is_abundant(int number, int *memo) {
    if (memo[number] == 0) { // not computed yet
        memo[number] = compute_abundance(number); // -1 No, +1 Yes
    }
    return memo[number] == 1;
}


void tests() {
    int memo[28123] = {0};
    assert( is_abundant(12, memo) == true );
    assert( memo[28] == 0); // Tests memoization
    assert( is_abundant(28, memo) == false );
    assert( memo[28] == -1); // Tests memoization
    assert( is_abundant(28, memo) == false );  // Tests memoization
    
    std::cout << "Unit tests pass" << std::endl ;
}


int main(int argc, char *argv[]) {
    tests();

    int memo[28123] = {0};          // For the abundance memoization
    bool checked[28123] = {false};  // Have we checked this number already to see if
                                    // It's  
    for(int i = 1; i < 28123; i++) {     
        for(int j = 1; j < 28123 - i; j++) {
            if (is_abundant(i, memo) && is_abundant(j, memo))
                checked[i + j] = true;
        }
    }

    int abundant_sum = 0;
    for(int i = 1; i < 28123; i++)
        if (!checked[i])
            abundant_sum += i;

    std::cout << "Sum: " << abundant_sum << std::endl ;
}