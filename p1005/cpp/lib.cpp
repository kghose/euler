#include <cstdint>
#include <generator>
#include <iostream>
#include <memory>
#include <ranges>
#include <vector>

#include "lib.h"

auto get_target_lists(size_t pI, const PrimeList &partialList, uint16_t target,
                   const PrimeList &primes) -> std::generator<PrimeList> {
  for (size_t i = pI; i < primes.size(); i++) {
    auto newPartialList = PrimeList(partialList);
    newPartialList.push_back(primes[i]);

    PrimeType s = 0;
    for (auto p : newPartialList) {
      s += p;
    }

    if (s == target) {
      co_yield newPartialList;
    }

    if (s < target) {
      co_yield std::ranges::elements_of(
          get_target_lists(i + 1, newPartialList, target, primes));
    }
  }
}

