#include <iostream>
#include "Stack.hpp"
#include "Calculator.hpp"
#include "GUI.h"

using namespace nStack;
using namespace std;

int main() {
	char Minput = ' ';
	Start_display(Minput);
	Calculator Mcalculator;
	char Minfix[100] = {};
	char Mpostfix[100] = {};
	double Mresult = 0;
	do {
		Start_formula();
		cin.getline(Minfix, 99);
		Mcalculator.Get_post_fix(Minfix, Mpostfix);
		cout << endl;
		cout << "Postfix value is ";
		Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
		cout << Mpostfix << endl << endl;
		Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
		Mresult = Mcalculator.Calculate(Mpostfix);
		cout << "Result is ";
		Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
		cout << Mresult;
		Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));

		memset(Minfix, NULL, 100);
		memset(Mpostfix, NULL, 100);
		Loop_display(Minput);
	} while (Minput != 'c');
}