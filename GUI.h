#ifndef __GUI
#define __GUI
#include <Windows.h>

enum class Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};
void Text_color(int textColor, int backgroundColor);
void Start_display(char& start);
void Start_formula();
void Flush();

void Text_color(int textColor, int backgroundColor)
{
	int color = textColor + backgroundColor * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void Loop_display(char& end)
{
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "  If you want to calculate other formula, " << std::endl;
	std::cout << "Enter anything ";
	Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
	std::cout << "except 'c'" << std::endl;
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
	std::cout << "  Or you want to exit, ";
	Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
	std::cout << "Enter 'c'" << std::endl;
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
	std::cin >> end;
	Flush();
}
inline void Start_display(char& start)
{
	std::cout << std::endl;
	std::cout << "  If you want to input next formula, ";
	std::cout << "Enter anything ";
	Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
	std::cout << "except 'c'" << std::endl;
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
	std::cout << "  If you want to exit, ";
	Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
	std::cout << "Enter 'c'" << std::endl;
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
	std::cout << ">> ";
	std::cin >> start;
	Flush();
}

inline void Start_formula()
{
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
	std::cout << std::endl;
	std::cout << "  Enter the ";
	Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
	std::cout << "INFIX FORMULA ";
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
	std::cout << "to calculate" << std::endl;
	std::cout << ">>";
}

void Flush()
{
	while (getchar() != '\n');
}

#endif __GUI