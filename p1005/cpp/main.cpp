#include <fstream>
#include <iostream>
#include <string>
#include <sys/resource.h>

#include "lib.h"

auto peak_memory_mb() -> long {
  struct rusage usage;
  if (getrusage(RUSAGE_SELF, &usage) == 0) {
    return usage.ru_maxrss / 1024;
  }
  return -1;
}

auto load_primes(int max) -> PrimeList {
  PrimeList primes{};

  std::ifstream file("../../primes1000.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open primes1000.txt." << '\n';
    return primes;
  }

  std::string line;

  while (std::getline(file, line)) {
    PrimeType p = std::stoi(line);
    primes.push_back(p);
    if (p > max) {
      break;
    }
  }

  return primes;
}

void print_diagnostics(PrimeType target, const std::vector<PrimeList> &pl) {
  std::cout << "Target=" << target << " Lists=" << pl.size()
            << " (Mem=" << peak_memory_mb() << "MB)" << "\r";
}

auto main(int argc, char *argv[]) -> int {
  if (argc != 2) {
    std::cout << argv[0] << " <target>\n";
    exit(1);
  }

  PrimeType target = std::atoi(argv[1]);

  auto primes = load_primes(target);

  std::vector<PrimeList> got;
  for (const auto &l : get_target_lists(0, PrimeList{}, target, primes)) {
    got.push_back(l);
    if (got.size() % 50 == 0) {
      print_diagnostics(target, got);
    }
  }
  print_diagnostics(target, got);
  std::cout << "\n\n";
}
