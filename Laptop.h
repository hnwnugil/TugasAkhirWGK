#ifndef LAPTOP_H
#define LAPTOP_H

#include <GL/glew.h>
#include <GL/freeglut.h>

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

private:
    // Menyimpan sudut bukaan layar (sebelumnya variabel global 'step')
    int step;
};

#endif // LAPTOP_H