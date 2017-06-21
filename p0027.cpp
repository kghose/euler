/*

Quadratic primes
Problem 27 
Euler discovered the remarkable quadratic formula:

n^2 + n + 41

It turns out that the formula will produce 40 primes for the consecutive integer values 0 ≤ n ≤ 39. 
However, when n=40, 40^2 + 40 + 41 = 40(40+1)+41 is divisible by 41, and certainly 
when n=41, 41^2 + 41 + 41  is clearly divisible by 41.

The incredible formula n^2 − 79n + 1601 was discovered, which produces 80 primes for the consecutive 
values 0 ≤ n ≤ 79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

n^2 + an + b, where |a|<1000 and |b|≤1000

where |n|is the modulus/absolute value of n

e.g. |11|=11 and |−4|=4

Find the product of the coefficients, a and b, for the quadratic expression that produces the 
maximum number of primes for consecutive values of n, starting with n=0.

*/
#include <iostream>
#include <vector>
#include <cmath>


/*
    Keep an ordered list of primes. Use binary search to find the number in the list
    If the number is larger than than the largest number in the list, extend the list
*/
struct Primal {
    std::vector<int> prime_list;
    Primal() {
        prime_list = {2, 3, 5, 7, 11, 13};  // Just to get us started
    }

    int last_prime() {
        if (prime_list.size())
            return prime_list[prime_list.size() - 1];
        else
            return 0;
    }

    void compute_primes_just_past(int n) {
        int i = last_prime() + 1;
        while ( last_prime() < n ) {
            if ( dumb_prime_check(i) ) { prime_list.push_back(i); }
            i++;
        }
    }

    bool dumb_prime_check(int n) {
        for(int j = 2; j <= std::sqrt(n); j++) { if ( n % j == 0 ) return false; }
        return true;
    }

    bool bisect(int n, int low, int high) {
        if (high - low == 1) { return (n == prime_list[low]) || (n == prime_list[high]); }

        int mid = ( high + low ) / 2;
        if (n <= prime_list[mid]) {
            return bisect(n, low, mid);
        } else {
            return bisect(n, mid, high);
        }
    }

    bool in_prime_list(int n) {
        return bisect(n, 0, prime_list.size() - 1);
    }

    bool is_prime(int n) {
        if ( n > last_prime() ) { compute_primes_just_past(n);}
        return in_prime_list(n);
    }
};


void test1() {
    Primal p;
    for (int n : p.prime_list) { std::cout << n << " ";}
    std::cout << std::endl;

    for (int i = 2; i < 14; i++) {
        std::cout << i << ": " << p.in_prime_list(i) << std::endl;
    }
}


void test2() {
    Primal p;
    for (int i = 2; i < 100; i++) {
        if (p.dumb_prime_check(i)) {
            std::cout << i << std::endl;
        }
    }
}


void test3() {
    Primal p;
    for (int i = 2; i < 100; i++) {
        if (p.is_prime(i)) {
            std::cout << i << std::endl;
        }
    }
}


int score_for_quadratic(int a, int b, Primal &p) {
    int n = 0;
    while (p.is_prime( n * n + a * n  + b )) { n++; }
    return n;
}


void test4() {
    Primal p;
    std::cout << "1, 41 : " << score_for_quadratic(1, 41, p) << std::endl;
    std::cout << "-79, 1601 : " << score_for_quadratic(-79, 1601, p) << std::endl;
}


int main(int argc, char *argv[]) {
    // test1();
    // test2();
    // test3();
    // test4();

    int max_score = 0, max_a, max_b;
    Primal p;
    for (int a = -999; a < 1000; a++)
        for(int b = -1000; b <= 1000; b++) {
            int ms = score_for_quadratic(a, b, p);
            if ( ms > max_score) {
                max_score = ms;
                max_a = a; max_b = b;   
            }
        }
    
    std::cout << "a = " << max_a << ", b = " << max_b << " (score = " << max_score << ") a * b = " << max_a * max_b << std::endl;
}