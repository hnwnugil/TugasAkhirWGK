#ifndef CAMERA_H
#define CAMERA_H

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


};

#endif // CAMERA_H
