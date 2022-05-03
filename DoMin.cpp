#include "Header.h"
#include "Console.h"
#include "Funtion.h"

int main()
{
	resizeConsole1(ConsoleWidth, ConsoleHeight);
	SetConsoleTitle(TEXT("Game Minesweeper"));
	
	system("cls");
	Cursor(false);
	music();
	MainLine();
	
	Menu();
	
}

