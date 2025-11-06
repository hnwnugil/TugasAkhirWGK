#include "Meja.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

// Proporsi meja — tebal dan kokoh
#define MEJA_WIDTH 2.0f
#define MEJA_DEPTH 1.2f
#define MEJA_THICK 0.08f   // ketebalan permukaan meja
#define LEG_HEIGHT 0.9f
#define LEG_WIDTH 0.12f    // lebar kaki
#define LEG_DEPTH 0.12f    // kedalaman kaki

float Meja::vertices[] =
{
    // Atas
    -MEJA_WIDTH / 2,  MEJA_THICK / 2, -MEJA_DEPTH / 2, // 0
     MEJA_WIDTH / 2,  MEJA_THICK / 2, -MEJA_DEPTH / 2, // 1
     MEJA_WIDTH / 2,  MEJA_THICK / 2,  MEJA_DEPTH / 2, // 2
    -MEJA_WIDTH / 2,  MEJA_THICK / 2,  MEJA_DEPTH / 2, // 3
    // Bawah
    -MEJA_WIDTH / 2, -MEJA_THICK / 2, -MEJA_DEPTH / 2, // 4
     MEJA_WIDTH / 2, -MEJA_THICK / 2, -MEJA_DEPTH / 2, // 5
     MEJA_WIDTH / 2, -MEJA_THICK / 2,  MEJA_DEPTH / 2, // 6
    -MEJA_WIDTH / 2, -MEJA_THICK / 2,  MEJA_DEPTH / 2  // 7
};

float Meja::normals[] =
{
    // Atas (Y+)
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    // Bawah (Y-)
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    // Depan (Z-)
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    // Belakang (Z+)
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    // Kiri (X-)
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    // Kanan (X+)
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
};

unsigned char Meja::indicesTable[] = {
    // Atas
    0, 1, 2, 3,
    // Bawah
    4, 5, 6, 7,
    // Depan (Z = -MEJA_DEPTH/2)
    0, 1, 5, 4,
    // Belakang (Z = +MEJA_DEPTH/2)
    3, 2, 6, 7,
    // Kiri (X = -MEJA_WIDTH/2)
    0, 4, 7, 3,
    // Kanan (X = +MEJA_WIDTH/2)
    1, 5, 6, 2
};

Meja::Meja()
{
    matAmbAndDif[0] = 0.6f; matAmbAndDif[1] = 0.3f; matAmbAndDif[2] = 0.1f; matAmbAndDif[3] = 1.0f;
    matSpec[0] = 0.3f; matSpec[1] = 0.3f; matSpec[2] = 0.3f; matSpec[3] = 1.0f;
    matShine[0] = 20.0f;
}

// Simple draw method without lighting
void Meja::draw()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Meja::vertices);
    glNormalPointer(GL_FLOAT, 0, Meja::normals);

    // Draw table surfaces
    for (int i = 0; i < 6; ++i) {
        if (i == 0) {
            // Top surface - soft white
            glColor4f(0.98f, 0.98f, 0.98f, 1.0f);
        } else {
            // Other surfaces - brown
            glColor4f(0.6f, 0.3f, 0.1f, 1.0f);
        }
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &Meja::indicesTable[i * 4]);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    float boneWhiteMaterial[] = { 0.96f, 0.96f, 0.86f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, boneWhiteMaterial);

    // Draw legs
    auto drawLeg = [&](float centerX, float topY, float centerZ, float width, float height, float depth) {
        float x1 = centerX - width / 2, x2 = centerX + width / 2;
        float y1 = topY, y2 = topY - height;
        float z1 = centerZ - depth / 2, z2 = centerZ + depth / 2;

        glColor4f(0.96f, 0.96f, 0.86f, 1.0f);
        
        glBegin(GL_QUADS);
        
        // Front face
        glNormal3f(0, 0, 1);
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        // Back face
        glNormal3f(0, 0, -1);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);

        // Left face
        glNormal3f(-1, 0, 0);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z2);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y2, z1);

        // Right face
        glNormal3f(1, 0, 0);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y2, z1);

        // Top face
        glNormal3f(0, 1, 0);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);

        // Bottom face
        glNormal3f(0, -1, 0);
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);
        
        glEnd();
    };

    float topOfLeg = -MEJA_THICK / 2;
    float legW = LEG_WIDTH;
    float legH = LEG_HEIGHT;
    float legD = LEG_DEPTH;

    float frontZ = -MEJA_DEPTH / 2 + legD / 2;
    float backZ = MEJA_DEPTH / 2 - legD / 2;
    float leftX = -MEJA_WIDTH / 2 + legW / 2;
    float rightX = MEJA_WIDTH / 2 - legW / 2;

    drawLeg(leftX, topOfLeg, frontZ, legW, legH, legD);
    drawLeg(rightX, topOfLeg, frontZ, legW, legH, legD);
    drawLeg(leftX, topOfLeg, backZ, legW, legH, legD);
    drawLeg(rightX, topOfLeg, backZ, legW, legH, legD);

    drawSupportBar();
    drawScreen();
}

void Meja::drawSupportBar()
{
    float barHeight = 0.06f;
    float barDepth = 0.08f;
    float barY = -MEJA_THICK / 2 - LEG_HEIGHT / 2;
    float frontZ = -MEJA_DEPTH / 2 + LEG_DEPTH / 2;
    float leftX = -MEJA_WIDTH / 2 + LEG_WIDTH / 2;
    float rightX = MEJA_WIDTH / 2 - LEG_WIDTH / 2;

    float x1 = leftX, x2 = rightX;
    float y1 = barY + barHeight / 2, y2 = barY - barHeight / 2;
    float z1 = frontZ - barDepth / 2, z2 = frontZ + barDepth / 2;

    glColor4f(0.96f, 0.96f, 0.86f, 1.0f);

    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0, 0, 1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    // Back face
    glNormal3f(0, 0, -1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);

    // Top face
    glNormal3f(0, 1, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);

    // Bottom face
    glNormal3f(0, -1, 0);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    // Left face
    glNormal3f(-1, 0, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);

    // Right face
    glNormal3f(1, 0, 0);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);

    glEnd();
}

void Meja::drawScreen()
{
    float supportBarY = -MEJA_THICK / 2 - LEG_HEIGHT / 2;
    float tableBottomY = -MEJA_THICK / 2;
    float frontZ = -MEJA_DEPTH / 2;
    float leftX = -MEJA_WIDTH / 2 + 0.1f;
    float rightX = MEJA_WIDTH / 2 - 0.1f;

    float x1 = leftX, x2 = rightX;
    float y1 = tableBottomY, y2 = supportBarY;
    float z1 = frontZ + 0.1f;

    glColor4f(0.1f, 0.1f, 0.1f, 1.0f);

    glBegin(GL_QUADS);
    
    glNormal3f(0, 0, -1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    glEnd();
}
