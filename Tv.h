#ifndef TV_H
#define TV_H
#include "Raycast.h"

class Tv : public Raycast::IRaycastable
{
public:
    Tv();
    void draw();
    
    // Raycast hit detection
    bool isHit(float rayOriginX, float rayOriginY, float rayOriginZ,
        float rayDirX, float rayDirY, float rayDirZ) override;
    void getBoundingBox(float& minX, float& minY, float& minZ,
        float& maxX, float& maxY, float& maxZ) const override;
    
    // Toggle layar TV
    void toggleScreen();
    bool getIsScreenOn() const { return bIsScreenOn; }
    
private:
    static float vertices[];
    static float normals[];
    static unsigned char stripIndicesScreen[];
    static unsigned char stripIndicesFrame[];
    static unsigned char stripIndicesStand[];
    
    float matAmbAndDif[4];
    float matSpec[4];
    float matShine[1];
    
    bool bIsScreenOn; // Status layar TV
    
    // Bounding box
    float minX, minY, minZ;
    float maxX, maxY, maxZ;
    
    static constexpr float HITBOX_OFFSET = 0.5f;
};

#endif