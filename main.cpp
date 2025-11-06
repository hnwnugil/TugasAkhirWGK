#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Laptop.h" 
#include "Meja.h"   
#include "Tv.h"     
#include "Camera.h"
#include "MejaTv.h"
#include "Lantai.h"
#include "Raycast.h"

static Laptop laptop;
static Camera camera;
static Meja meja;
static Tv tv;
static MejaTv mejaTv;
static Lantai lantai;

void drawCrosshair(); // Deklarasi fungsi untuk menggambar crosshair

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.

    // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);

    // Light property vectors.
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec[] = { 0.5, 0.5, 0.5, 1.0 };
    float lightPos[] = { 0.0, 1.5, 3.0, 1.0 };
    float globAmb[] = { 0.1, 0.1, 0.1, 1.0 };

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
    lantai.draw();

    glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.5f, 0.1f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    laptop.draw();
    glPopMatrix();

    glPushMatrix();
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.25f);
	meja.draw();
	glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 1.0f, -2.0f); 
    glTranslatef(0.0f, -1.2f, 0.0f); 
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    mejaTv.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 1.0f, -2.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    tv.draw();
    glPopMatrix();

    drawCrosshair(); // Gambar crosshair di atas semuanya

    glutSwapBuffers();
}

void drawCrosshair() {
    // Save all OpenGL state that we might modify
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Get current viewport dimensions
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int w = viewport[2];
    int h = viewport[3];

    // Disable all 3D rendering features
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);

    // Save and set up 2D orthographic projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    // Save and reset modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw crosshair
    float centerX = w / 2.0f;
    float centerY = h / 2.0f;
    float crosshairSize = 10.0f;

    // Set crosshair color and line width
    glColor3f(0.0f, 0.0f, 0.0f); // Black crosshair
    glLineWidth(2.0f);

    // Draw the crosshair lines
    glBegin(GL_LINES);
    // Horizontal line
    glVertex2f(centerX - crosshairSize, centerY);
    glVertex2f(centerX + crosshairSize, centerY);
    // Vertical line
    glVertex2f(centerX, centerY - crosshairSize);
    glVertex2f(centerX, centerY + crosshairSize);
    glEnd();

    // Restore matrices
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Restore all OpenGL state
    glPopAttrib();
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

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        std::cout << "Left click detected!" << std::endl;
        
        // Cek apakah kamera melihat laptop
        if (camera.raycast(laptop))
        {
            std::cout << "Hit: Laptop" << std::endl;
            
            // Toggle layar laptop
            laptop.toggleScreen();
            
            glutPostRedisplay(); // Refresh tampilan
        }
        // Cek apakah kamera melihat TV
        else if (camera.raycast(tv))
        {
            std::cout << "Hit: TV" << std::endl;
            
            // Toggle layar TV
            tv.toggleScreen();
            
            glutPostRedisplay(); // Refresh tampilan
        }
        else
        {
            std::cout << "Hit: Nothing" << std::endl;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // Right click to close lid
        if (camera.raycast(laptop))
        {
            if(laptop.getIsOpen() == false)
            { 
                std::cout << ">>> Ray HIT laptop! Opening lid..." << std::endl;
                laptop.animateOpen(); // Gunakan animasi untuk klik
                glutPostRedisplay();
            }
            else
            {
                std::cout << ">>> Ray HIT laptop! Closing lid..." << std::endl;
                laptop.animateClose(); // Gunakan animasi untuk klik
                glutPostRedisplay();
            }
        }
        else
        {
            std::cout << ">>> Ray MISS." << std::endl;
        }
    }
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

void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press right mouse keys to open/close the laptop." << std::endl;
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
	glutSetWindow(glutGetWindow());
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutSetCursor(GLUT_CURSOR_NONE);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}