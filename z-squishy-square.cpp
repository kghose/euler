/*
 * I define a squishy square to be a number with an even number of digits whose
 * square root is the sum of the top and bottom half of its digits. Like 81,
 * 2025 and 494209. This program will find squishy squares upto 2 x N, where N
 * is the number you pass to the program. Because of it's simplicity it can only
 * work up to N = 9
 *
 * Compile with: g++ -O3 z-squishy-square.cpp -o squishy
 *
 */
#include <cmath>
#include <cstdint>
#include <iostream>

// Integer powers of ten using only integer arithmetic.
uint64_t pow10i(uint64_t i) {
  uint64_t r = 1;
  for (uint64_t j = 0; j < i; j++) {
    r *= 10;
  }
  return r;
}

// Range of numbers to search whose squares will have an even number of digits.
struct Range {
  uint64_t start, stop, p;
};

// Given a digit count i find us the range of numbers whose squares will have 2i
// digits
Range get_range(uint64_t i) {
  uint64_t p = pow10i(i);
  uint64_t start = ceil(sqrt(pow10i(2 * i - 1)));
  uint64_t stop = p - 1;
  return Range{start, stop, p};
}

// Given a number n, tell us if n*n is squishy
bool is_squishy(uint64_t n, uint64_t p) {
  uint64_t square = n * n;
  uint64_t high = square / p;
  uint64_t low = square - high * p;
  return n == high + low;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Invoke as ./squishy <1/2 the number of digits to compute to>"
              << std::endl;
    exit(1);
  }
  uint64_t N = atoi(argv[1]);
  if (N > 9) {
    std::cout << "Sorry, this program will only work for N <= 9" << std::endl;
    exit(1);
  }

  for (uint64_t idx = 1; idx <= N; idx++) {
    Range c_range = get_range(idx);
    for (uint64_t n = c_range.start; n <= c_range.stop; n++) {
      if (is_squishy(n, c_range.p)) {
        std::cout << n * n << std::endl;
      }
    }
  }

  return 0;
}
