#include "Laptop.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <algorithm>

// Definisi dari main.cpp asli
#define ONE_BY_ROOT_THREE 0.57735

// Data vertex, normal, dan index sekarang menjadi 'static' 
// di dalam file .cpp ini, hanya bisa diakses oleh kelas Laptop.

// Box vertex co-ordinate vectors.
// MODIFIKASI: Nilai Y diubah dari [-1.0, 1.0] menjadi [0.0, 0.1] 
// agar lebih tipis seperti laptop.
static float vertices[] =
{
    1.0, 0.0, 1.0,  // 0
    1.0, 0.1, 1.0,  // 1
    1.0, 0.1, -1.0, // 2
    1.0, 0.0, -1.0, // 3
    -1.0, 0.0, 1.0, // 4
    -1.0, 0.1, 1.0, // 5
    -1.0, 0.1, -1.0,// 6
    -1.0, 0.0, -1.0 // 7
};

// Vertex indices (Sama seperti aslinya)
static unsigned char stripIndices0[] = { 5, 4, 1, 0, 2, 3, 6, 7, 5, 4 };
static unsigned char stripIndices1[] = { 0, 4, 3, 7 };
static unsigned char stripIndices2[] = { 6, 5, 2, 1 };

// Box vertex normal vectors (Sama seperti aslinya)
// (Ini akan membuat pencahayaan "squashed", tapi sesuai dengan kode asli)
static float normals[] =
{
    ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,
    ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE
};

// Helper function untuk delay (Windows/Unix compatible)
void delayMs(int ms) {
    int start = glutGet(GLUT_ELAPSED_TIME);
    while (glutGet(GLUT_ELAPSED_TIME) - start < ms) {
        // Busy wait - simple but works on all platforms
    }
}

// Implementasi Metode Kelas Laptop

Laptop::Laptop()
{
    // Inisialisasi sudut layar (lid)
    step = 0;
    bIsOpen = false;

    // Inisialisasi bounding box berdasarkan vertices laptop
    minX = -1.0f;
    maxX = 1.0f;
    minY = 0.0f;
    maxY = 0.1f;
    minZ = -1.0f;
    maxZ = 1.0f;
}

void Laptop::animateOpen()
{
    std::cout << "Starting lid open animation..." << std::endl;

    while (step < MAX_STEP) {
        step += ANIMATION_SPEED;
        if (step > MAX_STEP) step = MAX_STEP;

        // Render frame untuk melihat animasi
        glutPostRedisplay();
        glutMainLoopEvent(); // Process events tanpa blocking

        // Delay untuk mengontrol kecepatan animasi
        delayMs(ANIMATION_DELAY);
    }

    bIsOpen = true; // Set status to open
    std::cout << "Lid opened to: " << step << " degrees" << std::endl;
}

void Laptop::animateClose()
{
    std::cout << "Starting lid close animation..." << std::endl;

    while (step > 0) {
        step -= ANIMATION_SPEED;
        if (step < 0) step = 0;

        // Render frame untuk melihat animasi
        glutPostRedisplay();
        glutMainLoopEvent(); // Process events tanpa blocking

        // Delay untuk mengontrol kecepatan animasi
        delayMs(ANIMATION_DELAY);
    }

    bIsOpen = false; // Set status to closed
    std::cout << "Lid closed to: " << step << " degrees" << std::endl;
}

void Laptop::openLid()
{
    // Versi lama untuk keyboard - langsung increment
    if (step < MAX_STEP) step++;
}

void Laptop::closeLid()
{
    // Versi lama untuk keyboard - langsung decrement
    if (step > 0) step--;
}

bool Laptop::isHit(float rayOriginX, float rayOriginY, float rayOriginZ,
    float rayDirX, float rayDirY, float rayDirZ)
{
    // Gunakan static function dari Raycast class
    return Raycast::rayAABBIntersection(
        rayOriginX, rayOriginY, rayOriginZ,
        rayDirX, rayDirY, rayDirZ,
        minX, minY, minZ,
        maxX, maxY, maxZ,
        HITBOX_OFFSET
    );
}

void Laptop::getBoundingBox(float& outMinX, float& outMinY, float& outMinZ,
    float& outMaxX, float& outMaxY, float& outMaxZ) const
{
    outMinX = minX;
    outMinY = minY;
    outMinZ = minZ;
    outMaxX = maxX;
    outMaxY = maxY;
    outMaxZ = maxZ;
}

void Laptop::draw()
{
    // Material property vectors (Diubah menjadi abu-abu)
    float matAmbAndDif[] = { 0.6, 0.6, 0.6, 1.0 };
    float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float matShine[] = { 50.0 };

    // Terapkan material properties untuk laptop
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    // Aktifkan vertex arrays (dipindahkan dari drawScene)
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Tentukan lokasi array
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Gambar 5 sisi dari "base" laptop
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, stripIndices0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, stripIndices1);

    // Gambar "lid" (layar) yang berputar
    glPushMatrix();

    // MODIFIKASI: Translate ke hinge (engsel) baru di Y=0.1
    glTranslatef(0.0, 0.1, -1.0);
    glRotatef((float)step, -1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.1, 1.0);

    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, stripIndices2);

    glPopMatrix();

    // Disable client states (best practice)
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}