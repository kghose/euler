/*
 * Create a printed representation of the operation.
 */
#pragma once

#include <format>
#include <string>

#include "operation.h"

struct PrintOperation {
  std::string operator()(const int i) { return std::to_string(i); }
  std::string operator()(const Operation &o);
};

inline std::string print(std::string lv, std::string rv, Op op) {
  std::string op_symbol = "";
  switch (op) {
  case Op::Minus:
    op_symbol = "-";
    break;
  case Op::Plus:
    op_symbol = "+";
    break;
  case Op::Divide:
    op_symbol = "/";
    break;
  case Op::Multiply:
    op_symbol = "*";
    break;
  }
  return std::format("({} {} {})", lv, op_symbol, rv);
}

inline std::string PrintOperation::operator()(const Operation &o) {
  std::string l = std::visit(PrintOperation{}, o.lhs);
  std::string r = std::visit(PrintOperation{}, o.rhs);
  return print(l, r, o.op);
}

inline std::string print(const Operation &o) {
	return std::visit(PrintOperation{}, Operand(o));
}

TEST_CASE("test basic operations") {

  SUBCASE("plus") {
    Operand l = 1, r = 1;
    Operation o{.lhs = l, .rhs = r, .op = Op::Plus};

    auto a = print(o);
    CHECK(a == "(1 + 1)");
  }

  SUBCASE("minus") {
    Operand l = 3, r = 1;
    Operation o{.lhs = l, .rhs = r, .op = Op::Minus};

    auto a = print(o);
    CHECK(a == "(3 - 1)");
  }

  SUBCASE("divide") {
    Operand l = 4, r = 2;
    Operation o{.lhs = l, .rhs = r, .op = Op::Divide};
    
    auto a = print(o);
    CHECK(a == "(4 / 2)");

  }

  SUBCASE("multiply") {
    Operand l = 1, r = 2;
    Operation o{.lhs = l, .rhs = r, .op = Op::Multiply};

    auto a = print(o);
    CHECK(a == "(1 * 2)");
  }
}

TEST_CASE("test operations with illegal results") {

  SUBCASE("negative input") {
    Operand l = 1, r = -1;
    Operation o{.lhs = l, .rhs = r, .op = Op::Plus};

    auto a = print(o);
    CHECK(a == "(1 + -1)");
  }

  SUBCASE("negative result") {
    Operand l = 1, r = 2;
    Operation o{.lhs = l, .rhs = r, .op = Op::Minus};

    auto a = print(o);
    CHECK(a == "(1 - 2)");
  }
}

TEST_CASE("nested operands") {

  SUBCASE("nested lhs") {
    Operand a = 4, b = 2, c = 1,
            lhs = Operation{.lhs = a, .rhs = b, .op = Op::Divide};
    Operation o{.lhs = lhs, .rhs = c, .op = Op::Minus};

    auto ans = print(o);
    CHECK(ans == "((4 / 2) - 1)");
  }

  SUBCASE("nested lhs,rhs") {
    Operand a = 4, b = 2, c = 6, d = 3,
            lhs = Operation{.lhs = a, .rhs = b, .op = Op::Divide},
            rhs = Operation{.lhs = c, .rhs = d, .op = Op::Divide};
    Operation o{.lhs = lhs, .rhs = rhs, .op = Op::Minus};

    auto ans = print(o);
    CHECK(ans == "((4 / 2) - (6 / 3))");
  }
}
