#include "Camera.h"

Camera::Camera() {
    // Posisi awal kamera (dari gluLookAt asli)
    posX = 0.0f;
    posY = 0.0f;
    posZ = 3.0f;

    // Titik yang dilihat kamera (dari gluLookAt asli)
    lookX = 0.0f;
    lookY = 0.0f;
    lookZ = 0.0f;

    // Vektor 'up' standar
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;

    // Atur kecepatan gerak
    moveSpeed = 0.1f;
	rotateSpeed = 0.05f;
}

// Terapkan transformasi view menggunakan gluLookAt
void Camera::look() {
    gluLookAt(posX, posY, posZ,   // Posisi mata (eye)
        lookX, lookY, lookZ,   // Titik yang dilihat (center)
        upX, upY, upZ);      // Vektor 'up'
}

// --- Fungsi Helper ---

// Menghitung vektor 'forward' (di bidang XZ)
void Camera::getForwardVector(float& fwdX, float& fwdZ) {
    fwdX = lookX - posX;
    fwdZ = lookZ - posZ;
    // Normalisasi vektor
    float len = sqrt(fwdX * fwdX + fwdZ * fwdZ);
    if (len != 0) { // Hindari pembagian dengan nol
        fwdX /= len;
        fwdZ /= len;
    }
}

void Camera::rotateView(float angle) {
    // 1. Dapatkan vektor dari 'eye' ke 'lookAt'
    float vecX = lookX - posX;
    float vecZ = lookZ - posZ;

    // 2. Terapkan rumus rotasi 2D
    // x' = x*cos(a) - z*sin(a)
    // z' = x*sin(a) + z*cos(a)
    float rotatedX = vecX * cos(angle) - vecZ * sin(angle);
    float rotatedZ = vecX * sin(angle) + vecZ * cos(angle);

    // 3. Setel 'lookAt' baru dengan menambahkan kembali posisi 'eye'
    lookX = posX + rotatedX;
    lookZ = posZ + rotatedZ;
}

// --- Fungsi Gerak ---

void Camera::moveForward() {
    float fwdX, fwdZ;
    getForwardVector(fwdX, fwdZ);

    // Gerakkan posisi dan titik lihat
    posX += fwdX * moveSpeed;
    posZ += fwdZ * moveSpeed;
    lookX += fwdX * moveSpeed;
    lookZ += fwdZ * moveSpeed;
}

void Camera::moveBackward() {
    float fwdX, fwdZ;
    getForwardVector(fwdX, fwdZ);

    posX -= fwdX * moveSpeed;
    posZ -= fwdZ * moveSpeed;
    lookX -= fwdX * moveSpeed;
    lookZ -= fwdZ * moveSpeed;
}

void Camera::turnLeft() {
    rotateView(rotateSpeed);
}
void Camera::turnRight() {
    rotateView(-rotateSpeed);
}