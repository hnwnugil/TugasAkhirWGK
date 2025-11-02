#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <GL/freeglut.h>
#include "Raycast.h"

class Camera
{
private:
    // Variabel untuk menyimpan posisi, titik lihat, dan vektor 'up'
    float posX, posY, posZ;
    float lookX, lookY, lookZ;
    float upX, upY, upZ;

    // Kecepatan gerak kamera
    float moveSpeed;
    float mouseSense;

    float yaw;   // Rotasi Kiri/Kanan
    float pitch; // Rotasi Atas/Bawah

    // Variabel untuk mouse
    int windowCenterX;
    int windowCenterY;

public:
    // Konstruktor
    Camera();

    // Fungsi untuk menerapkan gluLookAt()
    void look();

    // Fungsi untuk menggerakkan kamera
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void mouseLook(int x, int y);
    void centerMouse();

    void setWindowCenter(int centerX, int centerY)
    {
        windowCenterX = centerX;
        windowCenterY = centerY;
    }

    // Getter functions untuk raycast
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    float getPosZ() { return posZ; }

    float getLookX() { return lookX; }
    float getLookY() { return lookY; }
    float getLookZ() { return lookZ; }

    // Generic raycast function untuk IRaycastable objects
    bool raycast(Raycast::IRaycastable& object);

    // Template function untuk raycast ke berbagai object types
    template<typename T>
    bool raycastTo(T& object) {
        static_assert(std::is_base_of_v<Raycast::IRaycastable, T>,
            "Object must implement IRaycastable interface");
        return raycast(object);
    }

private:
    // Fungsi helper privat untuk mendapatkan vektor arah
    void getForwardVector(float& forwardX, float& forwardZ);
    void getRightVector(float& rightX, float& rightZ);
    void rotateView(float angle);
};

#endif // CAMERA_H