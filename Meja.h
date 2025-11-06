#ifndef MEJA_H
#define MEJA_H

#include "Light.h"

class Meja
{
public:
    Meja();
    void draw();
    void draw(const Light& light, const Vec3& camPos); // New method with lighting

private:
    static float vertices[];
    static float normals[];
    static unsigned char indicesTable[];

    float matAmbAndDif[4];
    float matSpec[4];
    float matShine[1];

    void drawSupportBar();
    void drawScreen();
    void drawSupportBar(const Light& light, const Vec3& camPos);
    void drawScreen(const Light& light, const Vec3& camPos);
};

#endif // MEJA_H