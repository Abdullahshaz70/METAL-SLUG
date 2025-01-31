#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>

using namespace std;


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void color(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}
struct Position {
	int x=50, y=50;
};
struct Player {
	Position position;
	char sym = -37;
};

void movement(Player& player, char key) {
	int sleep = 50;
	switch (key) {
	case 'a':
		gotoRowCol(player.position.x, player.position.y);
		cout << ' ';
		player.position.y--;
		gotoRowCol(player.position.x, player.position.y);
		cout << player.sym;
		break;
	case 'd':
		gotoRowCol(player.position.x, player.position.y);
		cout << ' ';
		player.position.y++;
		gotoRowCol(player.position.x, player.position.y);
		cout << player.sym;
		break;
	case 'w':
		for (int i = 0; i < 5; i++) {
			gotoRowCol(player.position.x, player.position.y);
			cout << ' ';
			player.position.x--;
			Sleep(sleep);
			gotoRowCol(player.position.x, player.position.y);
			cout << player.sym;
		}
		for (int i = 0; i < 5; i++) {
			gotoRowCol(player.position.x, player.position.y);
			cout << ' ';
			Sleep(sleep);
			player.position.x++;
			gotoRowCol(player.position.x, player.position.y);
			cout << player.sym;
		}
		break;
	}
}
int main() {
	Player player;
	cout << "hehe" << endl;
	gotoRowCol(player.position.x, player.position.y);
	cout << player.sym;

	do {
		if (_kbhit())
		{
			char key = _getch(); 
			movement(player, key);
		}
	}while (true);
	
	return 0;
	
}