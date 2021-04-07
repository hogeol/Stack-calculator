#ifndef __CALCULATOR
#define __CALCULATOR
#include "Stack.hpp"

namespace nStack {
		class Calculator
		{
		private:
			char mnumber[11] = { '0','1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };
			enum class sign {
				LEFT_PARENTHESES = '(',
				RIGHT_PARENTHESES = ')',
				MULTIPLY = '*',
				DIVIDE = '/',
				PLUS = '+',
				MINUS = '-',
				SPACE = ' ',
				OPERAND,
				NEGATIVE
			};
		public:
			int Get_priority(char operate, int exist);
			bool Isprior(char operation_1, char operation_2);
			bool Isnum(char sign);
			int Get_next_value(char* postfix, char* value, int& type);
			void Get_post_fix(char* infixValue, char* postfixValue);
			double Calculate(char* postfixvalue);
		};
}
#endif __CALCULATOR
