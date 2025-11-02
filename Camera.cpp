#include "Camera.h"
#include "Laptop.h" // Include this for the raycast function

#define PI 3.1415926535f

#include <cmath>
#include <GL/freeglut.h>

Camera::Camera() {
    // 1. Atur posisi awal (tampilan depan yang kamu inginkan)
    posX = 0.0f;
    posY = 0.5f;
    posZ = 4.0f;

    // 2. Atur vektor 'up' standar
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;

    // 3. Atur kecepatan
    moveSpeed = 0.1f;
    mouseSense = 0.005f;

    // 4. Inisialisasi sudut (PENTING!)
    // -PI / 2.0f membuat kamera menghadap ke -Z (ke arah scene)
    yaw = -PI / 2.0f;
    pitch = 0.0f; // Lihat lurus ke depan

    // 5. Hitung look vector awal berdasarkan sudut
    lookX = cos(pitch) * cos(yaw);
    lookY = sin(pitch);
    lookZ = cos(pitch) * sin(yaw);
}

// Raycast function - checks if camera is looking at the laptop
bool Camera::raycast(Raycast::IRaycastable& object) {
    return object.isHit(posX, posY, posZ, lookX, lookY, lookZ);
}

// Terapkan transformasi view menggunakan gluLookAt
void Camera::look() {
    // Kita melihat ke titik: (posisi + arah)
    gluLookAt(posX, posY, posZ,                 // Posisi mata (eye)
        posX + lookX, posY + lookY, posZ + lookZ, // Titik yang dilihat (center)
        upX, upY, upZ);                 // Vektor 'up'
}

// --- Fungsi Gerak ---

void Camera::moveForward() {
    // Hitung vektor forward HANYA berdasarkan yaw (di bidang XZ)
    float fwdX = cos(yaw);
    float fwdZ = sin(yaw);

    // Gerakkan HANYA posisi
    posX += fwdX * moveSpeed;
    posZ += fwdZ * moveSpeed;
}

void Camera::moveBackward() {
    // Hitung vektor forward HANYA berdasarkan yaw (di bidang XZ)
    float fwdX = cos(yaw);
    float fwdZ = sin(yaw);

    // Gerakkan HANYA posisi
    posX -= fwdX * moveSpeed;
    posZ -= fwdZ * moveSpeed;
}

void Camera::moveLeft() {
    // Vektor "kanan" adalah (sin(yaw), -cos(yaw))
    // (Ini adalah rotasi 90 derajat dari vektor "forward" (cos(yaw), sin(yaw))
    float rightX = sin(yaw);
    float rightZ = -cos(yaw);

    // Untuk bergerak ke KIRI, kita kurangi vektor "kanan"
    posX += rightX * moveSpeed;
    posZ += rightZ * moveSpeed;
}

void Camera::moveRight() {
    // Vektor "kanan" adalah (sin(yaw), -cos(yaw))
    float rightX = sin(yaw);
    float rightZ = -cos(yaw);

    // Untuk bergerak ke KANAN, kita tambahkan vektor "kanan"
    posX -= rightX * moveSpeed;
    posZ -= rightZ * moveSpeed;
}

void Camera::mouseLook(int x, int y) {
    // Jangan lakukan apa-apa jika mouse ada di tengah
    if (x == windowCenterX && y == windowCenterY) {
        return;
    }

    // 1. Hitung delta (perubahan) mouse
    int deltaX = x - windowCenterX;
    int deltaY = y - windowCenterY;

    // 2. Update sudut Yaw (Kiri/Kanan)
    // (Gunakan += untuk akumulasi, bukan =)
    yaw += deltaX * mouseSense;

    // 3. Update sudut Pitch (Atas/Bawah)
    pitch -= deltaY * mouseSense; // Y dibalik (y=0 ada di atas)

    // 4. Batasi Pitch (±180 derajat)
    // Kita batasi ~89 derajat (atau 1.55 radian) agar tidak terbalik
    float limit = 1.55f; // sedikit di bawah PI/2 (1.57)
    if (pitch > limit) {
        pitch = limit;
    }
    if (pitch < -limit) {
        pitch = -limit;
    }

    // 5. Hitung ulang vektor 'look' berdasarkan sudut baru
    lookX = cos(pitch) * cos(yaw);
    lookY = sin(pitch);
    lookZ = cos(pitch) * sin(yaw);

    // 6. Kembalikan mouse ke tengah!
    centerMouse();
}

void Camera::centerMouse() {
    // Fungsi ini "memaksa" kursor kembali ke tengah layar
    // Ini penting agar rotasi bisa tak terbatas
    glutWarpPointer(windowCenterX, windowCenterY);
}

// Private helper functions (add these if they don't exist)
void Camera::getForwardVector(float& forwardX, float& forwardZ) {
    forwardX = cos(yaw);
    forwardZ = sin(yaw);
}

void Camera::getRightVector(float& rightX, float& rightZ) {
    rightX = sin(yaw);
    rightZ = -cos(yaw);
}

void Camera::rotateView(float angle) {
    yaw += angle;
}