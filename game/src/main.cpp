#include "rlImGui.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetWindowTitle("Space Defender 3000"); //Set custom window title. Used for customizing the game window.
    Image icon = LoadImageFromTexture(LoadTexture("../game/assets/textures/1B.png"));
    SetWindowIcon(icon); //Set custom window icon. Used for customizing the game window.
    SetTargetFPS(60);

    //Background
    Vector2 BgPosition{ 0.0f, 0.0f };
    const Rectangle BgSize{ 0.0f, 0.0f, 1024.0f, 1024.0f };
    const Rectangle BgRec{ 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Player
    Vector2 playerSize{ 124.0f, 135.0f };
    const Rectangle playerShipRec{ 0.0f, 0.0f, playerSize.x, playerSize.y };
    const float playerRotationSpeed = 200.0f;
    float playerRotation = 0.0f;

    //Enemies
    Vector2 enemyPosition{ 1000.0f, 360.0f };
    Vector2 enemyShipSize{ 182.0f, 232.0f };
    const Rectangle enemyShipRec{ 0.0f, 0.0f, 182.0f, 232.0f };
    Color enemyColor{ 240, 31, 55, 255 };


    //Load Textures
    Texture2D backgroundTex = LoadTexture("../game/assets/textures/bg_space.png"); //Load texture from file. Used to load textures into memory before drawing.
    Texture2D playerShipTex = LoadTexture("../game/assets/textures/1B.png");
    Texture2D enemyShip1Tex = LoadTexture("../game/assets/textures/8.png");


    //Load Audio
    InitAudioDevice(); //Initialize audio device. Needed to play music and sounds.
    Music music = LoadMusicStream("../game/assets/audio/Cyberpunk Moonlight Sonata.mp3"); //Function #4: Load music from file. Must be loaded into memory to play.
    PlayMusicStream(music); //Start playing loaded music. 
    Sound laser = LoadSound("../game/assets/audio/laser.mp3"); //Load sound effect from file. Used to load sounds into memory.


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (IsKeyDown(KEY_E))
            playerRotation += playerRotationSpeed * dt;
        if (IsKeyDown(KEY_Q))
            playerRotation -= playerRotationSpeed * dt;
        if (IsKeyDown(KEY_SPACE))
            PlaySound(laser); //Play the "laser" sound effect when spacebar is pressed.

        UpdateMusicStream(music); //Updates buffers for music streaming. Needed for continuous music playback.

        const Vector2 mousePosition = GetMousePosition(); //Get mouse position coordinates (x,y). Needed for mouse inputs.
        const Vector2 playerSpritePosition{ mousePosition.x - (playerSize.x * 0.5f), mousePosition.y - (playerSize.y * 0.5f) };
        const Rectangle playerRec{ mousePosition.x, mousePosition.y, playerSize.x, playerSize.y };
        const Rectangle enemy1Rec{ 1000, 360, 182, 232 };

        //Collison Detection
        bool isColliding = false;
        isColliding = CheckCollisionCircles(mousePosition, 70, enemyPosition, 120); //Checks for collison between 2 circles. Useful interaction between game objects.
        
        if (isColliding)
            enemyColor = { 255, 255, 0, 255 };
        else
            enemyColor = { 240, 31, 55, 255 };

        //****DRAW****

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexturePro(backgroundTex, BgSize, BgRec, { BgSize.x * 0.5f, BgSize.y * 0.5f }, 0.0f, WHITE); //Draw a loaded texture on the screen. Used to draw game assets.

        //Draw player
        DrawCircleV(mousePosition, 70, BLUE); //Draw a circle on the screen.
        DrawTexturePro(playerShipTex, playerShipRec, playerRec, { playerSize.x * 0.5f, playerSize.y * 0.5f }, playerRotation, WHITE);

        //Draw enemies
        DrawCircleV(enemyPosition, 120, enemyColor);
        DrawTexturePro(enemyShip1Tex, enemyShipRec, enemy1Rec, { enemyShipSize.x * 0.5f, enemyShipSize.y * 0.5f }, 0, WHITE);
  
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}