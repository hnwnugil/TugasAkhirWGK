#ifndef LAPTOP_H
#define LAPTOP_H

class Laptop
{
public:
    // Konstruktor
    Laptop();

    // Menggambar laptop
    void draw();

    // Metode untuk mengontrol bukaan layar
    void openLid();
    void closeLid();

    // Animasi membuka/tutup lid dengan loop
    void animateOpen();
    void animateClose();

    // Raycast hit detection
    bool isHit(float rayOriginX, float rayOriginY, float rayOriginZ,
        float rayDirX, float rayDirY, float rayDirZ);
    void drawBoundingBox();

	bool getIsOpen() const { return bIsOpen; }

private:
	bool bIsOpen; // Status bukaan layar (true = terbuka, false = tertutup)
    
    // Menyimpan sudut bukaan layar (sebelumnya variabel global 'step')
    int step;

    // Bounding box
    float minX, minY, minZ;
    float maxX, maxY, maxZ;

    // Animation properties
    static constexpr int MAX_STEP = 145; // Step maksimum (145 derajat)
    static constexpr int ANIMATION_SPEED = 3; // Kecepatan animasi (step per iterasi)
    static constexpr int ANIMATION_DELAY = 20; // Delay dalam milidetik antar step
};

#endif // LAPTOP_H