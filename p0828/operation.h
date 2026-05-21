#pragma once
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <variant>

#include "doctest.h"

enum class Op { Minus, Plus, Divide, Multiply };

struct Operation;
struct Operate {
  std::optional<int> operator()(const int i) { return i; }
  std::optional<int> operator()(const Operation &o);
};

using Operand = std::variant<int, Operation>;

struct Operation {
  Operand &lhs, &rhs;
  Op op;
  std::optional<int> compute() { return std::visit(Operate{}, Operand(*this)); }
};

inline std::optional<int> compute(int lv, int rv, Op op) {
  switch (op) {
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

  auto a = compute(lv, rv, o.op);
  if (!a.has_value()) {
    return std::nullopt;
  }

  int av = a.value();
  if (av < 0) {
    return std::nullopt;
  }

  return av;
}

TEST_CASE("test basic operations") {

  SUBCASE("plus") {
    Operand l = 1, r = 1;
    Operation o{.lhs = l, .rhs = r, .op = Op::Plus};

    auto a = o.compute();
    CHECK(a.value() == 2);
  }

  SUBCASE("minus") {
    Operand l = 3, r = 1;
    Operation o{.lhs = l, .rhs = r, .op = Op::Minus};

    auto a = o.compute();
    CHECK(a.value() == 2);
  }

  SUBCASE("divide") {
    Operand l = 4, r = 2;
    Operation o{.lhs = l, .rhs = r, .op = Op::Divide};

    auto a = o.compute();
    CHECK(a.value() == 2);
  }

  SUBCASE("multiply") {
    Operand l = 1, r = 2;
    Operation o{.lhs = l, .rhs = r, .op = Op::Multiply};

    auto a = o.compute();
    CHECK(a.value() == 2);
  }
}

TEST_CASE("test operations with illegal results") {

  SUBCASE("negative input") {
    Operand l = 1, r = -1;
    Operation o{.lhs = l, .rhs = r, .op = Op::Plus};

    auto a = o.compute();
    CHECK(a.has_value() == false);
  }

  SUBCASE("negative result") {
    Operand l = 1, r = 2;
    Operation o{.lhs = l, .rhs = r, .op = Op::Minus};

    auto a = o.compute();
    CHECK(a.has_value() == false);
  }

  SUBCASE("minus") {
    Operand l = 3, r = 1;
    Operand o = Operation{.lhs = l, .rhs = r, .op = Op::Minus};

    auto a = std::visit(Operate{}, o);
    CHECK(a.value() == 2);
  }

  SUBCASE("divide") {
    Operand l = 4, r = 2;
    Operand o = Operation{.lhs = l, .rhs = r, .op = Op::Divide};

    auto a = std::visit(Operate{}, o);
    CHECK(a.value() == 2);
  }

  SUBCASE("multiply") {
    Operand l = 1, r = 2;
    Operand o = Operation{.lhs = l, .rhs = r, .op = Op::Multiply};

    auto a = std::visit(Operate{}, o);
    CHECK(a.value() == 2);
  }
}
