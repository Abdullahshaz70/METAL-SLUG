#include "raylib.h"
#include<conio.h>
#include<math.h>
#include<iostream>
const int screenWidth = 1280;
const int screenHeight = 960;

const int maxBullets = 30;
const int maxSoldierEnemy = 30;
int ENEMY = 10;
int coolDown = 0; // ye use kiya taake simultaneously bullets aik sath na nikal ayein , C++ tez hai zara

float spawnTimer = 0.0f;
float spawnInterval = 5.0f;
int currentEnemyIndex = 0;

int animationFrameCounter = 0;
const int animationSpeed = 6;


struct Player {
    Vector2 position;
    Texture2D texture[13];
    Image img[13];

    int playerWidth = 60;
    int playerHeight = 90;
    float speed = 5.0f;
    bool isJump = false;
    bool isAscending = false;
    int MAX_JUMP = 65;
    int jumpProgress = 0;
    int moveProgress = 0;
    bool isMoving = false;
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
Bullet enemyBullet_array[maxBullets];

struct Enemy {
    Vector2 position;
    Texture2D texture;
    Image img;
    float speed = 5.0f;
    int width = 60;
    int height = 90;
    int health;
    bool isAlived;
    int bulletCount = 0;
    Rectangle collider;
};
Enemy soldierEnemy[maxSoldierEnemy];

struct Helicopter {
    Image img;
    Texture2D texture;
    int height = 200;
    int width = 250;
    Vector2 position = { 10 , 50 };
    int health = 100;

};

void initillizePlayer(Player& player) {
    player.position.x = 5;
    player.position.y = 850;
    player.img[0] = LoadImage("x64/Debug/player.png");
    player.img[1] = LoadImage("x64/Debug/player1.png");
    player.img[2] = LoadImage("x64/Debug/player2.png");
    player.img[3] = LoadImage("x64/Debug/player3.png");
    player.img[4] = LoadImage("x64/Debug/player4.png");
    player.img[5] = LoadImage("x64/Debug/player5.png");
    player.img[6] = LoadImage("x64/Debug/player6.png");
    player.img[7] = LoadImage("x64/Debug/player7.png");
    player.img[8] = LoadImage("x64/Debug/player8.png");
    player.img[9] = LoadImage("x64/Debug/player9.png");
    player.img[10] = LoadImage("x64/Debug/player10.png");
    player.img[11] = LoadImage("x64/Debug/player11.png");
    ImageResize(&player.img[0], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[1], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[2], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[3], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[4], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[5], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[6], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[7], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[8], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[9], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[10], player.playerWidth, player.playerHeight);
    ImageResize(&player.img[11], player.playerWidth, player.playerHeight);
    player.texture[0] = LoadTextureFromImage(player.img[0]);
    player.texture[1] = LoadTextureFromImage(player.img[1]);
    player.texture[2] = LoadTextureFromImage(player.img[2]);
    player.texture[3] = LoadTextureFromImage(player.img[3]);
    player.texture[4] = LoadTextureFromImage(player.img[4]);
    player.texture[5] = LoadTextureFromImage(player.img[5]);
    player.texture[6] = LoadTextureFromImage(player.img[6]);
    player.texture[7] = LoadTextureFromImage(player.img[7]);
    player.texture[8] = LoadTextureFromImage(player.img[8]);
    player.texture[9] = LoadTextureFromImage(player.img[9]);
    player.texture[10] = LoadTextureFromImage(player.img[10]);
    player.texture[11] = LoadTextureFromImage(player.img[11]);
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
void initillizeEnemyBullet() {
    for (int i = 0; i < maxBullets; i++) {
        enemyBullet_array[i].img = LoadImage("x64/Debug/bullet.png");
        ImageResize(&enemyBullet_array[i].img, enemyBullet_array[i].width, enemyBullet_array[i].height);
        enemyBullet_array[i].texture = LoadTextureFromImage(bullet_array[i].img);
        enemyBullet_array[i].position.x = soldierEnemy[i].position.x;
        enemyBullet_array[i].position.y = soldierEnemy[i].position.y - 50;
        enemyBullet_array[i].damage = 100;

        enemyBullet_array[i].collider.x = enemyBullet_array[i].position.x;
        enemyBullet_array[i].collider.y = enemyBullet_array[i].position.y;
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
void initillizeHelicopter(Helicopter& helicopter) {

    helicopter.img = LoadImage("x64/Debug/helicopter.png");
    ImageResize(&helicopter.img, helicopter.width, helicopter.height);
    helicopter.texture = LoadTextureFromImage(helicopter.img);

}

void fireUpdate(Bullet* bullet) {
    if (bullet->isFired) {
        if (bullet->direction == 0) {
            bullet->position.x += 5;
            bullet->collider.x += 5;
            bullet->fireProgress += 5;

            if (bullet->fireProgress >= screenWidth) {
                bullet->isFired = false;
                bullet->fireProgress = 0;
            }
        }
        else if (bullet->direction == 1) {
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
void EnemyfireUpdate(Bullet* bullet) {

    if (bullet->isFired) {   
            bullet->position.x -= 5;
            bullet->collider.x = bullet->position.x;
            bullet->fireProgress -= 5;

            bullet->collider.y = bullet->position.y;

            if (bullet->fireProgress <= 0) {
                bullet->isFired = false;
                bullet->fireProgress = 0;
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
void shootBulletEnemy() {
    for (int i = 0; i < maxBullets; i++) {

        if ((soldierEnemy[i].position.x >= screenWidth / 2 and soldierEnemy[i].position.x < 3*screenWidth / 4)) {

            if (!enemyBullet_array[i].isFired) {
                enemyBullet_array[i].isFired = true;
                enemyBullet_array[i].fireProgress = soldierEnemy[i].position.x;
                break;
            }
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
            DrawRectangleLines((bullet_array[i].collider.x + bullet_array[i].width / 2) - 13, (bullet_array[i].collider.y + bullet_array[i].height / 2) - 13, 13, 13, RED);
        }
    }
}

void enemyfireDraw()
{
    for (int i = 0; i < maxBullets; i++) {
        if (enemyBullet_array[i].isFired) {
            DrawTexture(enemyBullet_array[i].texture, enemyBullet_array[i].position.x, enemyBullet_array[i].position.y, WHITE);
            DrawRectangleLines((enemyBullet_array[i].collider.x + enemyBullet_array[i].width / 2) - 13, (enemyBullet_array[i].collider.y + enemyBullet_array[i].height / 2) - 13, 13, 13, GREEN);
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
void updateBulletEnemy() {
    for (int i = 0; i < maxBullets; i++) {
        if (!enemyBullet_array[i].isFired) {
            enemyBullet_array[i].position.x = soldierEnemy[i].position.x;
            enemyBullet_array[i].position.y = soldierEnemy[i].position.y - 50;

            enemyBullet_array[i].collider.x = bullet_array[i].position.x;
            enemyBullet_array[i].collider.y = bullet_array[i].position.y;
        }
    }
}

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


bool movement(Player* player, int key)
{

    bool moved = false;
    player->isMoving = false;
    if (key == KEY_LEFT) {
        player->position.x -= player->speed;
        moved = true;
        player->isMoving = true;

    }
    else if (key == KEY_RIGHT) {
        player->position.x += player->speed;
        moved = true;
        player->isMoving = true;
    }
    else if (key == KEY_Z) {
        player->isJump = true;
        player->isAscending = true;
    }

    return moved;
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
void updatePosition(Rectangle& playercollider, Player& player) {
    playercollider.x = player.position.x;
    playercollider.y = player.position.y;
}
void updatePlayerAnimation(Player& player) {
    animationFrameCounter++;
    if (player.isMoving)
    {
        if (animationFrameCounter >= animationSpeed) {
            player.moveProgress++;
            if (player.moveProgress > 11)
                player.moveProgress = 0;
            animationFrameCounter = 0;
        }
        player.isMoving = false;
    }
    else
    {
        player.moveProgress = 0;
        animationFrameCounter = 0;
    }
}

void moveOutsideScreen(Player& player)
{
    if (player.position.x < 0)
        player.position.x = 0;
    if (player.position.x > screenWidth - player.playerWidth)
        player.position.x = screenWidth - player.playerWidth;

    for (int i = 0; i < maxBullets; i++)
    {
        if (bullet_array[i].position.x > screenWidth)
            bullet_array[i].isFired = false;

        if (enemyBullet_array[i].position.x == 0)
            enemyBullet_array[i].isFired = false;

    }

}


void UpdateEnemies() {


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

            if (soldierEnemy[i].position.x >= screenWidth / 2) 
                soldierEnemy[i].position.x -= soldierEnemy[i].speed;
            


            soldierEnemy[i].collider.x = soldierEnemy[i].position.x;
            soldierEnemy[i].collider.y = soldierEnemy[i].position.y;


            for (int j = 0; j < maxBullets; j++) {
                if (bullet_array[j].collider.x == soldierEnemy[i].collider.x) {
                    soldierEnemy[i].health -= bullet_array[j].damage;

                    if (soldierEnemy[i].health <= 10) {
                        soldierEnemy[i].isAlived = false;
                        bullet_array[j].isFired = false;
                        ENEMY--;
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



void drawAllTextures(Texture2D backGround, Rectangle playercollider ,
    Rectangle helicoptercollider , Helicopter helicopter,Player& player) {

    ClearBackground(RAYWHITE);
    DrawTexture(backGround, 0, 0, WHITE);
    DrawRectangleLines(playercollider.x, playercollider.y, playercollider.width, playercollider.height, GREEN);
    fireDraw();
    enemyDrawing();
    DrawRectangleLines(helicoptercollider.x, helicoptercollider.y, helicoptercollider.width, helicoptercollider.height, GREEN);

    if (ENEMY <= 0)
        DrawTexture(helicopter.texture, helicopter.position.x, helicopter.position.y, WHITE);

}


int main()
{
    srand(time(0));
    Player player;
    Enemy enemy;
    Bullet bullet;
    Helicopter helicopter;

    Rectangle playercollider = { player.position.x , player.position.y , player.playerWidth , player.playerHeight };
    Rectangle helicoptercollider = { helicopter.position.x , helicopter.position.y , helicopter.width , helicopter.height };

    InitWindow(screenWidth, screenHeight, "METAL SLUG");
    InitAudioDevice();
    SetTargetFPS(60);

    initillizePlayer(player);
    initillizeHelicopter(helicopter);
    initillizeBullet(player);
    initillizeSoldierEnemy();
    initillizeEnemyBullet();

    Image img1 = LoadImage("x64/Debug/background.jpg");
    ImageResize(&img1, screenWidth, screenHeight);
    Texture2D backGround = LoadTextureFromImage(img1);


    Sound menu = LoadSound("x64/Debug/Menu.mp3");
    Sound Stage1 = LoadSound("x64/Debug/Stage1.mp3");

    if (!mainMenu(backGround, menu))
    {
        StopSound(menu);
        PlaySound(Stage1);
        while (!WindowShouldClose())
        {


            if (IsKeyDown(KEY_LEFT) and !movement(&player, KEY_LEFT))
                player.moveProgress = 0;
            if (IsKeyDown(KEY_RIGHT) and !movement(&player, KEY_RIGHT))
                player.moveProgress = 0;
            if (IsKeyDown(KEY_Z) and player.position.y == 850)
                movement(&player, KEY_Z);

            moveOutsideScreen(player);


            if (coolDown > 0)
                coolDown--;
            if (IsKeyDown(KEY_X) and coolDown <= 0) {
                fire();
                coolDown = 6;
            }
            else
                player.isShooting = false;
          
            shootBulletEnemy();
        

            UpdateEnemies();
            updatePosition(playercollider, player);
          
            updateBullet(player);
            updateBulletEnemy();
         


            updatePlayerAnimation(player);
            jumpHandle(&player);

            for (int i = 0; i < maxBullets; i++) 
                fireUpdate(&bullet_array[i]);
         
            for (int i = 0; i < maxBullets; i++)
                EnemyfireUpdate(&enemyBullet_array[i]);

            if (player.moveProgress > 12)
                player.moveProgress = 1;

          

            BeginDrawing();

            drawAllTextures(backGround, playercollider, helicoptercollider, helicopter);
            DrawTexture(player.texture[player.moveProgress], player.position.x, player.position.y, WHITE);
         
           
            EndDrawing();


        }
    }

    UnloadTexture(backGround);
    UnloadImage(player.img[0]);
    UnloadTexture(player.texture[0]);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}