/*
Reciprocal cycles
Problem 26 
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with 
denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit 
recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

Algorithm:

For this particular case (long-division) we see that we get a cycle the moment the remainder from a run of
of the long division is the same as a previous remainder. This is because long division progesses by
adding a zero (0) to the end of the remainder to determine the next digit of the division.

To solve this problem we can therefore simulate long-division and keep track of the remainders in a 
hash table. If the new remainder has been seen before, we have a cycle.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdlib.h>


struct LongDivisionResult {
    std::vector<int> digits;
    int denominator, cycle_start;
    LongDivisionResult(int d=2) {
        denominator = d;
        cycle_start = -1;
    }
    int cycle_length() {
        int cyl = 0;
        if (cycle_start > -1) { cyl = digits.size() - cycle_start; }
        return cyl;
    }
};

std::ostream& operator << (std::ostream& out, const LongDivisionResult &div) {
    out << "1/" << div.denominator << " = 0.";
    for(int i = 0; i < div.digits.size(); i++) {
        if (i==div.cycle_start) out << "(";
        out << div.digits[i];
    }
    if (div.cycle_start > -1) {
        out << ") Cycle length: " << div.digits.size() - div.cycle_start;
    }
    return out;
}


/*
    Given a denominator value, perform multiple rounds of long division until a cycle is found
    
    @param d The denominator
    @return LongDivisionResult result structure
*/
LongDivisionResult long_division(int d) {
    div_t dvres = div(1, d);
    int old_rem = dvres.rem;
    LongDivisionResult res(d);    
    std::unordered_map<int, int> remainders_seen;

    for(int i = 0;; i++) {        
        dvres = div(dvres.rem * 10, d);
    
        if (old_rem == 0) { // A rational number
            res.digits.push_back(dvres.quot);
            break; 
        }

        if ( remainders_seen.count(old_rem) ) {
            // This remainder has been seen before.
            // The cycle starts from when we first saw this remainder
            res.cycle_start = remainders_seen[old_rem];
            break;
        } else { // No cycle yet
            remainders_seen[old_rem] = i;
            res.digits.push_back(dvres.quot);
        }

        old_rem = dvres.rem;
    }
    return res;
}


void test() {
    for(int i = 2; i < 101; i++) {
        std::cout << long_division(i) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // test();

    LongDivisionResult res, max_res;
    int max_cycle = -1;
    for(int i = 2; i < 1000; i++) {
        res = long_division(i);
        if( res.cycle_length() > max_cycle) {
            max_cycle = res.cycle_length();
            max_res = res;
        }
    }

    std::cout << "\nLongest cycle: "; 
    std::cout << max_res << std::endl;

    return 0;
}
