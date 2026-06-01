/*
 * Expression describes the binary tree shape of the expression.
 * Each node and leaf is statically, uniquely and automatically numbered
 *
 * Calculate furnishes a list of numbers and a list of operations and
 * then computes the value of the expression by substituting the
 * operations and numbers corresponding to the indices.
 */

#pragma once
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "doctest.h"

enum class Op { Minus, Plus, Div, Mult };

inline std::optional<int> compute(int lv, int rv, Op op) {
  switch (op) {
  case Op::Minus:
    return lv - rv;
  case Op::Plus:
    return lv + rv;
  case Op::Div: {
    div_t d = std::div(lv, rv);
    if (d.rem > 0) {
      return std::nullopt;
    } else {
      return d.quot;
    }
  }
  case Op::Mult:
    return lv * rv;
  }
}

struct Expression;
struct LeafInt {};

using Operand = std::variant<LeafInt, Expression>;

struct Expression {
  Operand &lhs, &rhs;
};

struct Calculation {
  std::vector<int> num;
  std::vector<Op> op;
  const Expression e;

  size_t leafIdx = 0, opIdx = 0;

  std::optional<int> eval() { return std::visit(*this, Operand(e)); }

  std::optional<int> operator()(const LeafInt _) { return num[leafIdx++]; }
  std::optional<int> operator()(const Expression &e);
};

inline Operand LEAF = LeafInt{};

inline std::optional<int> Calculation::operator()(const Expression &e) {
  std::optional<int> l = std::visit(*this, e.lhs);
  std::optional<int> r = std::visit(*this, e.rhs);

  if ((!l) || (!r)) {
    return std::nullopt;
  }

  int lv = l.value(), rv = r.value();
  if ((lv < 0) || (rv < 0)) {
    return std::nullopt;
  }

  auto a = compute(lv, rv, op[opIdx++]);
  if (!a.has_value()) {
    return std::nullopt;
  }

  int av = a.value();
  if (av < 0) {
    return std::nullopt;
  }

  return av;
}

struct TestCase {
  std::string name;
  Calculation c;
  int want;
};

TEST_CASE("test basic operations") {
  Expression e{.lhs = LEAF, .rhs = LEAF};

  auto tc = GENERATE(
      TestCase{.name = "plus",
               .c = Calculation{.num = {1, 1}, .op = {Op::Plus}, .e = e},
               .want = 2},
      TestCase{.name = "minus",
               .c = Calculation{.num = {2, 1}, .op = {Op::Minus}, .e = e},
               .want = 1},
      TestCase{.name = "divide",
               .c = Calculation{.num = {6, 2}, .op = {Op::Div}, .e = e},
               .want = 3},
      TestCase{.name = "multiply",
               .c = Calculation{.num = {3, 2}, .op = {Op::Mult}, .e = e},
               .want = 6}

  );

  SUBCASE(tc.name) { CHECK(tc.c.eval() == tc.want); }
}

TEST_CASE("test operations with illegal results") {
  Expression e{.lhs = LEAF, .rhs = LEAF};

  auto tc = GENERATE(
      TestCase{.name = "negative input",
               .c = Calculation{.num = {1, -1}, .op = {Op::Plus}, .e = e},
               .want = 0},
      TestCase{.name = "negative result",
               .c = Calculation{.num = std::vector<int>{1, 2},
                                .op = std::vector<Op>{Op::Minus},
                                .e = e},
               .want = 0});

  SUBCASE(tc.name) { CHECK(tc.c.eval().has_value() == false); }
}

TEST_CASE("nested operands") {

  SUBCASE("nested lhs") {
    Operand el = Expression{.lhs = LEAF, .rhs = LEAF};
    Expression e{.lhs = el, .rhs = LEAF};
    auto ans = Calculation{.num = {4, 2, 1}, .op = {Op::Div, Op::Minus}, .e = e}
                   .eval();

    CHECK(ans.value() == 1);
  }

  SUBCASE("nested lhs,rhs") {
    Operand el = Expression{.lhs = LEAF, .rhs = LEAF};
    Operand er = Expression{.lhs = LEAF, .rhs = LEAF};

    Expression e{.lhs = el, .rhs = er};
    auto ans = Calculation{.num = {4, 2, 6, 3},
                           .op = {Op::Div, Op::Div, Op::Minus},
                           .e = e}
                   .eval();

    CHECK(ans.value() == 0);
  }
}
