#include "raylib.h"
#include<conio.h>
#include<math.h>
#include<iostream>
const int screenWidth = 1280;
const int screenHeight = 960;
const int maxBullets = 30;
const int maxSoldierEnemy = 30;
int coolDown = 0; // ye use kiya taake simultaneously bullets aik sath na nikal ayein , C++ tez hai zara


struct Player {
    Vector2 position;
    Texture2D texture;
    Image img;

    int playerWidth = 60;
    int playerHeight = 90;
    float speed = 5.0f;
    bool isJump = false;
    bool isAscending = false;
    int MAX_JUMP = 65;
    int jumpProgress = 0;
};
struct Bullet {
    Vector2 position = { 50,50 };
    Image img;
    Texture2D texture;
    int height = 200;
    int width = 200;
    bool isFired = false;
    int fireProgress = 0;
    int direction;
    int damage;
    Rectangle collider;
};
Bullet bullet_array[maxBullets];
struct Enemy {
    Vector2 position;
    Texture2D texture;
    Image img;
    float speed = 5.0f;
    int width = 60;
    int height = 90;
    int health;
    bool isAlived;
    Rectangle collider;
};
Enemy soldierEnemy[maxSoldierEnemy];

void movement(Player* player, int key)
{

    if (key == KEY_LEFT) {
        player->position.x -= player->speed;
    }
    if (key == KEY_RIGHT) {
        player->position.x += player->speed;
    }
    if (key == KEY_Z) {
        player->isJump = true;
        player->isAscending = true;

    }

}
void jumpHandle(Player* player) {

    if (player->isJump) {

        player->position.y -= 5;
        player->jumpProgress += 5;

        if (player->jumpProgress >= player->MAX_JUMP) {

            player->isAscending = false;
            player->isJump = false;
            player->jumpProgress = 0;
        }

    }
    else {

        if (player->position.y != 850)
            player->position.y += 5;
    }
}

//ye us true value ke liye work karta hai
void fireHandle(Bullet* bullet) {
    if (bullet->isFired) {
        if (bullet->direction == 0) { // Move right
            bullet->position.x += 5;
            bullet->collider.x += 5;
            bullet->fireProgress += 5;

            if (bullet->fireProgress >= screenWidth) {
                bullet->isFired = false;
                bullet->fireProgress = 0;
            }
        }
        else if (bullet->direction == 1) { // Move up
            bullet->position.y -= 5;
            bullet->collider.y -= 5;

            bullet->fireProgress += 5;

            if (bullet->fireProgress >= screenHeight) {
                bullet->isFired = false;
                bullet->fireProgress = 0;
            }
        }
    }
}
void shootBullet(int direction) {
    for (int i = 0; i < maxBullets; i++) {
        if (!bullet_array[i].isFired) {
            bullet_array[i].isFired = true;
            bullet_array[i].fireProgress = 0;
            bullet_array[i].direction = direction;
            break;
        }
    }
}
void bulletLoading(Player& player)
{
    for (int i = 0; i < maxBullets; i++) {
        bullet_array[i].img = LoadImage("x64/Debug/bullet.png");
        ImageResize(&bullet_array[i].img, bullet_array[i].width, bullet_array[i].height);
        bullet_array[i].texture = LoadTextureFromImage(bullet_array[i].img);
        bullet_array[i].position.x = player.position.x;
        bullet_array[i].position.y = player.position.y - 50;

        bullet_array[i].collider.x = bullet_array[i].position.x;
        bullet_array[i].collider.y = bullet_array[i].position.y;
    }
}
void updateBulletPosition(Player& player)
{
    for (int i = 0; i < maxBullets; i++) {
        if (!bullet_array[i].isFired) {
            bullet_array[i].position.x = player.position.x;
            bullet_array[i].position.y = player.position.y - 50;

            bullet_array[i].collider.x = bullet_array[i].position.x;
            bullet_array[i].collider.y = bullet_array[i].position.y;
        }
    }
}
void fire()
{
    if (IsKeyDown(KEY_UP))
        shootBullet(1);
    else
        shootBullet(0);
}
void fireDraw()
{
    for (int i = 0; i < maxBullets; i++) {
        if (bullet_array[i].isFired) {
            DrawTexture(bullet_array[i].texture, bullet_array[i].position.x, bullet_array[i].position.y, WHITE);

            DrawRectangleLines((bullet_array[i].collider.x + bullet_array[i].width / 2) - 13,
                (bullet_array[i].collider.y + bullet_array[i].height / 2) - 13
                , 13, 13, RED);
        }
    }
}
void updateBullet(Player player) {
    for (int i = 0; i < maxBullets; i++) {
        if (!bullet_array[i].isFired) {
            bullet_array[i].position.x = player.position.x;
            bullet_array[i].position.y = player.position.y - 50;

            bullet_array[i].collider.x = bullet_array[i].position.x;
            bullet_array[i].collider.y = bullet_array[i].position.y;
        }
    }
}

// ye function main menu ke liye hai
bool mainMenu(Texture2D background, Sound Menu)
{
    PlaySound(Menu);
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawText("Metal Slug!", screenWidth / 2 - 150, screenHeight / 2 - 25, 50, DARKGRAY);
        DrawText("Press S to Start or ESC to Exit", screenWidth / 2 - 210, screenHeight / 2 + 50, 24, BLACK);
        EndDrawing();

        if (IsKeyPressed(KEY_S))
            return false;

        if (IsKeyPressed(KEY_ESCAPE))
            return true;

    }
    return true;
}

void initillizePlayer(Player& player) {
    player.position.x = 5;
    player.position.y = 850;
    player.img = LoadImage("x64/Debug/player.png");
    ImageResize(&player.img, player.playerWidth, player.playerHeight);
    player.texture = LoadTextureFromImage(player.img);
}
void initillizeBullet(Player player) {
    for (int i = 0; i < maxBullets; i++) {
        bullet_array[i].img = LoadImage("x64/Debug/bullet.png");
        ImageResize(&bullet_array[i].img, bullet_array[i].width, bullet_array[i].height);
        bullet_array[i].texture = LoadTextureFromImage(bullet_array[i].img);
        bullet_array[i].position.x = player.position.x;
        bullet_array[i].position.y = player.position.y - 50;
        bullet_array[i].damage = 100;

        bullet_array[i].collider.x = bullet_array[i].position.x;
        bullet_array[i].collider.y = bullet_array[i].position.y;
    }

}
void initillizeSoldierEnemy() {

    for (int i = 0; i < maxSoldierEnemy; i++) {
        soldierEnemy[i].img = LoadImage("x64/Debug/enemy.png");
        ImageResize(&soldierEnemy[i].img, soldierEnemy[i].width, soldierEnemy[i].height);
        soldierEnemy[i].texture = LoadTextureFromImage(soldierEnemy[i].img);

        soldierEnemy[i].position = { screenWidth, 857 };
        soldierEnemy[i].health = 100;
        soldierEnemy[i].isAlived = true;
        soldierEnemy[i].speed = GetRandomValue(1, 4);


        soldierEnemy[i].collider.x = soldierEnemy[i].position.x;
        soldierEnemy[i].collider.y = soldierEnemy[i].position.y;
    }

}
void enemyDrawing()
{
    for (int i = 0; i < maxSoldierEnemy; i++) {
        if (soldierEnemy[i].isAlived) {
            DrawTexture(soldierEnemy[i].texture, (int)soldierEnemy[i].position.x, (int)soldierEnemy[i].position.y, WHITE);
            DrawRectangleLines(soldierEnemy[i].collider.x, soldierEnemy[i].collider.y, soldierEnemy[i].width, soldierEnemy[i].height, PURPLE);
        }
    }
}

float spawnTimer = 0.0f;  // Timer to control spawn interval
float spawnInterval = 3.0f; // Time in seconds between each spawn
int currentEnemyIndex = 0;  // To keep track of the next enemy to spawn

void updatePosition(Rectangle& playercollider, Player& player) {
    playercollider.x = player.position.x;
    playercollider.y = player.position.y;
}
void UpdateEnemies() {


    /*  for (int i = 0; i < maxSoldierEnemy ; i++) {
          if (soldierEnemy[i].isAlived  ) {



              if(soldierEnemy[i].position.x > GetRandomValue(screenWidth / 2, screenWidth - 1))
                  soldierEnemy[i].position.x -= soldierEnemy[i].speed;

              soldierEnemy[i].collider.x = soldierEnemy[i].position.x;
              soldierEnemy[i].collider.y = soldierEnemy[i].position.y;


              for (int i = 0; i < maxBullets; i++) {
                  for (int j = 0; j < maxSoldierEnemy; j++) {

                      if (bullet_array[i].collider.x == soldierEnemy[j].collider.x) {

                          soldierEnemy[j].health -= bullet_array[i].damage;

                          if (soldierEnemy[j].health <= 10) {
                              soldierEnemy[j].isAlived = false;
                              bullet_array[i].isFired = false;
                              soldierEnemy[j].collider = { 0 ,0 ,0 ,0 };


                          }
                      }
                  }
              }

          }
      }
 */


    for (int i = 0; i < maxSoldierEnemy; i++) {

        if (!soldierEnemy[i].isAlived && spawnTimer >= spawnInterval && currentEnemyIndex < maxSoldierEnemy) {

            spawnTimer = 0.0f;
            soldierEnemy[i].position = { screenWidth, 857 };
            soldierEnemy[i].health = 100;
            soldierEnemy[i].isAlived = true;
            soldierEnemy[i].speed = GetRandomValue(1, 4);
            currentEnemyIndex++;
        }


        if (soldierEnemy[i].isAlived) {

            if (soldierEnemy[i].position.x > screenWidth / 2) {
                soldierEnemy[i].position.x -= soldierEnemy[i].speed;
            }


            soldierEnemy[i].collider.x = soldierEnemy[i].position.x;
            soldierEnemy[i].collider.y = soldierEnemy[i].position.y;


            for (int j = 0; j < maxBullets; j++) {
                if (bullet_array[j].collider.x == soldierEnemy[i].collider.x) {
                    soldierEnemy[i].health -= bullet_array[j].damage;

                    if (soldierEnemy[i].health <= 10) {
                        soldierEnemy[i].isAlived = false;
                        bullet_array[j].isFired = false;
                        /* soldierEnemy[i].collider = { 0 ,0 ,0 ,0 };*/
                        soldierEnemy[i].collider.x = soldierEnemy[i].position.x;
                        soldierEnemy[i].collider.y = soldierEnemy[i].position.y;
                    }
                }
            }
        }
    }


    spawnTimer += GetFrameTime();
}

void moveOutsideScreen(Player& player)
{
    if (player.position.x < 0)
        player.position.x = 0;
    if (player.position.x > screenWidth - player.playerWidth)
        player.position.x = screenWidth - player.playerWidth;
}
void drawAllTextures(Texture2D backGround, Rectangle playercollider, Player player) {

    ClearBackground(RAYWHITE);
    DrawTexture(backGround, 0, 0, WHITE);
    DrawRectangleLines(playercollider.x, playercollider.y, playercollider.width, playercollider.height, GREEN);
    fireDraw();
    DrawTexture(player.texture, player.position.x, player.position.y, WHITE);
    enemyDrawing();
}

int main()
{
    srand(time(0));
    Player player;
    Enemy enemy;
    Bullet bullet;
    Rectangle playercollider = { player.position.x , player.position.y , player.playerWidth , player.playerHeight };


    InitWindow(screenWidth, screenHeight, "METAL SLUG");
    InitAudioDevice();
    SetTargetFPS(60);

    initillizePlayer(player);

    Image img1 = LoadImage("x64/Debug/background.jpg");
    ImageResize(&img1, screenWidth, screenHeight);
    Texture2D backGround = LoadTextureFromImage(img1);

    Sound menu = LoadSound("x64/Debug/Menu.mp3");
    Sound Stage1 = LoadSound("x64/Debug/Stage1.mp3");

    initillizeBullet(player);

    initillizeSoldierEnemy();

    if (!mainMenu(backGround, menu))
    {
        StopSound(menu);
        PlaySound(Stage1);
        while (!WindowShouldClose())
        {
            //update the bullet positions
            updateBullet(player);

            if (IsKeyDown(KEY_LEFT))movement(&player, KEY_LEFT);
            if (IsKeyDown(KEY_RIGHT))movement(&player, KEY_RIGHT);
            if (IsKeyDown(KEY_Z) and player.position.y == 850)movement(&player, KEY_Z);
            moveOutsideScreen(player);

            //All fire function--------------------------------------------
            if (coolDown > 0) {
                coolDown--;
            }
            if (IsKeyDown(KEY_X) and coolDown <= 0) {
                fire();
                coolDown = 7;
            }
            //-------------------------------------------------------------


            UpdateEnemies();


            updatePosition(playercollider, player);
            //Fire Handling
            for (int i = 0; i < maxBullets; i++) {
                fireHandle(&bullet_array[i]);
            }
            jumpHandle(&player);

            BeginDrawing();
            drawAllTextures(backGround, playercollider, player);
            EndDrawing();
        }
    }

    UnloadTexture(backGround);
    UnloadImage(player.img);
    UnloadTexture(player.texture);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}