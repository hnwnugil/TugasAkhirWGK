#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Laptop.h" // Sertakan kelas baru
#include "Meja.h"   // (Seperti di kode asli)
#include "Tv.h"     // (Seperti di kode asli)

// --- SEMUA GLOBAL TERKAIT KOTAK DIHAPUS ---
// (step, vertices, normals, stripIndices)

// Buat instance global dari Laptop
static Laptop laptop;

// Initialization routine (Tidak berubah)
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.

    // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);

    // Light property vectors.
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos[] = { 0.0, 1.5, 3.0, 1.0 };
    float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

    // Light properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0); // Enable particular light source.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.
}

// Drawing routine
void drawScene(void)
{
    // --- SEMUA KODE GAMBAR BOLA DAN KOTAK DIHAPUS ---

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Posisikan kamera (Sama seperti aslinya)
    gluLookAt(0.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Gambar laptop
    laptop.draw();

    glutSwapBuffers();
}

// OpenGL window reshape routine (Tidak berubah)
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine (Tidak berubah)
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

// Callback routine for non-ASCII key entry
void specialKeyInput(int key, int x, int y)
{
    // MODIFIKASI: Panggil metode dari objek laptop
    if (key == GLUT_KEY_UP) laptop.openLid();
    if (key == GLUT_KEY_DOWN) laptop.closeLid();

    glutPostRedisplay();
}

// Routine to output interaction instructions (Tidak berubah)
void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press up/down arrow keys to open/close the laptop." << std::endl;
}

// Main routine (Tidak berubah)
int main(int argc, char** argv)
{
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tugas Akhir"); // Mengganti nama window
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}