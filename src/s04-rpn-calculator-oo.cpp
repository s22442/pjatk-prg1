/*
 * A reverse-polish notation calculator.
 */

#include <C:/Users/downl/pjatk-prg1/include/s22442/RPN_calculator.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>


static auto pop_top(std::stack<double>& stack) -> double
{
    if (stack.empty()) {
        throw std::logic_error{"empty stack"};
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}


namespace student { namespace rpn_calculator {
Element::~Element()
{}

Literal::Literal(double const v) : value{v}
{}
auto Literal::evaluate(stack_type& stack) const -> void
{
    stack.push(value);
}

auto Print::evaluate(stack_type& stack) const -> void
{
    std::cout << stack.top() << "\n";
}

auto Addition::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for +"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(a + b);
}

auto Substraction::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for -"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(a - b);
}

auto Multiplication::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for *"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(a * b);
}

auto Division::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for /"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(a / b);
}

auto Integer_division::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for //"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(floor(a / b));
}

auto Modulus::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for %"};
    }

    int const b = pop_top(stack);
    int const a = pop_top(stack);

    stack.push(a % b);
}

auto Exponentiation::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for **"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(pow(a, b));
}

auto Root::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for sqrt"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(pow(a, 1 / b));
}

auto Maximum::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for max"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(std::max(a, b));
}

auto Minimum::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for min"};
    }

    auto const b = pop_top(stack);
    auto const a = pop_top(stack);

    stack.push(std::min(a, b));
}

Calculator::Calculator(stack_type s) : stack{std::move(s)}
{}

auto Calculator::push(std::unique_ptr<Element> op) -> void
{
    ops.push(std::move(op));
}

// FIXME implement Calculator::push(std::string)

auto Calculator::evaluate() -> void
{
    while (not ops.empty()) {
        auto op = std::move(ops.front());
        ops.pop();

        op->evaluate(stack);
    }
}
}}  // namespace student::rpn_calculator


auto make_args(int argc, char* argv[], bool const with_exec = false)
    -> std::vector<std::string>
{
    auto args         = std::vector<std::string>{};
    auto const offset = static_cast<size_t>(not with_exec);
    std::copy_n(argv + offset, argc - offset, std::back_inserter(args));
    return args;
}

auto main(int argc, char* argv[]) -> int
{
    using student::rpn_calculator::Calculator;
    auto calculator = Calculator{};

    for (auto const& each : make_args(argc, argv)) {
        try {
            using student::rpn_calculator::Addition;
            using student::rpn_calculator::Division;
            using student::rpn_calculator::Exponentiation;
            using student::rpn_calculator::Integer_division;
            using student::rpn_calculator::Literal;
            using student::rpn_calculator::Maximum;
            using student::rpn_calculator::Minimum;
            using student::rpn_calculator::Modulus;
            using student::rpn_calculator::Multiplication;
            using student::rpn_calculator::Print;
            using student::rpn_calculator::Root;
            using student::rpn_calculator::Substraction;

            if (each == "p") {
                calculator.push(std::make_unique<Print>());
            } else if (each == "+") {
                calculator.push(std::make_unique<Addition>());
            } else if (each == "-") {
                calculator.push(std::make_unique<Substraction>());
            } else if (each == "*") {
                calculator.push(std::make_unique<Multiplication>());
            } else if (each == "/") {
                calculator.push(std::make_unique<Division>());
            } else if (each == "//") {
                calculator.push(std::make_unique<Integer_division>());
            } else if (each == "%") {
                calculator.push(std::make_unique<Modulus>());
            } else if (each == "**") {
                calculator.push(std::make_unique<Exponentiation>());
            } else if (each == "sqrt") {
                calculator.push(std::make_unique<Root>());
            } else if (each == "max") {
                calculator.push(std::make_unique<Maximum>());
            } else if (each == "min") {
                calculator.push(std::make_unique<Minimum>());
            } else {
                calculator.push(std::make_unique<Literal>(std::stod(each)));
            }
        } catch (std::logic_error const& e) {
            std::cerr << "error: " << each << ": " << e.what() << "\n";
        }
    }

    try {
        calculator.evaluate();
    } catch (std::logic_error const& e) {
        std::cerr << "error: during evaluation: " << e.what() << "\n";
    }

    return 0;
}