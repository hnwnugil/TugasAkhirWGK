#ifndef RAYCAST_H
#define RAYCAST_H

class Raycast
{
public:
    // Static function untuk ray-AABB intersection
    static bool rayAABBIntersection(
        float rayOriginX, float rayOriginY, float rayOriginZ,
        float rayDirX, float rayDirY, float rayDirZ,
        float minX, float minY, float minZ,
        float maxX, float maxY, float maxZ,
        float hitboxOffset = 0.0f
    );

    // Helper function untuk menghitung expanded bounding box
    static void expandBoundingBox(
        float& minX, float& minY, float& minZ,
        float& maxX, float& maxY, float& maxZ,
        float offset
    );

    // Interface untuk object yang bisa di-raycast
    class IRaycastable {
    public:
        virtual ~IRaycastable() = default;
        virtual bool isHit(float rayOriginX, float rayOriginY, float rayOriginZ,
            float rayDirX, float rayDirY, float rayDirZ) = 0;
        virtual void getBoundingBox(float& minX, float& minY, float& minZ,
            float& maxX, float& maxY, float& maxZ) const = 0;
    };
};

#endif // RAYCAST_H

