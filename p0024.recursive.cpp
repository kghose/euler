/*

Lexicographic permutations
Problem 24 
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of 
the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, 
we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?


The alogrithm here is the same as for p0024.cpp, but is implemented as a recursive function.
The code is more concise and clear, but there is a significant increase in run-time due to the
repeated copying of std::vector values.

Algorithm: 

Defining:
    place - location in the permutation (we have 10 of these)
            place0 is the lowest (left most) place
    digit - the actual digit in that place

We use a "forward backward" algorithm
- For each place keep a list of available digits (i.e. not used in previous places) in lexicographic order
- Forward algorithm:
    - Starting with place0, pick a digit
    - Do this for all places
- Backward algorithm:
    - For a given place, if we've exhausted our list, go up one place and pick the next digit
    - Refresh all the downstream available digits lists 



*/
#include <iostream>
#include <sstream>
#include <vector>


struct Permuter {
    int max_places;  // The number of places we consider
    int iterations;  // The number of permutations left to do
    std::vector<int> final_permutation;  // The permutation we want

    /*
        At each level ("place") we loop over all the available digits, creating a new list of available digits
        for the next place down and passing that on to the next level (place). We keep track of how many
        permutations we have done and decrement that by one when we complete a permutation.

        @param place The current place we are considering 0, 1, 2 ....
        @param available_digits The digits we are allowed to pick from for this place
        @param permutation The number (permutation) we are building up
    */
    bool permute(int place, std::vector<int> available_digits, std::vector<int> permutation) {
        if (place == max_places) {
            // std::cout << printed_value(permutation) << std::endl;
            if (--iterations == 0) {
                final_permutation = permutation;
                return true;
            } else {
                return false;
            }        
        }
        for(int d : available_digits) {
            std::vector<int> new_permutation = permutation;
            new_permutation.push_back(d);
            std::vector<int> new_available_digits;
            for(int d0 : available_digits) {
                if (d0 != d) new_available_digits.push_back(d0);
            } 
            if (permute(place + 1, new_available_digits, new_permutation)) {
                return true;
            }
        }
        return false;
    }

    Permuter(int _digits, int _iterations) {
        max_places = _digits;
        iterations = _iterations;
        std::vector<int> available_digits;
        for(int i = 0; i < _digits; i++) available_digits.push_back(i);
        permute(0, available_digits, std::vector<int>());
    }

    std::string printed_value(std::vector<int> &val) {
        std::ostringstream out;
        for(int d : val) { out << d; }
        return out.str();
    }
};

void test(int digits, int ctr) {
    Permuter p(digits, ctr);
    std::cout << p.printed_value(p.final_permutation) << std::endl;
}


int main(int argc, char *argv[]) {
    test(3, 6);
    test(4, 10);
    test(10, 1000000);
}