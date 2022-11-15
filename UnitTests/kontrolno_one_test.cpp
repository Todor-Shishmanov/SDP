#include "CppUnitTest.h"
#include "../Kontrolni/kontrolno_one.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestOne;

namespace KontrolnoOne
{
	TEST_CLASS(GivenFunctions)
	{
	public:
		
		TEST_METHOD(isDigitCorrect)
		{
			for(char i = '0'; i <= '9'; i++)
				Assert::IsTrue(isDigit(i), L"isDigit does not recognize " + i);
		}

		TEST_METHOD(isDigitIncorrect)
		{
			for (unsigned char i = 0; i < 255; i++) {
				if (i >= '0' && i <= '9')
					continue;
				Assert::IsFalse(isDigit(i), L"isDigit recognizes " + i);
			}
				
		}

		TEST_METHOD(isOperationCorrect)
		{
			Assert::IsTrue(isOperation('+'), L"isOperation does not recognize +");
			Assert::IsTrue(isOperation('-'), L"isOperation does not recognize -");
			Assert::IsTrue(isOperation('/'), L"isOperation does not recognize /");
			Assert::IsTrue(isOperation('*'), L"isOperation does not recognize *");
			Assert::IsTrue(isOperation('^'), L"isOperation does not recognize ^");
		}

		TEST_METHOD(isOperationIncorrect)
		{
			for (unsigned char i = 0; i < 255; i++) {
				if (i == '+' || i == '-' || i == '/' || i == '*' || i == '^')
					continue;
				Assert::IsFalse(isOperation(i), L"isOperation recognizes " + i);
			}
		}

		TEST_METHOD(toDigitCorrect) 
		{
			Assert::AreEqual(0., toDouble('0'), L"Zero");
			Assert::AreEqual(2., toDouble('2'), L"Two");
			Assert::AreEqual(9., toDouble('9'), L"Nine");
		}

		TEST_METHOD(toDigitIncorrect)
		{
			try {
				toDouble('a');
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}

		TEST_METHOD(priorityCorrect) 
		{
			Assert::AreEqual(1u, priority('+'), L"+ priority not 1");
			Assert::AreEqual(1u, priority('-'), L"- priority not 1");
			Assert::AreEqual(2u, priority('/'), L"/ priority not 1");
			Assert::AreEqual(2u, priority('*'), L"* priority not 1");
			Assert::AreEqual(3u, priority('^'), L"^ priority not 1");
		}

		TEST_METHOD(priorityIncorrect)
		{
			try {
				priority('a');
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}

		TEST_METHOD(calculateCorrect)
		{
			Assert::AreEqual(12., calculate('+', 6, 6), L"6+6 != 12");
			Assert::AreEqual(8., calculate('+', 2, 6), L"2+6 != 8");
			Assert::AreEqual(24., calculate('*', 6, 4), L"6*4 != 24");
			Assert::AreEqual(12., calculate('/', 48, 4), L"48/4 != 12");
			Assert::AreEqual(0., calculate('/', 0, 4), L"0/4 != 0");
			Assert::AreEqual(0.5, calculate('/', 2, 4), L"0/4 != 0");
			Assert::AreEqual(100., calculate('^', 10, 2), L"10^2 != 100");
		}

		TEST_METHOD(calculateZeroDivision)
		{
			try {
				calculate('/', 2, 0);
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}

		TEST_METHOD(calculateWrongOperation)
		{
			try {
				calculate('a', 2, 2);
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}
	};

	TEST_CLASS(WritenFunctions)
	{
	public:

		TEST_METHOD(verifyCorrect)
		{
			Assert::IsTrue(verify(""), L"Empty string should be valid");
			Assert::IsTrue(verify("5"), L"Single digit expression should be valid");
			Assert::IsTrue(verify("5+5"),L"5+5 should be valid");
			Assert::IsTrue(verify("5*5+1"), L"5*5+1 should be valid");
			Assert::IsTrue(verify("6^2+2*4"), L"6^2+2*4 should be valid");
			Assert::IsTrue(verify("0/0"), L"0/0 should be valid (as an expression)");
		}
		TEST_METHOD(verifyIncorrect)
		{
			Assert::IsFalse(verify("54"), L"Two or more digits are not allowed");
			Assert::IsFalse(verify(nullptr), L"nullptr should be invalid");
			Assert::IsFalse(verify("5+"), L"Trailing operant should be invalid");
			Assert::IsFalse(verify("5*5+1-"), L"Trailing operant in longer expression should be invalid");
			Assert::IsFalse(verify("6^22+2*4"), L"Two or more digits in longer expression are not allowed");
			Assert::IsFalse(verify("+2-4"), L"Leading operant should be invalid");
			Assert::IsFalse(verify("5  +  5"), L"Whitespace is invalid");
		}
		
		TEST_METHOD(evaluateCorrectly)
		{
			Assert::AreEqual(0., evaluate("")); // empty
			Assert::AreEqual(12., evaluate("1*3+5-3+7")); // standard long
			Assert::AreEqual(257., evaluate("6*4/2+5*7^2")); // respect operation prio (resolved outside the for)
			Assert::AreEqual(254., evaluate("5^3*2-3+7")); // respect operation prio (resolved in the for)
			Assert::AreEqual(0., evaluate("0/9")); // valid operation
		}

		TEST_METHOD(evaluateLeadingOperant)
		{
			try {
				evaluate("+5-4");
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}

		TEST_METHOD(evaluateTrailingOperant)
		{
			try {
				evaluate("6*");
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}

		TEST_METHOD(evaluateZeroDivision)
		{
			try {
				evaluate("7/0");
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}

		TEST_METHOD(evaluateWhitespace)
		{
			try {
				evaluate("6*7 +4");
			}
			catch (const std::invalid_argument&) {
				return; // Pass
			}
			catch (...) {
				Assert::Fail(L"Wrong exception caught");
			}
			Assert::Fail(L"No exception thrown");
		}
	};
}
