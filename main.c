#include <stdio.h>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    float x;
    float y;
    float z;
} Projection;

void DrawPoint(const Point point);
void DrawProj(const Projection pj);
Point ConvertSpace(const Point point); // Returns a point in [Width, Height] space from [0,0]
Point ProjToPoint(const Projection pj);

int main() {
    char title[] = "My Game";
    InitWindow(WIDTH, HEIGHT, title);
    SetTargetFPS(FPS);

    if (!IsWindowReady()) return 0;

    float dz = 1;
    float speed = 0.02;

    Projection myproj1 = {0.5, 0.5, 1};
    Projection myproj2 = {-0.5, 0.5, 1};
    Projection myproj3 = {-0.5, -0.5, 1};
    Projection myproj4 = {0.5, -0.5, 1};
    while (!WindowShouldClose()) {
        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawProj(myproj1);
        DrawProj(myproj2);
        DrawProj(myproj3);
        DrawProj(myproj4);
        EndDrawing();

        // Calculation
        // float dt = GetFrameTime();
        myproj1.z += speed * dz;
        myproj2.z += speed * dz;
        myproj3.z += speed * dz;
        myproj4.z += speed * dz;
    }

    CloseWindow();
    return 0;
}

void DrawPoint(const Point prevpoint) {
    const float size = 20;
    Point point = ConvertSpace(prevpoint);
    DrawRectangle(point.x - size/2, point.y - size/2, size, size, GREEN);
}

void DrawProj(const Projection pj) {
    DrawPoint(ProjToPoint(pj));
}
Point ConvertSpace(const Point point) {
    float x = (((point.x) + 1)/2) * WIDTH;
    float y = (1 - (((point.y) + 1)/2)) * HEIGHT;
    return (Point){x,y};
}

Point ProjToPoint(const Projection pj) {
    if (pj.z == 0) return (Point){pj.x, pj.y};
    return (Point){pj.x / pj.z, pj.y / pj.z};
}
