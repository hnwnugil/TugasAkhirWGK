#ifndef TV_H
#define TV_H

class Tv
{
public:
    Tv();
    void draw();

private:
    static float vertices[];
    static float normals[];
    static unsigned char stripIndicesScreen[];
    static unsigned char stripIndicesFrame[];
    static unsigned char stripIndicesStand[];

    float matAmbAndDif[4];
    float matSpec[4];
    float matShine[1];
};

#endif 