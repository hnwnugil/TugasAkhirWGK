#include "Lantai.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

Lantai::Lantai() {
    tileSize = 0.5f;
    gridCount = 30;
}

void Lantai::draw() {
    float halfSize = (tileSize * gridCount) / 2.0f;
    float yFloor = -1.2f;
    float roomHeight = 5.0f;   // tinggi dinding
    float roomDepth = 0.0f;    // kedalaman ruangan (ke belakang)

    glDisable(GL_LIGHTING);
    glColor3f(0.96f, 0.96f, 0.96f); 

    glBegin(GL_QUADS);
    glVertex3f(-halfSize, yFloor, -halfSize);
    glVertex3f( halfSize, yFloor, -halfSize);
    glVertex3f( halfSize, yFloor,  halfSize);
    glVertex3f(-halfSize, yFloor,  halfSize);
    glEnd();

    // Grid
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i <= gridCount; ++i) {
        float x = -halfSize + i * tileSize;
        glVertex3f(x, yFloor, -halfSize);
        glVertex3f(x, yFloor,  halfSize);
    }
    for (int j = 0; j <= gridCount; ++j) {
        float z = -halfSize + j * tileSize;
        glVertex3f(-halfSize, yFloor, z);
        glVertex3f( halfSize, yFloor, z);
    }
    glEnd();

    float backWallZ = -halfSize - roomDepth;
    glColor3f(0.92f, 0.92f, 0.92f); 
    glBegin(GL_QUADS);
        // Belakang
        glVertex3f(-halfSize, yFloor, backWallZ);
        glVertex3f( halfSize, yFloor, backWallZ);
        glVertex3f( halfSize, yFloor + roomHeight, backWallZ);
        glVertex3f(-halfSize, yFloor + roomHeight, backWallZ);
    glEnd();

    glColor3f(0.93f, 0.93f, 0.93f);
    glBegin(GL_QUADS);
        glVertex3f(-halfSize, yFloor,  halfSize);
        glVertex3f(-halfSize, yFloor, backWallZ);
        glVertex3f(-halfSize, yFloor + roomHeight, backWallZ);
        glVertex3f(-halfSize, yFloor + roomHeight,  halfSize);
    glEnd();

    glColor3f(0.93f, 0.93f, 0.93f);
    glBegin(GL_QUADS);
        glVertex3f(halfSize, yFloor, backWallZ);
        glVertex3f(halfSize, yFloor,  halfSize);
        glVertex3f(halfSize, yFloor + roomHeight,  halfSize);
        glVertex3f(halfSize, yFloor + roomHeight, backWallZ);
    glEnd();

    glEnable(GL_LIGHTING);
}