#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define FPS 60
#define FGCOLOR GREEN

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    float x;
    float y;
    float z;
} Projection;

typedef struct {
    Projection *projs;
    size_t size;
    size_t capacity;
} ProjList;

void DrawPoint(const Point point);
void DrawProj(const Projection pj);
void DrawFace(const Projection *pjs, int *indicies, int facesize, float dz);
void MyDrawLine(const Projection a, const Projection b);

Point ConvertSpace(const Point point); // Returns a point in [Width, Height] space from [0,0]
Point ProjToPoint(const Projection pj);
void RotateProjXZ(Projection *pj, float angle);

Projection TranslateZ(Projection pj, float dz);

ProjList *ProjListInit();

int main() {
    char title[] = "Screen";
    InitWindow(WIDTH, HEIGHT, title);
    SetTargetFPS(FPS);

    if (!IsWindowReady()) return 0;


    Projection projs[] = {
    {0.5  , 0.5, 0.5},
    {-0.5 , 0.5, 0.5},
    {-0.5 , -0.5, 0.5},
    {0.5  , -0.5, 0.5},
    {0.5  , 0.5, -0.5},
    {-0.5 , 0.5, -0.5},
    {-0.5 , -0.5, -0.5},
    {0.5  , -0.5, -0.5}
};
    float dz = 2.0;

    while (!WindowShouldClose()) {
        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 8; ++i) {
            DrawProj(TranslateZ(projs[i], dz));
        }
        DrawFace(projs, (int[]){0,1,2,3}, 4, dz);
        DrawFace(projs, (int[]){4,5,6,7}, 4, dz);
        DrawFace(projs, (int[]){0, 4}, 2, dz);
        DrawFace(projs, (int[]){1, 5}, 2, dz);
        DrawFace(projs, (int[]){2, 6}, 2, dz);
        DrawFace(projs, (int[]){3, 7}, 2, dz);
        EndDrawing();

        // Calculation
        for (int i = 0; i < 8; ++i) {
            RotateProjXZ(&projs[i], 0.25 * PI * GetFrameTime());
            /* projs[i].z += 0.02; */
        }
    }

    CloseWindow();
    return 0;
}

void DrawPoint(const Point prevpoint) {
    const float size = 20;
    Point point = ConvertSpace(prevpoint);
    DrawRectangle(point.x - size/2, point.y - size/2, size, size, FGCOLOR);
}

void DrawProj(const Projection pj) {
    DrawPoint(ProjToPoint(pj));
}

void DrawFace(const Projection *pjs, int *indicies, int facesize, float dz) {
    for (int i = 0; i < facesize; ++i) {
        Projection a = pjs[indicies[i]];
        Projection b = pjs[indicies[(i+1)%facesize]];
        a.z += dz;
        b.z += dz;
        MyDrawLine(a, b);
    }
}

void MyDrawLine(const Projection a, const Projection b) {
    Point start = ConvertSpace(ProjToPoint(a));
    Point end = ConvertSpace(ProjToPoint(b));
    DrawLine(start.x, start.y, end.x, end.y, FGCOLOR);
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

void RotateProjXZ(Projection *pj, float angle) {
    float c = cos(angle);
    float s = sin(angle);

    float newx = pj->x * c - pj->z * s;
    float newz = pj->x * s + pj->z * c;

    pj->x = newx;
    pj->z = newz;
}

Projection TranslateZ(Projection pj, float dz) {
    return (Projection){pj.x, pj.y, pj.z + dz};
}
