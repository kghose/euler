/*
 * Expression describes the binary tree shape of the expression.
 * Each node is statically and uniquely numbered (OpIdx) as is each leaf
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

typedef int OpIdx;
typedef int NumIdx;

struct Expression;

using Operand = std::variant<NumIdx, Expression>;

struct Expression {
  Operand &lhs, &rhs;
  OpIdx opIdx;
};

struct Calculation {
  std::vector<int> num;
  std::vector<Op> op;
  const Expression e;

  std::optional<int> eval() { return std::visit(*this, Operand(e)); }

  std::optional<int> operator()(const NumIdx i) { return num[i]; }
  std::optional<int> operator()(const Expression &e);
};

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

  auto a = compute(lv, rv, op[e.opIdx]);
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
  Operand l = 0, r = 1;
  Expression e{.lhs = l, .rhs = r, .opIdx = 0};

  auto tc = GENERATE(TestCase{.name = "plus",
                              .c = Calculation{.num = std::vector<int>{1, 1},
                                               .op = std::vector<Op>{Op::Plus},
                                               .e = e},
                              .want = 2},
                     TestCase{.name = "minus",
                              .c = Calculation{.num = std::vector<int>{2, 1},
                                               .op = std::vector<Op>{Op::Minus},
                                               .e = e},
                              .want = 1},
                     TestCase{.name = "divide",
                              .c = Calculation{.num = std::vector<int>{6, 2},
                                               .op = std::vector<Op>{Op::Div},
                                               .e = e},
                              .want = 3},
                     TestCase{.name = "multiply",
                              .c = Calculation{.num = std::vector<int>{3, 2},
                                               .op = std::vector<Op>{Op::Mult},
                                               .e = e},
                              .want = 6}

  );

  SUBCASE(tc.name);
  CHECK(tc.c.eval() == tc.want);
}

/*
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
}

TEST_CASE("nested operands") {

  SUBCASE("nested lhs") {
    Operand a = 4, b = 2, c = 1,
            lhs = Operation{.lhs = a, .rhs = b, .op = Op::Divide};
    Operation o{.lhs = lhs, .rhs = c, .op = Op::Minus};

    auto ans = o.compute();
    CHECK(ans.value() == 1);
  }

  SUBCASE("nested lhs,rhs") {
    Operand a = 4, b = 2, c = 6, d = 3,
            lhs = Operation{.lhs = a, .rhs = b, .op = Op::Divide},
            rhs = Operation{.lhs = c, .rhs = d, .op = Op::Divide};
    Operation o{.lhs = lhs, .rhs = rhs, .op = Op::Minus};

    auto ans = o.compute();
    CHECK(ans.value() == 0);
  }
}
*/
