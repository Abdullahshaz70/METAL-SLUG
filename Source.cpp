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
 	bool isJump = false;
 	bool isAscending = false;
 	int jumpProgress = 0;
 	int jumpHeight = 5;
 };
 struct Bullet {
 	Position position;
 	char sym = -37;
 	bool isFired = true;
 	int maxDistance = 20;
 	int distanceProgress = 0;
 };
 struct Enemy {
 	Position position;
 	char sym = -37;
 	bool isAlive = false;
 	Position target;
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
 	/*	for (int i = 0; i < 5; i++) {
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
 		}*/
 		if (!player.isJump) {
 			player.isJump = true;
 			player.isAscending = true;
 		}
 
 		break;
 
 	default:
 		break;
 	}
 }
 void fire(Bullet& bullet, Player player) {
 	bullet.isFired = false;
 }
 void handleJump(Player& player) {
 
 	if (player.isJump) {
 
 		gotoRowCol(player.position.x, player.position.y);
 		cout << " ";
 
 		if (player.isAscending) {
 			player.position.x--;
 			player.jumpProgress++;
 
 			if (player.jumpProgress >= player.jumpHeight) {
 				player.isAscending = false;
 			}
 		}
 		else {
 			player.position.x++;
 			player.jumpProgress++;
 
 			if (player.jumpProgress >= player.jumpHeight * 2) {
 				player.isJump = false;
 				player.jumpProgress = 0;
 			}
 		}
 	}
 	gotoRowCol(player.position.x, player.position.y);
 	cout << player.sym;
 }
 void updateEnemy(Enemy& enemy , Player& player , int& i) {
 	//enemy.target = player.position;
 
 	if (!enemy.isAlive) {
 		
 		if (i == 0) {
 		enemy.position.x = 50;
 		enemy.position.y = 60 + rand() % (100 - 60);
 		}
 
 		gotoRowCol(enemy.position.x, enemy.position.y);
 		cout << " ";
 
 		if (player.position.y > enemy.position.y)
 			enemy.position.y++;
 		else
 			enemy.position.y--;
 
 		gotoRowCol(enemy.position.x, enemy.position.y);
 		cout << enemy.sym;
 
 		if (enemy.position.x == player.position.x and enemy.position.y == player.position.y)
 			enemy.isAlive = true;
 
 		i++;
 	}
 
 	
 }
 void updateFire(Bullet& bullet , Player player) {
 
 		gotoRowCol(bullet.position.x, bullet.position.y);
 		cout << " ";
 	if (!bullet.isFired and bullet.distanceProgress< 21) {
 
 		if (bullet.distanceProgress <= bullet.maxDistance) {
 			bullet.position.y++;
 			bullet.distanceProgress++;
 			gotoRowCol(bullet.position.x, bullet.position.y);
 			cout <<bullet.sym;
 		}
 		
 	}
 	else
 	{
 		bullet.distanceProgress = 0;
 		bullet.isFired = true;
 		gotoRowCol(bullet.position.x, bullet.position.y);
 		cout << " ";
 
 	}
 }
 int main() {
 	Player player;
 	Enemy enemyMan;
 	Bullet bullet;
 	gotoRowCol(player.position.x, player.position.y);
 	cout << player.sym;
 	int i = 0;
 	do {
 		if (_kbhit())
 		{
 			char key = _getch(); 
 			movement(player, key);
 			if (key == 32 and bullet.distanceProgress==0) {
 			bullet.position.x = player.position.x;
 			bullet.position.y = player.position.y + 1 ;
 			fire(bullet,player);
 			}
 		}
 		 updateEnemy(enemyMan, player, i);
  		 updateFire(bullet, player);
 		 handleJump(player);
 		 Sleep(SLEEP);
 	}while (true);
 	
 	return 0;
 	
 }
