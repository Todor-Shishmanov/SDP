#pragma once
#include <stdexcept>
namespace TestOne {
	inline bool isDigit(char c) {
		if (c < '0' || c > '9')
			return false;
		return true;
	}

	inline double toDouble(char c) {
		if (!isDigit(c))
			throw std::invalid_argument("Trying to convert non-integer character to int");
		int result = c - '0';
		return static_cast<double>(result);
	}

	inline bool isOperation(char c) {
		if (c != '+' && c != '-' && c != '*' && c != '/' && c != '^')
			return false;
		return true;
	}

	inline unsigned priority(char operation) {
		// Not all controll paths return a value
		//if (!isOperation(operation))
		//	throw std::invalid_argument("Invalid operation");

		switch (operation) {
		case('+'):
		case('-'): return 1;
		case('*') :
		case('/') : return 2;
		case('^'): return 3;
		default: throw std::invalid_argument("Invalid operation");
		}
	}

	double calculate(char operation, double left, double right);
	bool verify(const char* expression);
	double evaluate(const char* expression);
}
