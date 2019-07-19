#ifndef PICTURE_H
#define PICTURE_H

#include "pixel.h"

#include <vector>
#include <iostream>
#include <QString>

class Picture
{
public:
    Picture();
    Picture(int imageWidth,int imageHeight);

    //getters
    int getWidth();
    int getHeight();
    Pixel getPixel(int col,int row);
    Picture getObject(int index);
    int getObjArrSize();

    //setters
    void createPixel(Pixel pixel,int row,int col);
    void setPixel(char RGBGrBw, int newValue, int row, int col);

    //functions
    void toGrayscale();
    void toBW(int thresh);
    void getHistogram();
    int findThreshold();
    void floodFillUntil(int x, int y, int prevC, int newC);
    void createNewImage();
    void dialate(int size);
    void invert();
    void getObjects();
    void close(int size);
    int countObjects();
    void findYellow();
    int getLargestObject();
    void loadMasks();
    Picture getMask(int index);
    int findMatch();
    QString getID(int index);



private:
    Pixel * pixelArray;
    int imageWidth;
    int imageHeight;
    int test;
    std::vector<Picture> masks;
    std::vector<QString> id;
    float histogram[257];
    std::vector<Picture> objectArray;

};

#endif // PICTURE_H
