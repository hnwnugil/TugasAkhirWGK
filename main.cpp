#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Laptop.h" 
#include "Meja.h"   
#include "Tv.h"     
#include "Camera.h"
#include "MejaTv.h"

static Laptop laptop;
static Camera camera;
static Tv tv;
static MejaTv mejaTv;

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

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.look();

    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, 0.0f);
    laptop.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 1.0f, -2.0f); 
    glTranslatef(0.0f, -1.2f, 0.0f); 
    mejaTv.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 1.0f, -2.0f);
    tv.draw();
    glPopMatrix();

    glutSwapBuffers();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);

	camera.setWindowCenter(w / 2, h / 2);
    camera.centerMouse();
}

void mouseMove(int x, int y) {
    camera.mouseLook(x, y);
    glutPostRedisplay(); // Minta gambar ulang setelah mouse bergerak
}

void keyInput(unsigned char key, int x, int y)
{
    switch (tolower(key))
    {
    case 27:
        exit(0);
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW); // Tampilkan kursor lagi
        exit(0);
        break;
    case 'w':
        camera.moveForward();
        break;
    case 's':
        camera.moveBackward();
        break;
    case 'a':
        camera.moveLeft();
        break;
    case 'd':
        camera.moveRight();
        break;
    default:
        break;
    }
	glutPostRedisplay();
}

// Callback routine for non-ASCII key entry
void specialKeyInput(int key, int x, int y)
{
    // MODIFIKASI: Panggil metode dari objek laptop
    if (key == GLUT_KEY_UP) laptop.openLid();
    if (key == GLUT_KEY_DOWN) laptop.closeLid();

    glutPostRedisplay();
}

void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press up/down arrow keys to open/close the laptop." << std::endl;
    std::cout << "Press WASD keys to move the camera." << std::endl;
    std::cout << "Move the mouse to look around." << std::endl;
}

int main(int argc, char** argv)
{
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 100);
    glutCreateWindow("Tugas Akhir");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutPassiveMotionFunc(mouseMove);
    glutSetCursor(GLUT_CURSOR_NONE);
	

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}