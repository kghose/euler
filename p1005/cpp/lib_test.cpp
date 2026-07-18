#include <vector>

#include "../../doctest.h"
#include "lib.h"


TEST_CASE("5") {
  PrimeList primes{2, 3, 5, 7, 11, 13, 17, 19};

  std::vector<PrimeList> want{{2, 3}, {5}};

  PrimeType target = 5;
  std::vector<PrimeList> got;
  for (const auto &l : get_target_lists(0, PrimeList{}, target, primes)) {
    got.push_back(l);
  }

  CHECK(got == want);
}

TEST_CASE("20") {
  PrimeList primes{2, 3, 5, 7, 11, 13, 17, 19};

  std::vector<PrimeList> want{{2, 5, 13}, {2, 7, 11}, {3, 17}, {7, 13}};

  PrimeType target = 20;
  std::vector<PrimeList> got;
  for (const auto &l : get_target_lists(0, PrimeList{}, target, primes)) {
    got.push_back(l);
  }

  CHECK(got == want);
}
