#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#define SLEEP 50
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
	int lives = 5;
};
struct Bullet {
	Position position;
	char sym = -37;
};

void movement(Player& player, char key) {
	switch (key) {
	case 'a': // Ascii of it will be 97
		gotoRowCol(player.position.x, player.position.y);
		cout << ' ';
		player.position.y--;
		gotoRowCol(player.position.x, player.position.y);
		cout << player.sym;
		break;
	case 'd':// Ascii of it will be 100
		gotoRowCol(player.position.x, player.position.y);
		cout << ' ';
		player.position.y++;
		gotoRowCol(player.position.x, player.position.y);
		cout << player.sym;
		break;
	case 'w':// Ascii of it will be 119
		for (int i = 0; i < 5; i++) {
			gotoRowCol(player.position.x, player.position.y);
			cout << ' ';
			player.position.x--;
			Sleep(SLEEP);
			gotoRowCol(player.position.x, player.position.y);
			cout << player.sym;
		}
		for (int i = 0; i < 5; i++) {
			gotoRowCol(player.position.x, player.position.y);
			cout << ' ';
			Sleep(SLEEP);
			player.position.x++;
			gotoRowCol(player.position.x, player.position.y);
			cout << player.sym;
		}
		break;

	default:
		break;
	}
}
void fire(Bullet& bullet, int key) {

	switch (key) {
	case 32:// Ascii of spacebar this is the reason on this function we use int key instead of char key
		int i = 0;
		while (i <= 20) {
			gotoRowCol(bullet.position.x, bullet.position.y);
			cout << ' ';
			bullet.position.y++;
			Sleep(SLEEP);
			gotoRowCol(bullet.position.x, bullet.position.y);
			cout << bullet.sym;
			i++;
		}
		gotoRowCol(bullet.position.x, bullet.position.y);
		cout << " ";
		break;
	}

}
void enemy(Player& enemy_man , Player player) {
	
	enemy_man.position.x = 50;
	enemy_man.position.y = 60+rand() % (100-60);

	while (enemy_man.position.y != player.position.y) {
		gotoRowCol(enemy_man.position.x, enemy_man.position.y);
		cout << ' ';
		enemy_man.position.y--;
		gotoRowCol(enemy_man.position.x, enemy_man.position.y);
		cout << enemy_man.sym;
		Sleep(SLEEP);
		if (enemy_man.position.y == player.position.y) {
			player.lives--;
			gotoRowCol(enemy_man.position.x, enemy_man.position.y);
				cout << " ";
				break;
		}
	}
}
int main() {
	Player player;
	Player enemy_man;
	Bullet bullet;
	gotoRowCol(player.position.x, player.position.y);
	cout << player.sym;

	do {
		if (_kbhit())
		{
			char key = _getch(); 
			movement(player, key);
			bullet.position.x = player.position.x;
			bullet.position.y = player.position.y + 1 ;
			fire(bullet, key);
			enemy(enemy_man, player);
		}
	}while (true);
	
	return 0;
	
}



