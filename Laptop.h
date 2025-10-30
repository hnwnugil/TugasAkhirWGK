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

private:
    // Menyimpan sudut bukaan layar (sebelumnya variabel global 'step')
    int step;
};

#endif // LAPTOP_H