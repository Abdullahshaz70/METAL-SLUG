#include "raylib.h"
#include<conio.h>
#include<math.h>
struct Position {
    int x, y;
};
struct Player {
    Position position;
    Texture2D texture;
    Image img;
    int playerWidth = 60;
    int playerHeight = 90;
    float speed = 5.0f;
};
void movement(Player* player, int key)
{
   
    if (key == KEY_A) {
        player->position.x -= player->speed;
    }
    if (key == KEY_D) {
        player->position.x += player->speed;
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
        DrawTexture(player.texture, player.position.x, player.position.y,WHITE);
 
        EndDrawing();
    }
    UnloadTexture(backGround);
    UnloadImage(player.img);
    UnloadTexture(player.texture);
    CloseWindow();

    return 0;
}