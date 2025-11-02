#include "Raycast.h"
#include <algorithm>
#include <cmath>

bool Raycast::rayAABBIntersection(
    float rayOriginX, float rayOriginY, float rayOriginZ,
    float rayDirX, float rayDirY, float rayDirZ,
    float minX, float minY, float minZ,
    float maxX, float maxY, float maxZ,
    float hitboxOffset)
{
    // Apply hitbox offset if provided
    if (hitboxOffset > 0.0f) {
        expandBoundingBox(minX, minY, minZ, maxX, maxY, maxZ, hitboxOffset);
    }

    // Ray-AABB intersection using the slab method
    float t_near = -999999.0f; // Nilai sangat kecil
    float t_far = 999999.0f;   // Nilai sangat besar

    // Cek Sumbu X
    if (std::abs(rayDirX) < 0.0001f) {
        // Ray sejajar dengan slab X, cek apakah origin berada di dalam slab
        if (rayOriginX < minX || rayOriginX > maxX) return false;
    }
    else {
        float t1 = (minX - rayOriginX) / rayDirX;
        float t2 = (maxX - rayOriginX) / rayDirX;
        if (t1 > t2) std::swap(t1, t2); // Pastikan t1 <= t2
        t_near = std::max(t_near, t1);
        t_far = std::min(t_far, t2);
        if (t_near > t_far) return false; // Sinar tidak menabrak slab X
    }

    // Cek Sumbu Y
    if (std::abs(rayDirY) < 0.0001f) {
        if (rayOriginY < minY || rayOriginY > maxY) return false;
    }
    else {
        float t1 = (minY - rayOriginY) / rayDirY;
        float t2 = (maxY - rayOriginY) / rayDirY;
        if (t1 > t2) std::swap(t1, t2);
        t_near = std::max(t_near, t1);
        t_far = std::min(t_far, t2);
        if (t_near > t_far) return false; // Sinar tidak menabrak slab Y
    }

    // Cek Sumbu Z
    if (std::abs(rayDirZ) < 0.0001f) {
        if (rayOriginZ < minZ || rayOriginZ > maxZ) return false;
    }
    else {
        float t1 = (minZ - rayOriginZ) / rayDirZ;
        float t2 = (maxZ - rayOriginZ) / rayDirZ;
        if (t1 > t2) std::swap(t1, t2);
        t_near = std::max(t_near, t1);
        t_far = std::min(t_far, t2);
        if (t_near > t_far) return false; // Sinar tidak menabrak slab Z
    }

    // Cek apakah box ada di belakang kita
    if (t_far < 0) return false;

    // Jika semua cek lolos, berarti SINAR MENGENAI BOX
    return true;
}

void Raycast::expandBoundingBox(
    float& minX, float& minY, float& minZ,
    float& maxX, float& maxY, float& maxZ,
    float offset)
{
    minX -= offset;
    minY -= offset;
    minZ -= offset;
    maxX += offset;
    maxY += offset;
    maxZ += offset;
}