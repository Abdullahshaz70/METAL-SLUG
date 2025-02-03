#include "raylib.h"
#include<conio.h>
#include<math.h>

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

void movement(Player* player, int key)
{
   
    if (key == KEY_A) {
        player->position.x -= player->speed;
    }
    if (key == KEY_D) {
        player->position.x += player->speed;
    }
    if (key == KEY_W) {
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

int main()
{
    Player player;
    
    float deltaX = 0;
    float deltaY = 0;
    const int screenWidth = 1280;
    const int screenHeight = 960;
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

    while (!WindowShouldClose())    
    {   
        BeginDrawing();

        DrawTexture(backGround,0,0,WHITE);
        ClearBackground(RAYWHITE);  

        if (IsKeyDown(KEY_A))movement(&player, KEY_A);
        if (IsKeyDown(KEY_D))movement(&player, KEY_D);
        if (IsKeyPressed(KEY_W))movement(&player, KEY_W);
        
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
