#include <stdio.h>
#include <raylib.h>

typedef struct {
    int x;
    int y;
} Point;

void DrawPoint(Point *point);

int main() {
    int width = 800;
    int height = 600;
    char title[] = "My Game";
    InitWindow(width, height, title);
    SetTargetFPS(60);

    if (!IsWindowReady()) return 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Point firstpoint = {400,300};
        DrawPoint(&firstpoint); // Draw a point in 2d space
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawPoint(Point *point) {
    const int size = 10;
    DrawRectangle(point->x, point->y, size, size, GREEN);
}
