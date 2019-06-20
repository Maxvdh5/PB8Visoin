#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
public:
    Pixel();
    Pixel(int R,int G,int B);
    Pixel(int BW);

    int getR();
    int getG();
    int getB();
    int getGr();
    int getBW();

    void setR(int R);
    void setG(int G);
    void setB(int B);
    void setGr(int Gr);
    void setBW(int BW);

private:
    int R;
    int G;
    int B;
    int Gr;
    int BW;
};

#endif // PIXEL_H
