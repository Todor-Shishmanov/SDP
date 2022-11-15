#include "kontrolno_one.h"
#include <cmath>
#include <stack>

namespace TestOne {
	double calculate(char operation, double left, double right) {
		switch (operation) {
		case('+'): return left + right;
		case('-'): return left - right;
		case('*'): return left * right;
		case('/'): {
			if (right == 0.)
				throw std::invalid_argument("Zero division");
			return left / right;

		}
		case('^'): return std::pow(left, right);
		default: throw std::invalid_argument("No such operation");
		}
	}

	bool verify(const char* expression) {
		if (expression == nullptr)
			return false;
		if (expression[0] == '\0')
			return true;

		bool is_even_index = false;
		for (unsigned i = 0; expression[i] != '\0'; i++) {
			char current_symbol = expression[i];
			is_even_index = !is_even_index;
			if (is_even_index && !isDigit(current_symbol))
				return false;
			if (!is_even_index && !isOperation(current_symbol))
				return false;
		}
		if (!is_even_index)
			return false;
		return true;
	}

	double evaluate(const char* expression) {
		if (!verify(expression))
			throw std::invalid_argument("Not a valid expression");
		if (expression[0] == '\0')
			return 0;
		
		std::stack<char> operation_stack;
		std::stack<double> number_stack;
		number_stack.push(static_cast<double>(toDouble(expression[0])));
		
		// Calculate only when current operation prio is smaller or equal than the last operation prio
		
		for (unsigned i = 1; expression[i] != '\0'; i+=2) {
			char current_operation = expression[i];
			double current_number = toDouble(expression[i + 1]);
			if (!operation_stack.empty()) {
				char last_operation = operation_stack.top();
				while (priority(last_operation) >= priority(current_operation) && !operation_stack.empty()) {
					last_operation = operation_stack.top();
					operation_stack.pop();
					double right = number_stack.top();
					number_stack.pop();
					double left = number_stack.top();
					number_stack.pop();
					number_stack.push(calculate(last_operation, left, right));
				}	
			}
			number_stack.push(current_number);
			operation_stack.push(current_operation);
		}

		// Resulting  stack with only decreasing (starting from the top) priority operation
		while (!operation_stack.empty()) { // Different than the for loop, because priority is reversed
			char operation = operation_stack.top();
			operation_stack.pop();
			double right = number_stack.top();
			number_stack.pop();
			double left = number_stack.top();
			number_stack.pop();
			number_stack.push(calculate(operation, left, right));
		}
		
		return number_stack.top();
	}
}

