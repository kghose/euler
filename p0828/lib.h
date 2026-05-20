#pragma once
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <variant>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

enum class Op { Minus, Plus, Divide, Multiply };

struct Operation;
using Operand = std::variant<int, Operation>;

struct Operation {
  Operand &lhs, &rhs;
  Op op;
};

struct Operate {
  std::optional<int> operator()(const int i) { return i; }
  std::optional<int> operator()(const Operation &o);
};

inline std::optional<int> Operate::operator()(const Operation &o) {
  std::optional<int> l = std::visit(*this, o.lhs);
  std::optional<int> r = std::visit(*this, o.rhs);

  if ((!l) || (!r)) {
    return std::nullopt;
  }

  int lv = l.value(), rv = r.value();
  if ((lv < 0) || (rv < 0)) {
    return std::nullopt;
  }

  switch (o.op) {
  case Op::Minus:
    return lv - rv;
  case Op::Plus:
    return lv + rv;
  case Op::Divide: {
    div_t d = std::div(lv, rv);
    if (d.rem > 0) {
      return std::nullopt;
    } else {
      return d.quot;
    }
  }
  case Op::Multiply:
    return lv * rv;
  }
}

TEST_CASE("test basic operations") {

  SUBCASE("add") {
    Operand l = 1, r = 1;
    Operand o = Operation{.lhs = l, .rhs = r};

    auto a = std::visit(Operate{}, o); 
    CHECK(a.value() == 2); 
  }
}
