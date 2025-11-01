#ifndef LANTAI_H
#define LANTAI_H

class Lantai {
public:
    Lantai();
    void draw();

private:
    float tileSize;   // ukuran satu ubin
    int gridCount;    // jumlah ubin per sisi (total = gridCount x gridCount)
};

#endif