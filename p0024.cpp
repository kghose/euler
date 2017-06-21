/*

Lexicographic permutations
Problem 24 
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of 
the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, 
we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
  
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


struct DigitMatrix {
    int **available_digits;
    int *place_value;
    int digits;

    void initialize_available_digits(int place = 0) {
        // Only the first one has full choice
        if (place == 0) {
            for(int i=0; i < digits; i++) available_digits[0][i] = i;
        } else {
            for(int i=0, j=0; i < digits - place + 1; i++) {
                if (i == place_value[place - 1]) continue;  // This digit used by previous place
                available_digits[place][j] = available_digits[place - 1][i];
                j++;
            }
        }
        place_value[place] = 0;  // This place starts from the begining of the available list
    }

    DigitMatrix(int _digits = 10) {
        digits = _digits;
        place_value = new int[digits - 1]{0};     // Current pointer for each place
        available_digits = new int*[digits - 1];  // These are the digits to fill. The last one has no freedom
        for(int i=0; i < digits - 1; i++)
            available_digits[i] = new int[digits - i];  // For each succesive digit, we have one less option
        for(int place = 0; place < digits - 1; place++)
            initialize_available_digits(place);
    }

    ~DigitMatrix() {
        for(int i=0; i < digits - 1; i++)
            delete[] available_digits[i];
        delete[] available_digits;
    }

    void advance_place(int place) {
        place_value[place]++;
        if (place_value[place] == digits - place) {  // All outta digits
            advance_place(place - 1);
            initialize_available_digits(place);
        }
    }

    void next() {
        advance_place(digits - 2);
    }

    std::string internal_state() {
        std::ostringstream out;
        for(int place = 0; place < digits - 1; place++) {
            for(int i = 0; i < digits - place; i++) {
                if (i == place_value[place]) {
                    out << "[" << available_digits[place][i] << "]";
                } else {
                    out << " " << available_digits[place][i] << " ";                   
                }   
            }
            out << std::endl;
        }
        return out.str();
    }

};


std::ostream& operator << (std::ostream &o, const DigitMatrix& dm) {
    for(int place = 0; place < dm.digits - 1; place++) {
        o << dm.available_digits[place][dm.place_value[place]];
    }
    o << dm.available_digits[dm.digits - 2][1 - dm.place_value[dm.digits - 2]];  // last digit has no freedom
    return o;
}

void test(int digits, int ctr) {
    DigitMatrix dm(digits);
    while (ctr--) {
        std::cout << dm << std::endl;
        std::cout << dm.internal_state() << std::endl;
        dm.next();
    }    
}


int main(int argc, char *argv[]) {
    test(3, 6);
    test(4, 10);

    DigitMatrix dm(10);
    for(int i=0; i < 999999; i++)
        dm.next();
    
    std::cout << dm << std::endl;
}