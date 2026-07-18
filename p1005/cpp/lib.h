#pragma once

#include <cstdint>
#include <generator>
#include <vector>

using PrimeType = uint16_t;
using PrimeList = std::vector<PrimeType>;

auto get_target_lists(size_t currentI, const PrimeList &partialList,
                   uint16_t target, const PrimeList &primes)
    -> std::generator<PrimeList>;
