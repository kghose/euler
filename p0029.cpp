/*

Distinct powers
Problem 29 
Consider all integer combinations of a ^ b for 2 ≤ a ≤ 5 and 2 ≤ b ≤ 5:

2^2=4, 2^3=8, 2^4=16, 2^5=32
3^2=9, 3^3=27, 3^4=81, 3^5=243
4^2=16, 4^3=64, 4^4=256, 4^5=1024
5^2=25, 5^3=125, 5^4=625, 5^5=3125
If they are then placed in numerical order, with any repeats removed, we get the following sequence of 
15 distinct terms:

4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125

How many distinct terms are in the sequence generated by ab for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100?


Algorithm:

We can see that the brute force way will fail, because one of our elements is 100 ^ 100 which is
a rather large number.

What we want to figure out is how many of these (a, b) pairs are equivalent representations of each
other: a ^ b = c ^ d

The only way this equivalence can be met is if c is a power of a or vice versa:

c = a ^ k and kd = b assuming a < c

We can proceed as follows.

There are a total of 100 - 2 + 1 = 99 * 99 numbers to consider.
We arrange these in a 99 x 99 grid with rows representing a and columns b.

Consider the pair (i, j) compared to the pair (k, l) where i < k

First we establish if k is a power of i by repeated division.
Say k = i ^ m
We then check if m * l = j. If so, (k, l) is a double of (i, j) and we "blank out" the
grid point (k, l) (And no longer have to check it)

We repeat this for all pairs of grid points, starting from (2, 2) onwards.

*/
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <cassert>


/*
First we establish if k is a power of i by repeated division.
- divide k by i, keep quot and rem
- If there is a rem, not a power
- Keep doing until we are done

    @param i
    @param k
    @returns -1 if not a power, power otherwise
*/
int power_of(int i, int k) {
    int power = 0;
    div_t dvres = div(k, i);
    for (;;) {
        power++;
        if ( dvres.rem != 0 ) { return -1; }
        if ( dvres.quot == 1 ) { return power; }
        dvres = div(dvres.quot, i);
    }
}

/*
First we establish if k is a power of i
Say k = i ^ m
We then check if m * l = j. If so, (k, l) is a double of (i, j)
*/
bool equivalent_old(int i, int j, int k, int l) {
    int m = power_of(i, k);
    return ( m > -1 ) && ( m * l == j );
}


bool equivalent(int i, int j, int k, int l) {
    return ( std::abs ( j * std::log(i) - l * std::log(k) ) < 0.0000001 );
}


void test() {
    assert ( power_of(10, 100) == 2 );
    assert ( power_of(3, 81) == 4 );
    assert ( power_of(2, 25) == -1 );

    assert ( equivalent(2, 4, 4, 2) );

    assert ( ! equivalent(2, 4, 5, 2) );

    std::cout << "Tests pass" << std::endl;    
}



// void print_grid(int **grid, )


int search_grid(int a_max, int b_max) {

    /* 
        Grid starts out being all zeros
        When we find a a ^ b that is equivalent to a previous one we 
        set that grid point to 1
    */
    int **grid = new int*[a_max + 1];
    for (int i = 0; i <= a_max; i++) { 
        grid[i] = new int[b_max + 1]();
    }

    for( int i = 2; i <= a_max; i++ ) {
        for( int j = 2; j <= b_max; j++ ) {
            if (grid[i][j] == 1) continue; 
            for( int k = i + 1; k <= a_max; k++ ) {
                for( int l = 2; l <= b_max; l++ ) {
                    if (grid[k][l] == 1) continue;
                    if (equivalent (i, j, k, l)) { grid[k][l] = 1; }
                }
            }
        }
    }

    int distinct = 0;
    for( int i = 2; i <= a_max; i++ ) {
        for( int j = 2; j <= b_max; j++ ) {
            if (grid[i][j] == 0) distinct++;
        }
    }

    return distinct;
}


int main(int argc, char *argv[]) {
    test();
    std::cout << "2 ≤ a ≤ 5 and 2 ≤ b ≤ 5 -> " << search_grid(5, 5) << std::endl;
    std::cout << "2 ≤ a ≤ 100 and 2 ≤ b ≤ 100 -> " << search_grid(100, 100) << std::endl;
}