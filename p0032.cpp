/*

Pandigital products
Problem 32 
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; 
for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, 
and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 
1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.


Algorithm:

We use a total of 9 digits. As a heuristic for number of digits in each component

M1         M2          P
1 (9)   x  2 (99)    = 3 (901) NO
1 (9)   x  3 (999)   = 4 (8991) NO
1 (9)   x  4 (9999)  = 5 (89991) POSSIBLE 
1 (1)   x  5 (10000)  = 5 (10000) NO 
2 (99)  x  2 (99)    = 4 (9801) NO
2 (99)  x  3 (999)   = 5 (98901) POSSIBLE
2 (10)  x  4 (1000)   = 5 (10000) NO
3 (100) x  3 (100)   = 5 (10000) NO

So we see that we can restrict ourselves to 1, 4 and 2, 3 digit combinations for the two multipliers

Assuming that such numbers are relatively rare, we store the products in a set

*/
#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_set>
#include <stdlib.h>


/* 
    Set up five counters that cycle through permutations
    of 1,2,3,4,5,6,7,8,9

    The lowest place (0) is the slowest changing. Therefore the
    available_digits for place p + 1 depends on the available_digits
    for p and the current p digit.

*/
struct Permute5 {
    int **available_digits;
    int *index;

    void set_available_digits(int place = 0) {
        if (place == 5) return;  // Nothing to do
        if (place == 0) {  // This has full freedom, so can have any of the 9
            for( int i = 0; i < 9; i++ ) {
                available_digits[ place ][ i ] = i + 1;    
            }
        } else {
            for( int i = 0, j = 0; i < 9 - place + 1 ; i++ ) {
                if ( i != index[ place - 1 ] ) {  // Copy all available digits, except the one in use by place + 1
                    available_digits[ place ][ j ] = available_digits[ place - 1 ][ i ];
                    j++;
                }
            }
            index[ place ] = 0;  // Reset the counter
        }
        set_available_digits(place + 1) ;  // Need to recursively set dependent digits
    }

    Permute5() {
        available_digits = new int*[ 5 ];
        for (int place = 0; place < 5; place++) {
            available_digits[ place ] = new int [ 9 - place ];
        }
        index = new int[ 5 ]();
        set_available_digits(0);
    }

    /*
        Generate the next permutation. Return false if we are all out of permutations  
    */
    bool next(int place = 4) {
        if ( place < 0) return true;
        if (index[ place ] < 9 - place - 1) {
            index[ place ]++;
            set_available_digits(place + 1);  // Update downstream choices
            return true;
        } else {
            if (place == 0) return false;  // All out of permute
            return next(place - 1);  // Need to advance the next higher digit (and so on)
        }
    }

    /*
        Treat place d0 as most significant digit and d1 as least significant digit
        Return the decimal value. So say our digits are 12345 and d0 = 2, d1 = 4
        The value returned will be 5 + 4 * 10 + 3 * 100
    */
    int value(int d0, int d1) const {
        int pow10 = 1, val = 0;
        for(int place = d1; place >= d0; place--) {
            val += available_digits[ place ][ index [ place ] ] * pow10;
            pow10 *= 10;
        }
        return val;
    }

    std::string internal_state() {
        std::ostringstream out;
        for(int place = 0; place < 5; place++) {
            for(int i = 0; i < 9 - place; i++) {
                if (i == index[ place ]) {
                    out << "[" << available_digits[ place ][ i ] << "]";
                } else {
                    out << " " << available_digits[ place ][ i ] << " ";                   
                }   
            }
            out << std::endl;
        }
        return out.str();
    }


};

std::ostream& operator << (std::ostream& out, const Permute5 &p) {
    for (int place = 0 ; place < 5; place++) {
        std::cout << p.available_digits[ place ][ p.index [ place ] ];
    }
    return out;
}


void test() {
    Permute5 p5;
    for(int i = 0; i < 20; i++) {
        std::cout << p5 << std::endl;
        std::cout << p5.internal_state() << std::endl;
        p5.next(); 
    }
    for(int i = 0; i < 1658; i++) { p5.next(); }
    std::cout << "\n\n ... \n\n" << std::endl;
    for(int i = 0; i < 20; i++) {
        std::cout << p5 << std::endl;
        std::cout << p5.internal_state() << std::endl;
        p5.next(); 
    } 
}

void test1() {
    Permute5 p5;
    for(int i = 0; i < 1700; i++) { p5.next(); }
    std::cout << p5 << " " << p5.value(0, 0) << ", " << p5.value(1, 4) << std::endl; 
    std::cout << p5 << " " << p5.value(0, 1) << ", " << p5.value(2, 4) << std::endl; 
}


// m1_digits are 1 or 2
// return -1 if the product is not pandigital, return the product otherwise
int check_pandigital(const Permute5 &p5, int m1_digits) {
    int m1 = p5.value(0, m1_digits - 1),
        m2 = p5.value(m1_digits, 4),
        product = m1 * m2;
    
    std::unordered_set<int> s;
    for (int place = 0 ; place < 5; place++) {
        s.insert( p5.available_digits[ place ][ p5.index [ place ] ] );
    }

    div_t dvres;
    dvres.quot = product;
    while( dvres.quot > 0) {
        dvres = div(dvres.quot, 10);
        if ( dvres.rem == 0 ) return -1; // Can't have a zero
        if ( s.count( dvres.rem ) ) return -1;  // We have a repeated digit
        s.insert( dvres.rem );
    }
    if ( s.size() != 9 ) return -1;  // Some digits are missing

    return product;  // If we survive till here, all digits are unique and present
}


int main(int argc, char* argv[]) {
    // test();
    // test1();
    Permute5 p5;
    std::unordered_set<int> s;
    int product, sum = 0;
    while( p5.next() ) { // We can do this because 1 * 2345 and 12 * 345 are both not pandigital
        for (int digit : {1, 2}) {
            product = check_pandigital(p5, digit);
            if (product != -1) { // pan-digital
                if ( !s.count( product ) ) {
                    std::cout << p5.value(0, digit - 1) << " * " << p5.value(digit, 4) << " = " << product << std::endl;
                    s.insert( product );
                    sum += product;
                }
            }
        }
    }
    std::cout << "\nSum is " << sum << std::endl;

    return 0;
}