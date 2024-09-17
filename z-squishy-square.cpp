/*
 * I define a squishy square to be a number with an even number of digits whose
 * square root is the sum of the top and bottom half of its digits. Like 81,
 * 2025 and 494209. This program will find squishy squares upto 2 x N, where N
 * is the number you pass to the program. Because of it's simplicity it can only
 * work up to N = 9
 *
 * Compile with: g++ -O3 -lpthread -fopenmp z-squishy-square.cpp -o squishy
 * Set omp threads env variable before running: e.g.  export OMP_NUM_THREADS=12
 *
 */
#include <cmath>
#include <cstdint>
#include <iostream>

const uint64_t powers_of_ten[] = {10,     100,      1000,      10000,
                                  100000, 10000000, 100000000, 1000000000};

struct Range {
  uint64_t start, stop;
};

struct CandidateRange {
  Range high, low;
  uint64_t pow_ten;
};

CandidateRange get_candidate_range(uint64_t pow_ten) {
  return CandidateRange{Range{pow_ten / 10, pow_ten - 1}, Range{0, pow_ten - 1},
                        pow_ten};
}

struct Candidate {
  uint64_t high, low, pow_ten;
};

bool is_squishy(const Candidate &candidate) {
  uint64_t number = candidate.low + candidate.high * candidate.pow_ten;
  uint64_t sum = candidate.low + candidate.high;
  return (sum * sum == number);
}

bool next_candidate(Candidate &candidate, uint64_t max_pow_ten) {
  uint64_t next_low = candidate.low + 1;
  uint64_t next_high = candidate.high;
  if (next_low == candidate.pow_ten) {
    next_low = 0;
    next_high += 1;
  }
  if (next_high == candidate.pow_ten) {
    if (candidate.pow_ten == max_pow_ten) {
      return false;
    }
    candidate.pow_ten *= 10;
  }
  candidate.low = next_low;
  candidate.high = next_high;
  return true;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Invoke as ./squishy <number of digits to compute to>"
              << std::endl;
    exit(1);
  }
  uint64_t N = atoi(argv[1]);
  if (N > 9) {
    std::cout << "Sorry, this program will only work for N <= 9" << std::endl;
    exit(1);
  }

  for (uint64_t idx = 0; idx < N; idx++) {
    CandidateRange c_range = get_candidate_range(powers_of_ten[idx]);
    for (uint64_t high = c_range.high.start; high <= c_range.high.stop;
         high++) {
#pragma omp parallel for
      for (uint64_t low = c_range.low.start; low <= c_range.low.stop; low++) {

        Candidate candidate{high, low, c_range.pow_ten};
        if (is_squishy(candidate)) {
          std::cout << candidate.high * candidate.pow_ten + candidate.low
                    << std::endl;
        }
      }
    }
  }

  return 0;
}
