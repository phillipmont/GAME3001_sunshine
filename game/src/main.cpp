#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    float playerRotation = 0.0f;
    const float playerWidth = 124.0f;
    const float playerHeight = 135.0f;
    const float playerRotationSpeed = 200.0f;
    Vector2 enemyPosition { 1000, 360 };

    const Rectangle rectangle{ 1000.0f, 500.0f, 160.0f, 90.0f };

    //Load Textures
    Texture2D playerShip = LoadTexture("../game/assets/textures/1B.png");
    Texture2D enemyShip1 = LoadTexture("../game/assets/textures/8.png");


    //Load Audio
    InitAudioDevice();
    Music music = LoadMusicStream("../game/assets/audio/Cyberpunk Moonlight Sonata.mp3");
    PlayMusicStream(music);
    Sound laser = LoadSound("../game/assets/audio/laser.mp3");


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (IsKeyDown(KEY_E))
            playerRotation += playerRotationSpeed * dt;
        if (IsKeyDown(KEY_Q))
            playerRotation -= playerRotationSpeed * dt;
        if (IsKeyDown(KEY_SPACE))
            PlaySound(laser);

        UpdateMusicStream(music);

        const Vector2 playerPosition = GetMousePosition();
        const Vector2 playerSpritePosition { playerPosition.x - (playerWidth * 0.5f), playerPosition.y - (playerHeight * 0.5f) };
        const Rectangle playerRec { playerPosition.x, playerPosition.y, playerWidth, playerHeight };
        const Rectangle playerShipRec { 0, 0, playerWidth, playerHeight };

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Render player
        DrawCircleV(playerPosition, 70, BLUE);
        DrawTexturePro(playerShip, playerShipRec, playerRec, { playerWidth * 0.5f, playerHeight * 0.5f }, playerRotation, BLUE);

        // Render enemies
        DrawCircleV(enemyPosition, 100, RED);
        DrawTextureEx(enemyShip1, enemyPosition, 270.0f, 1, RED);
        enemyPosition.x--;

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}