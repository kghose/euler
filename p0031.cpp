/*

Coin sums
Problem 31 
In England the currency is made up of pound, £, and pence, p, and there are eight coins 
in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?

*/
#include <iostream>
#include <vector>


struct CoinCollection {
    std::vector<int> values, coins, max_coins;
    int max_value;

    CoinCollection(int _max_value = 200) {
        values = {1, 2, 5, 10, 20, 50, 100, 200};
        coins = {0, 0, 0, 0, 0, 0, 0, 0};
        max_value = _max_value;
        for(int v : values) { max_coins.push_back( max_value / v ); }
    }

    int collection_value() {
        int val = 0;
        for(int i=0; i < coins.size(); i++) { val += coins[i] * values[i]; }
        return val;
    }

    /*
        Try the next possible coin combination.
        Return false if we are out of combinations
    */
    bool next(int coin=0) {
        if ( (coins[coin] < max_coins[coin]) && (collection_value() < max_value) ) {
            coins[coin]++;
            return true;
        } else {
            if ( coin == coins.size() - 1 ) {
                return false;  // We have exhausted all combinations to test
            } else {
                coins[coin] = 0;  // Reset this one
                return next(coin + 1);  // Advance the next counter
            }
        }
    }
};


std::ostream& operator << (std::ostream& out, const CoinCollection& cl) {
    for( int c : cl.coins ) {
        out << c << ", ";
    }
    return out;
}


void test() {
    CoinCollection c;
    std::vector<int> counters = {200, 100, 100, 100, 10000};
    for(int t : counters) {
        for( int i = 0; i < t; i++) {
            c.next();
        }
        std::cout << c << ": " << c.collection_value() << std::endl;
    }    
}


int main(int argc, char* argv[]) {
    // test();
    int max_value = 200, cnt = 0;
    CoinCollection c(max_value);
    while(c.next()) {
        if ( c.collection_value() == max_value ) {
            cnt++;
            std::cout << c << std::endl;
        }
    }
    std::cout << "Total ways: " << cnt << std::endl;
}
