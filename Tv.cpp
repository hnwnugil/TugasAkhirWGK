#include "Tv.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Definisi proporsi TV
#define TV_WIDTH 3.2f
#define TV_HEIGHT 1.8f
#define TV_DEPTH 0.05f
#define FRAME_THICKNESS 0.05f
#define STAND_HEIGHT 0.3f
#define STAND_BASE 0.8f
#define SCREEN_Z ( -TV_DEPTH/2 - 0.001f ) 
#define FRAME_Z ( -TV_DEPTH/2 )

float Tv::vertices[] =
{
    // Layar TV (bagian dalam, depan)
   -TV_WIDTH/2 + FRAME_THICKNESS, TV_HEIGHT/2 - FRAME_THICKNESS, SCREEN_Z, // 0
     TV_WIDTH/2 - FRAME_THICKNESS, TV_HEIGHT/2 - FRAME_THICKNESS, SCREEN_Z, // 1
     TV_WIDTH/2 - FRAME_THICKNESS, -TV_HEIGHT/2 + FRAME_THICKNESS, SCREEN_Z, // 2
    -TV_WIDTH/2 + FRAME_THICKNESS, -TV_HEIGHT/2 + FRAME_THICKNESS, SCREEN_Z, // 3
    
    // Frame luar (depan) - GUNAKAN FRAME_Z (nilai aslinya)
    -TV_WIDTH/2, TV_HEIGHT/2, FRAME_Z, // 4
     TV_WIDTH/2, TV_HEIGHT/2, FRAME_Z, // 5
     TV_WIDTH/2, -TV_HEIGHT/2, FRAME_Z, // 6
    -TV_WIDTH/2, -TV_HEIGHT/2, FRAME_Z, // 7
    
    // Frame belakang
    -TV_WIDTH/2, TV_HEIGHT/2, TV_DEPTH/2, // 8
     TV_WIDTH/2, TV_HEIGHT/2, TV_DEPTH/2, // 9
     TV_WIDTH/2, -TV_HEIGHT/2, TV_DEPTH/2, // 10
    -TV_WIDTH/2, -TV_HEIGHT/2, TV_DEPTH/2, // 11
    
    // Stand TV
    - STAND_BASE/2, -TV_HEIGHT/2, 0.0f, // 12
    STAND_BASE/2, -TV_HEIGHT/2, 0.0f, // 13
    0.0f, -TV_HEIGHT/2 - STAND_HEIGHT, 0.0f // 14
};

float Tv::normals[] =
{
    // Layar (vertices 0-3): normal menghadap ke BELAKANG (ke arah kamera)
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    // Frame depan (vertices 4-7)
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    // Frame belakang (vertices 8-11)
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    // Stand (vertices 12-14)
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
};

unsigned char Tv::stripIndicesScreen[] = { 0, 1, 3, 2 };
unsigned char Tv::stripIndicesFrame[] = {
    4, 5, 7, 6,
    8, 9, 11, 10
};
unsigned char Tv::stripIndicesStand[] = { 12, 13, 14 };

Tv::Tv()
{
    matAmbAndDif[0] = 0.1f; matAmbAndDif[1] = 0.1f; matAmbAndDif[2] = 0.1f; matAmbAndDif[3] = 1.0f;
    matSpec[0] = 0.8f; matSpec[1] = 0.8f; matSpec[2] = 0.8f; matSpec[3] = 1.0f;
    matShine[0] = 100.0f;
    
    bIsScreenOn = false; // TV mati saat inisialisasi
    
    // Setup bounding box berdasarkan vertices TV
    minX = -TV_WIDTH/2;
    maxX = TV_WIDTH/2;
    minY = -TV_HEIGHT/2 - STAND_HEIGHT;
    maxY = TV_HEIGHT/2;
    minZ = -TV_DEPTH/2;
    maxZ = TV_DEPTH/2;
}

void Tv::toggleScreen()
{
    bIsScreenOn = !bIsScreenOn;
    std::cout << "TV screen turned " << (bIsScreenOn ? "ON" : "OFF") << std::endl;
}

bool Tv::isHit(float rayOriginX, float rayOriginY, float rayOriginZ,
    float rayDirX, float rayDirY, float rayDirZ)
{
    return Raycast::rayAABBIntersection(
        rayOriginX, rayOriginY, rayOriginZ,
        rayDirX, rayDirY, rayDirZ,
        minX, minY, minZ,
        maxX, maxY, maxZ,
        HITBOX_OFFSET
    );
}

void Tv::getBoundingBox(float& outMinX, float& outMinY, float& outMinZ,
    float& outMaxX, float& outMaxY, float& outMaxZ) const
{
    outMinX = minX;
    outMinY = minY;
    outMinZ = minZ;
    outMaxX = maxX;
    outMaxY = maxY;
    outMaxZ = maxZ;
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
    
    // Gambar layar - jika nyala, putih terang, jika mati, hitam
    if (bIsScreenOn) {
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f); // Putih terang
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, Tv::stripIndicesScreen);
        // glEnable(GL_LIGHTING);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f); // Hitam
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, Tv::stripIndicesScreen);
    }
    
    // Gambar frame
    glColor3f(0.3f, 0.3f, 0.3f);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, Tv::stripIndicesFrame);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, &Tv::stripIndicesFrame[4]);
    
    // Gambar stand
    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_BYTE, Tv::stripIndicesStand);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}