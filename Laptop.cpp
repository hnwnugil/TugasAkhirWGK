#include "Laptop.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <algorithm>

// Definisi dari main.cpp asli
#define ONE_BY_ROOT_THREE 0.57735f

// Data geometri laptop (dibuat static karena hanya digunakan di file ini)
static float vertices[] = {
    1.0f, 0.0f, 1.0f,   // 0
    1.0f, 0.1f, 1.0f,   // 1
    1.0f, 0.1f, -1.0f,  // 2
    1.0f, 0.0f, -1.0f,  // 3
    -1.0f, 0.0f, 1.0f,  // 4
    -1.0f, 0.1f, 1.0f,  // 5
    -1.0f, 0.1f, -1.0f, // 6
    -1.0f, 0.0f, -1.0f  // 7
};

static unsigned char stripIndices0[] = { 5, 4, 1, 0, 2, 3, 6, 7, 5, 4 };
static unsigned char stripIndices1[] = { 0, 4, 3, 7 };
static unsigned char stripIndices2[] = { 6, 5, 2, 1 };

static float normals[] = {
    ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,   // 0
    ONE_BY_ROOT_THREE,  ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,   // 1
    ONE_BY_ROOT_THREE,  ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,  // 2
    ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,  // 3
    -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,  // 4
    -ONE_BY_ROOT_THREE,  ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,  // 5
    -ONE_BY_ROOT_THREE,  ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, // 6
    -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE  // 7
};

// Fungsi delay sederhana (busy wait)
void delayMs(int ms) {
    int start = glutGet(GLUT_ELAPSED_TIME);
    while (glutGet(GLUT_ELAPSED_TIME) - start < ms) {
        // Busy wait
    }
}

// Konstruktor
Laptop::Laptop() {
    step = 0;
    bIsOpen = false;
    bIsScreenOn = false; // Layar mati saat inisialisasi

    // Inisialisasi bounding box
    minX = -1.0f;
    maxX = 1.0f;
    minY = 0.0f;
    maxY = 0.1f;
    minZ = -1.0f;
    maxZ = 1.0f;
}

// Animasi membuka laptop
void Laptop::animateOpen() {
    std::cout << "Starting lid open animation..." << std::endl;
    while (step < MAX_STEP) {
        step += ANIMATION_SPEED;
        if (step > MAX_STEP) step = MAX_STEP;
        glutPostRedisplay();
        glutMainLoopEvent();
        delayMs(ANIMATION_DELAY);
    }
    bIsOpen = true;
    std::cout << "Lid opened to: " << step << " degrees" << std::endl;
}

// Animasi menutup laptop
void Laptop::animateClose() {
    std::cout << "Starting lid close animation..." << std::endl;

    // Matikan layar saat menutup laptop
    if (bIsScreenOn) {
        bIsScreenOn = false;
        std::cout << "Screen turned off (laptop closing)" << std::endl;
    }

    while (step > 0) {
        step -= ANIMATION_SPEED;
        if (step < 0) step = 0;
        glutPostRedisplay();
        glutMainLoopEvent();
        delayMs(ANIMATION_DELAY);
    }
    bIsOpen = false;
    std::cout << "Lid closed to: " << step << " degrees" << std::endl;
}

// Metode manual untuk buka/tutup (tidak digunakan dalam animasi utama, hanya untuk debugging atau kontrol halus)
void Laptop::openLid() {
    if (step < MAX_STEP) step++;
}

void Laptop::closeLid() {
    if (step > 0) step--;
}

// Toggle layar laptop (hanya jika cukup terbuka)
void Laptop::toggleScreen() {
    if (step >= 90) {
        bIsScreenOn = !bIsScreenOn;
        std::cout << "Laptop screen turned " << (bIsScreenOn ? "ON" : "OFF") << std::endl;
    } else {
        std::cout << "Cannot turn on screen - laptop lid is not open enough!" << std::endl;
    }
}

// Deteksi raycast terhadap bounding box dengan offset
bool Laptop::isHit(float rayOriginX, float rayOriginY, float rayOriginZ,
                   float rayDirX, float rayDirY, float rayDirZ) {
    return Raycast::rayAABBIntersection(
        rayOriginX, rayOriginY, rayOriginZ,
        rayDirX, rayDirY, rayDirZ,
        minX, minY, minZ,
        maxX, maxY, maxZ,
        HITBOX_OFFSET
    );
}

// Mengembalikan bounding box
void Laptop::getBoundingBox(float& outMinX, float& outMinY, float& outMinZ,
                            float& outMaxX, float& outMaxY, float& outMaxZ) const {
    outMinX = minX;
    outMinY = minY;
    outMinZ = minZ;
    outMaxX = maxX;
    outMaxY = maxY;
    outMaxZ = maxZ;
}

void Laptop::drawKeyboard()
{
    // Draw a simple keyboard on the base
    float keyboardMaterial[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Dark gray
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, keyboardMaterial);

    // Draw keyboard area
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.7f, 0.11f, 0.2f);   // Front left
    glVertex3f(0.7f, 0.11f, 0.2f);    // Front right
    glVertex3f(0.7f, 0.11f, -0.7f);   // Back right
    glVertex3f(-0.7f, 0.11f, -0.7f);  // Back left
    glEnd();

    // Draw individual keys (simplified as small rectangles)
    float keyMaterial[] = { 0.4f, 0.4f, 0.4f, 1.0f }; // Light gray
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, keyMaterial);

    // Draw a few representative keys
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 10; col++) {
            float x = -0.5f + col * 0.1f;
            float z = 0.0f - row * 0.15f;
            float keySize = 0.04f;

            glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(x - keySize, 0.12f, z - keySize);
            glVertex3f(x + keySize, 0.12f, z - keySize);
            glVertex3f(x + keySize, 0.12f, z + keySize);
            glVertex3f(x - keySize, 0.12f, z + keySize);
            glEnd();
        }
    }
}


// Menggambar laptop
void Laptop::draw() {
    // Properti material
    float matAmbAndDif[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float matSpec[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float matShine[] = { 1.0f };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Gambar base laptop
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, stripIndices0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, stripIndices1);
	drawKeyboard();

    // Gambar lid (layar)
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, -1.0f);
    glRotatef(static_cast<float>(step), -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.1f, 1.0f);

    if (bIsScreenOn) {
        // Layar menyala: gambar emissive (tanpa lighting)
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, stripIndices2);
        glEnable(GL_LIGHTING);
    } else {
        // Layar mati: warna abu-abu gelap kebiruan
        glColor3f(0.1f, 0.1f, 0.1f);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, stripIndices2);
    }

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}