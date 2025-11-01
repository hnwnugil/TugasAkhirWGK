#ifndef MEJA_TV_H
#define MEJA_TV_H

class MejaTv {
public:
    MejaTv();
    void draw();

private:
    static float vertices[];
    static float normals[];
    static unsigned char indicesTable[]; 

    float matAmbAndDif[4];
    float matSpec[4];
    float matShine[1];
};

#endif