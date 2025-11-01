#include "Tv.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

// Definisi proporsi TV
#define TV_WIDTH 3.2f     // dari 1.5f → jadi lebih lebar
#define TV_HEIGHT 1.8f    // dari 0.8f → jadi lebih tinggi
#define TV_DEPTH 0.05f    // tetap tipis
#define FRAME_THICKNESS 0.05f // frame sedikit lebih tebal
#define STAND_HEIGHT 0.3f // stand lebih tinggi
#define STAND_BASE 0.8f   // base stand lebih lebar

float Tv::vertices[] =
{
    // Layar TV (bagian dalam, depan)
    -TV_WIDTH/2 + FRAME_THICKNESS,  TV_HEIGHT/2 - FRAME_THICKNESS, -TV_DEPTH/2, // 0
     TV_WIDTH/2 - FRAME_THICKNESS,  TV_HEIGHT/2 - FRAME_THICKNESS, -TV_DEPTH/2, // 1
     TV_WIDTH/2 - FRAME_THICKNESS, -TV_HEIGHT/2 + FRAME_THICKNESS, -TV_DEPTH/2, // 2
    -TV_WIDTH/2 + FRAME_THICKNESS, -TV_HEIGHT/2 + FRAME_THICKNESS, -TV_DEPTH/2, // 3

    // Frame luar (depan)
    -TV_WIDTH/2,  TV_HEIGHT/2, -TV_DEPTH/2, // 4
     TV_WIDTH/2,  TV_HEIGHT/2, -TV_DEPTH/2, // 5
     TV_WIDTH/2, -TV_HEIGHT/2, -TV_DEPTH/2, // 6
    -TV_WIDTH/2, -TV_HEIGHT/2, -TV_DEPTH/2, // 7

    // Frame belakang (untuk ketebalan)
    -TV_WIDTH/2,  TV_HEIGHT/2, TV_DEPTH/2, // 8
     TV_WIDTH/2,  TV_HEIGHT/2, TV_DEPTH/2, // 9
     TV_WIDTH/2, -TV_HEIGHT/2, TV_DEPTH/2, // 10
    -TV_WIDTH/2, -TV_HEIGHT/2, TV_DEPTH/2, // 11

    // Stand TV (V-shape) — diperbaiki agar selalu menempel di bawah TV
    - STAND_BASE/2, -TV_HEIGHT/2,                    0.0f, // 12 → atas kiri
    STAND_BASE/2, -TV_HEIGHT/2,                    0.0f, // 13 → atas kanan
    0.0f,         -TV_HEIGHT/2 - STAND_HEIGHT,     0.0f  // 14 → bawah tengah
};

float Tv::normals[] =
{
    // Normal untuk layar & frame depan: menghadap ke depan (+Z)
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    // Normal untuk frame belakang: menghadap ke belakang (-Z)
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    // Normal untuk stand (menghadap ke depan)
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

unsigned char Tv::stripIndicesScreen[] = { 0, 1, 3, 2 };

unsigned char Tv::stripIndicesFrame[] = {
    4, 5, 7, 6,   // depan
    8, 9, 11, 10  // belakang
};

unsigned char Tv::stripIndicesStand[] = { 12, 13, 14 };

// Konstruktor
Tv::Tv()
{
    matAmbAndDif[0] = 0.1f; matAmbAndDif[1] = 0.1f; matAmbAndDif[2] = 0.1f; matAmbAndDif[3] = 1.0f;
    matSpec[0] = 0.8f; matSpec[1] = 0.8f; matSpec[2] = 0.8f; matSpec[3] = 1.0f;
    matShine[0] = 100.0f;
}

void Tv::draw()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, Tv::vertices);
    glNormalPointer(GL_FLOAT, 0, Tv::normals);

    // Gambar layar (hitam)
    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, Tv::stripIndicesScreen);

    // Gambar frame depan & belakang
    glColor3f(0.3f, 0.3f, 0.3f);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, Tv::stripIndicesFrame);           // depan
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, &Tv::stripIndicesFrame[4]);      // belakang

    // Gambar stand
    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_BYTE, Tv::stripIndicesStand);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}