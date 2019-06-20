#include "pixel.h"

Pixel::Pixel()
{

}

Pixel::Pixel(int R, int G, int B)
{
    this->R = R;
    this->G = G;
    this->B = B;
}

Pixel::Pixel(int BW)
{
    this->BW = BW;
}

int Pixel::getR()
{
    return this->R;
}

int Pixel::getG()
{
    return this->G;
}

int Pixel::getB()
{
    return this->B;
}

int Pixel::getGr()
{
    return this->Gr;
}

int Pixel::getBW()
{
   return this->BW;
}

void Pixel::setR(int R)
{
    this->R = R;
}

void Pixel::setG(int G)
{
    this->G = G;
}

void Pixel::setB(int B)
{
    this->B = B;
}

void Pixel::setGr(int Gr)
{
    this->Gr = Gr;
}

void Pixel::setBW(int BW)
{
    this->BW = BW;
}
