#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <GL/freeglut.h>

class Camera
{
public:
    // Variabel untuk menyimpan posisi, titik lihat, dan vektor 'up'
    float posX, posY, posZ;
    float lookX, lookY, lookZ;
    float upX, upY, upZ;

    // Kecepatan gerak kamera
    float moveSpeed;
    float rotateSpeed;

    // Konstruktor
    Camera();

    // Fungsi untuk menerapkan gluLookAt()
    void look();

    // Fungsi untuk menggerakkan kamera
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();

private:
    // Fungsi helper privat untuk mendapatkan vektor arah
    void getForwardVector(float& fwdX, float& fwdZ);
	void rotateView(float angle);
};

#endif // CAMERA_H
