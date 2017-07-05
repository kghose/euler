/*

Digit factorials
Problem 34
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.


Algorithm:

N = number
F = sum of factorial of digits

Digits    N          F
2        10          2
         99          725760

3        100         3
         999         1088640

4        1000        4
         9999        1451520

7        1000000     7
         9999999     2540160

8        10000000    8
         99999999    2903040

As can be seen numbers with 8 digits and more can never be expressed as the sum of the factorials
of their digits, so need only search from 2 to 7 digits
*/
#include<vector>
#include<iostream>
#include<cassert>


// Stores digits for a number, allows us to increment it.
// Incrementing beyond 99...9 increases the digit count
struct Number {
	int d_min, d_max;
	std::vector<int> digits;
	std::vector<int> powers;
	std::vector<int> factorial;

	Number(int min_digit, int max_digit) {
		d_min = min_digit;
		d_max = max_digit;
		int power = 1, fact = 1;
		for(int i = 0; i < d_max; i++) {
			powers.push_back( power );
			power *= 10;
		}
		for(int i = 0; i < 10; i++) {
			factorial.push_back( fact );
			fact *= (i + 1);
		}
		for(int i = 0; i < d_min - 1; i++) { digits.push_back( 0 ); }
		digits.push_back( 1 );
	}

	int value() const {
		int val = 0;
		for(int i = 0; i < digits.size(); i++) {
			val += digits[i] * powers[i];
		}
		return val;
	}

	int sum_of_factorials() const {
		int val = 0;
		for(int i = 0; i < digits.size(); i++) {
			val += factorial[ digits[i] ];
		}
		return val;
	}

	// Increment number. If max_digits exceeded, return false
	bool next() {
		int d = 0;
		for( ;; ) {
			digits[ d ]++;
			if( digits[ d ] < 10) return true;
			digits[ d ] = 0;
			d++;
			if ( d == d_max - 1 ) return false;
			if ( d == digits.size() ) digits.push_back( 0 );
		}
	}
};


std::ostream& operator<<(std::ostream& out, const Number &n) {
	for(int i = n.digits.size() - 1; i > -1; i--) {
		out << n.digits[i];
	}
	out << ": val = " << n.value() << ": !(d) = " << n.sum_of_factorials();
	return out;
}


void test1() {
	Number n(2, 3);
	for(int f : n.factorial ) {
		std::cout << f << std::endl;
	}
	for(;;) {
		std::cout << n << std::endl;
		if ( !n.next() ) break;
	}
}


int main(int argc, char *argv[]) {
	// test1();

	int sum = 0;
	Number n(2, 7);
	for(;;) {
		if( n.value() == n.sum_of_factorials() ) {
			sum += n.value();
			std::cout << n << std::endl;
		}
		if ( !n.next() ) break;
	}

	std::cout << sum << std::endl;
}
