/*

Digit cancelling fractions
Problem 33 
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting 
to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, 
is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, 
and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.


Algorithm:

Enumerating through all combinations of WX / YZ find those examples where X, Z are not zero and
W == Z  WX / YZ = X / Y or
X == Y  WX / YZ = W / Z

Then, eliminate common prime factors from all of these fractions to arrive at the denominator
*/
#include<vector>
#include<iostream>
#include<cassert>


// Represents WX / YZ
struct TwoDigitFraction {
	int W, X, Y, Z;
	TwoDigitFraction() { ; }
	TwoDigitFraction(int n, int d) {
		W = n / 10;
		X = n % 10;
		Y = d / 10;
		Z = d % 10;
	}
	int num() { return W * 10 + X; }
	int den() { return Y * 10 + Z; }
};


const std::vector<float> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47};


// Reduce a fraction to it's simplest (relatively prime) components
TwoDigitFraction reduce(TwoDigitFraction f) {
	int num = f.num(), den = f.den();
	for(int p : primes) {
		while( ( num % p == 0 ) && ( den % p == 0) ) {
			num /= p;
			den /= p;
		}
	}
	return TwoDigitFraction( num, den );
}


// Performs reduction on both sides before checking equality
// This leads to redundant work, but the data set is so small, the clarity is worth it
bool operator==( const TwoDigitFraction f1, const TwoDigitFraction f2 ) {
	TwoDigitFraction f1_r = reduce( f1 ), f2_r = reduce( f2 );
	return ( ( f1_r.W == f2_r.W ) &&
			 ( f1_r.X == f2_r.X ) &&
			 ( f1_r.Y == f2_r.Y ) &&
			 ( f1_r.Z == f2_r.Z ) );
}


bool operator!=( const TwoDigitFraction f1, const TwoDigitFraction f2 ) {
	return !( f1 == f2 );
}


void test1() {
	assert( TwoDigitFraction( 14, 28 ) == TwoDigitFraction( 1, 2 ) );
	assert( TwoDigitFraction( 13, 26 ) == TwoDigitFraction( 1, 2 ) );
	assert( TwoDigitFraction( 5 * 13, 3 * 7 ) == TwoDigitFraction( 5 * 13, 3 * 7 ) );
	std::cerr << "Reduction and equality tests pass." << std::endl;
}


// W == Z  WX / YZ = X / Y or
// X == Y  WX / YZ = W / Z
bool is_digit_cancelling_fraction(const TwoDigitFraction &f) {
	if ( ( f.X == 0 ) && ( f.Z == 0 ) ) return false;
	if ( ( ( f == TwoDigitFraction ( f.X, f.Y ) ) && ( f.W == f.Z ) ) ||
		 ( ( f == TwoDigitFraction ( f.W, f.Z ) ) && ( f.X == f.Y ) ) ) return true;
 	return false;
}


void test2() {
	assert( is_digit_cancelling_fraction( TwoDigitFraction ( 49, 98 ) ) );
	assert( !is_digit_cancelling_fraction( TwoDigitFraction ( 30, 50 ) ) );
	std::cerr << "Membership tests pass." << std::endl;
}


// Return a two digit fraction that is a reduced version of the product of
// the supplied list of two digit fractions. The result may not be a two digit fraction
// But will do for our purposes
TwoDigitFraction reduced_product(const std::vector<TwoDigitFraction> &f_list) {
	std::vector<int> num, den;
	for( auto f : f_list ) {
		num.push_back( f.num() );
		den.push_back( f.den() );
	}
	for(int i = 0; i < num.size(); i++) {
		for(int j = 0; j < den.size(); j++) {
			TwoDigitFraction r = reduce( TwoDigitFraction( num[i], den[j] ));
			num[i] = r.num();
			den[j] = r.den();
		}
	}

	int n=1, d=1;
	for(int i = 0; i < num.size(); i++) {
		n *= num[i];
		d *= den[i];
	}

	return TwoDigitFraction( n, d );
}


int main( int argc, char *argv[] ) {
	test1();
	test2();

	std::vector<TwoDigitFraction> f_list;
	for( int Y = 1; Y < 10; Y++) {
		for( int Z = 1; Z < 10; Z++) {
			for( int W = 1; W <= Y; W++) {
				for( int X = 1; X < 10; X++) {
					TwoDigitFraction tdf(  W * 10 + X, Y * 10 + Z);
					if ( tdf.num() >= tdf.den() ) continue;
					if ( is_digit_cancelling_fraction( tdf ) ) {
						f_list.push_back( tdf );
						std::cout << tdf.num() << ", " << tdf.den() << std::endl;
					}
				}
			}
		}
	}

	TwoDigitFraction tdf = reduced_product( f_list );
	std::cout << tdf.den() << std::endl;
}
