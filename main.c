#include <stdio.h>
#include <raylib.h>

int main() {
    int width = 800;
    int height = 600;
    char title[] = "My Game";
    InitWindow(width, height, title);
    SetTargetFPS(60);
    printf("Initializing loop\n");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("TEST", 10, 10, 20, DARKGRAY);
        EndDrawing();

    }
    printf("Closing loop\n");
    CloseWindow();
    return 0;
}
