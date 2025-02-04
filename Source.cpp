#include "raylib.h"
#include<conio.h>
#include<math.h>
const int screenWidth = 1280;
const int screenHeight = 960;
const int maxBullets = 10;
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
    int height=200;
    int width=200;
    bool isFired = false;
    int fireProgress = 0;
};
Bullet bullet_array[maxBullets];   // ye array hai taake zada bullets store ho sakein

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

        player->position.y-=5;
        player->jumpProgress+=5;

        if (player->jumpProgress >= player->MAX_JUMP) {
            
            player->isAscending = false;
            player->isJump = false;
            player->jumpProgress = 0;
        }
     
    }
    else {

        if (player->position.y != 850)
            player->position.y+=5;
    }
}

//ye us true value ke liye work karta hai
void fireHandle(Bullet* bullet) {


    if (bullet->isFired) {

        bullet->position.x +=  5;
        bullet->fireProgress += 5;

        if (bullet->fireProgress >= screenWidth - 200) {
            bullet->isFired = false;
            bullet->fireProgress = 0;
        }

    }

}
// ye function sirf us bullet ko true karta hai
void shootBullet() {

    for (int i = 0; i < maxBullets; i++) {
        if (!bullet_array[i].isFired) {
            bullet_array[i].isFired = true;
            bullet_array[i].fireProgress = 0;
            break;
        }
    }
}                         

int main()
{
    Player player;
    Bullet bullet;


    InitWindow(screenWidth, screenHeight, "METAL SLUG");
    SetTargetFPS(60);

    player.position.x= 5;
    player.position.y = 850;

    player.img = LoadImage("C:\\Users\\Dell\\source\\repos\\METAL SLUG\\x64\\Debug\\player.png");
    ImageResize(&player.img, player.playerWidth, player.playerHeight);
    player.texture = LoadTextureFromImage(player.img);

    Image img1 = LoadImage("C:\\Users\\Dell\\source\\repos\\METAL SLUG\\x64\\Debug\\background.jpg");
    ImageResize(&img1, screenWidth, screenHeight);
    Texture2D backGround = LoadTextureFromImage(img1);

    for (int i = 0; i < maxBullets; i++) {
            bullet_array[i].img = LoadImage("C:\\Users\\Dell\\source\\repos\\METAL SLUG\\x64\\Debug\\bullet.png");
            ImageResize(&bullet_array[i].img, bullet_array[i].width, bullet_array[i].height);
            bullet_array[i].texture = LoadTextureFromImage(bullet_array[i].img);
            bullet_array[i].position.x = player.position.x;
            bullet_array[i].position.y = player.position.y - 50;
    }


    while (!WindowShouldClose())    
    {   
       //update the bullet positions
        for (int i = 0; i < maxBullets; i++) {               

            if (!bullet_array[i].isFired) {
                bullet_array[i].position.x = player.position.x ;
                bullet_array[i].position.y = player.position.y - 50; ;
            }
        }

        if (IsKeyDown(KEY_LEFT))movement(&player, KEY_LEFT);
        if (IsKeyDown(KEY_RIGHT))movement(&player, KEY_RIGHT);
        if (IsKeyDown(KEY_Z) and player.position.y == 850)movement(&player, KEY_Z);

//-------------------------------------------------------------

        // All fire function

        if (IsKeyDown(KEY_X) and coolDown <= 0) {
            shootBullet();
            coolDown = 7;
        }
        coolDown--;
        if (coolDown < 0)
            coolDown = 0;

        for (int i = 0; i < maxBullets; i++)
            fireHandle(&bullet_array[i]);
 //-------------------------------------------------------------


         

        BeginDrawing();


        DrawTexture(backGround,0,0,WHITE);
        ClearBackground(RAYWHITE);  


        for (int i = 0; i < maxBullets; i++) {
            if (bullet_array[i].isFired) {
                DrawTexture(bullet_array[i].texture, bullet_array[i].position.x, bullet_array[i].position.y, WHITE);
            }
        }
       
     
        DrawTexture(player.texture, player.position.x, player.position.y,WHITE);
        
        jumpHandle(&player);
   

        EndDrawing();
    }

    UnloadTexture(backGround);
    UnloadImage(player.img);
    UnloadTexture(player.texture);
    CloseWindow();

    return 0;
}