#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");

    rlImGuiSetup(true);

    Vector2 position = { 100,100 };
    Vector2 position2 = { 100, 100 };
    Vector2 velocity = { 10, 0 };
    Vector2 acceleration = { 0, 50 };
    float maxSpeed = 1000.0f;
    float maxAcceleration = 1000.0f;

    SetTargetFPS(165);

    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        rlImGuiBegin();

        ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
        ImGui::SliderFloat2("velocity", &(velocity.x), -maxSpeed, maxSpeed);
        rlImGuiEnd();

        Vector2 deltaV = acceleration * dt;
        velocity = velocity + deltaV; //px/s/s * s = px/s
        Vector2 displacement = velocity * dt; //px/s * s = px
        position = position + displacement;

        DrawLine()
        
        //position = WraparoundScreen(position);

        DrawCircleV(position, 50, GREEN);
        DrawFPS(10, 10);
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}