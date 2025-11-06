#ifndef MEJA_H
#define MEJA_H

class Meja
{
public:
    Meja();
    void draw();

private:
    static float vertices[];
    static float normals[];
    static unsigned char indicesTable[];

    float matAmbAndDif[4];
    float matSpec[4];
    float matShine[1];

    void drawSupportBar();
    void drawScreen();

};

#endif // MEJA_H