#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
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

Point ConvertSpace(const Point point);
Point ProjToPoint(const Projection pj);
void RotateProjXZ(Projection *pj, float angle);
void RotateProjYZ(Projection *pj, float angle);

Projection TranslateZ(Projection pj, float dz);
Projection* GenTorus(float R, float r, int numTheta, int numPhi, size_t *outCount);

ProjList *ProjListInit();

int main() {
    char title[] = "Screen";
    InitWindow(WIDTH, HEIGHT, title);
    SetTargetFPS(FPS);

    if (!IsWindowReady()) return 0;


/*******************************/
/*     Projection projs[] = {  */
/*     {0.5f  , 0.5f, 0.5f},   */
/*     {-0.5f , 0.5f, 0.5f},   */
/*     {-0.5f , -0.5f, 0.5f},  */
/*     {0.5f  , -0.5f, 0.5f},  */
/*     {0.5f  , 0.5f, -0.5f},  */
/*     {-0.5f , 0.5f, -0.5f},  */
/*     {-0.5f , -0.5f, -0.5f}, */
/*     {0.5f  , -0.5f, -0.5f}  */
/* };                          */
/*******************************/

    float dz = 2.0f;
    size_t torusSize;
    Projection *mybeautifuldonut = GenTorus(0.75f, 0.2f, 60, 20, &torusSize);
    for (int i = 0; i < torusSize; ++i) {
        RotateProjYZ(&mybeautifuldonut[i],PI/4.0f);
    }


    while (!WindowShouldClose()) {
        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        /* for (int i = 0; i < 8; ++i) { */
        /*     DrawProj(TranslateZ(projs[i], dz)); */
        /* } */
        for (int i = 0; i < torusSize; ++i) {
            DrawProj(TranslateZ(mybeautifuldonut[i], dz));
        }
        /* DrawFace(projs, (int[]){0,1,2,3}, 4, dz); */
        /* DrawFace(projs, (int[]){4,5,6,7}, 4, dz); */
        /* DrawFace(projs, (int[]){0, 4}, 2, dz); */
        /* DrawFace(projs, (int[]){1, 5}, 2, dz); */
        /* DrawFace(projs, (int[]){2, 6}, 2, dz); */
        /* DrawFace(projs, (int[]){3, 7}, 2, dz); */
        EndDrawing();

        float speed = 0.50f;

        // Calculation
        // for (int i = 0; i < 8; ++i) {
            // RotateProjXZ(&projs[i], 0.25f * PI * GetFrameTime());
            /* projs[i].z += 0.02; */
        // }
        for (int i = 0; i < torusSize; ++i) {
            RotateProjXZ(&mybeautifuldonut[i], speed * PI * GetFrameTime());
            RotateProjYZ(&mybeautifuldonut[i], speed * PI * GetFrameTime());
        }
    }

    CloseWindow();
    free(mybeautifuldonut);
    return 0;
}

void DrawPoint(const Point prevpoint) {
    const float size = 10.0f;
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
    float c = cosf(angle);
    float s = sinf(angle);

    float newx = pj->x * c - pj->z * s;
    float newz = pj->x * s + pj->z * c;

    pj->x = newx;
    pj->z = newz;
}
void RotateProjYZ(Projection *pj, float angle) {
    float c = cosf(angle);
    float s = sinf(angle);

    float newy = pj->y * c - pj->z * s;
    float newz = pj->y * s + pj->z * c;

    pj->y = newy;
    pj->z = newz;
}

Projection TranslateZ(Projection pj, float dz) {
    return (Projection){pj.x, pj.y, pj.z + dz};
}

Projection *GenTorus(float R, float r, int numTheta, int numPhi,
                     size_t *outCount) {
    size_t cnt = (size_t)numTheta * numPhi;
    *outCount = cnt;
    Projection *res = malloc(cnt * sizeof(Projection));
    if (!res) {*outCount = 0; return NULL;}
    size_t cursize = 0;
    for (int i = 0; i < numTheta; ++i) {
        float theta = 2.0f * PI * ((float)i/numTheta);
        for (int j = 0; j < numPhi; ++j) {
            float phi = 2.0f * PI * ((float)j / numPhi);
            float ring = R + r * cosf(phi);
            float newx = ring * cosf(theta);
            float newy = r * sinf(phi);
            float newz = ring * sinf(theta);
            res[cursize++] = (Projection){.x = newx, .y = newy, .z = newz};
        }
    }
    return res;
}
