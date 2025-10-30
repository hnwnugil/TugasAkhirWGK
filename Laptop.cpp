#include "Laptop.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

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

// Implementasi Metode Kelas Laptop

Laptop::Laptop()
{
    // Inisialisasi sudut layar (lid)
    step = 0;
}

void Laptop::openLid()
{
    // Batasi bukaan layar hingga 120 derajat
    if (step < 145) step++;
}

void Laptop::closeLid()
{
    if (step > 0) step--;
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