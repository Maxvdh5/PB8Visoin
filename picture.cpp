#include "picture.h"

#include <math.h>

Picture::Picture()
{

}

Picture::Picture(int imageWidth, int imageHeight)
{
    this->pixelArray = new Pixel[imageWidth*imageHeight];
    this->imageHeight = imageHeight;
    this->imageWidth = imageWidth;
}

int Picture::getWidth()
{
    return this->imageWidth;
}

int Picture::getHeight()
{
    return this->imageHeight;
}

Pixel Picture::getPixel(int col, int row)
{
    return pixelArray[row*imageHeight+col];
}

Picture Picture::getObject(int index)
{
    return objectArray[index];
}

void Picture::createPixel(Pixel pixel, int row, int col)
{
    pixelArray[row*imageHeight+col] = pixel;
}

void Picture::setPixel(char RGBGrBw, int newValue, int row, int col)
{
    switch(RGBGrBw){
    case 'R' : pixelArray[row*imageHeight+col].setR(newValue); break;
    case 'G' : pixelArray[row*imageHeight+col].setG(newValue); break;
    case 'B' : pixelArray[row*imageHeight+col].setB(newValue); break;
    case 'r' : pixelArray[row*imageHeight+col].setGr(newValue); break;
    case 'w' : pixelArray[row*imageHeight+col].setBW(newValue); break;
    default: break;
    }
}


void Picture::toGrayscale()
{
    for ( int row = 0; row < this->imageWidth ; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            this->setPixel('r',(this->getPixel(col,row).getR()* 0.2126)+(this->getPixel(col,row).getG()* 0.7152)+(this->getPixel(col,row).getB()* 0.0722),row,col);
        }
}

void Picture::toBW()
{
    int thresh = findThreshold();
    thresh = thresh + (0.5*(255-thresh));

    for ( int row = 0; row < this->imageWidth ; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            if(this->getPixel(col,row).getGr() < thresh)
                this->setPixel('w',0,row,col);
            else
                this->setPixel('w',255,row,col);
        }


}

void Picture::getHistogram()
{
    int occurence[256] = {0};
    for(int i = 0; i <256; i++)
    {
        histogram[i] = 0;
    }
    int total = 0;

    for ( int row = 0; row < this->imageWidth ; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            int value = this->getPixel(col,row).getGr();

            occurence[value] = occurence[value]+1;
            total++;
        }


    for(int i =0; i<256;i++)
    {
        histogram[i] = (float) occurence[i] /  (float) total;
    }
}

int Picture::findThreshold()
{
    getHistogram();
    double probability[256], mean[256];
    double max_between, between[256];
    int threshold;


    for(int i = 0; i < 256; i++) {
        probability[i] = 0.0;
        mean[i] = 0.0;
        between[i] = 0.0;
    }

    probability[0] = histogram[0];

    for(int i = 1; i < 256; i++) {
        probability[i] = probability[i - 1] + histogram[i];
        mean[i] = mean[i - 1] + i * histogram[i];
    }

    threshold = 0;
    max_between = 0.0;

    for(int i = 0; i < 255; i++) {
    if(probability[i] != 0.0 && probability[i] != 1.0)
    {
        between[i] = pow(mean[255] * probability[i] - mean[i], 2) / (probability[i] * (1.0 - probability[i]));
    }
    else
    {
        between[i] = 0.0;
    }
        if(between[i] > max_between) {
            max_between = between[i];
            threshold = i;
        }
    }

    return threshold;
}

void Picture::floodFillUntil(int x, int y, int prevC, int newC)
{
    // Base cases
    if (x < 400 || x >= 500|| y < 300 || y >= 400)
        return;
    if (this->getPixel(y,x).getBW() != prevC)
        return;

    // Replace the color at (x, y
    this->setPixel('W',newC,x,y);

    // Recur for north, east, south and west
    this->floodFillUntil(x+1, y, prevC, newC);
    this->floodFillUntil(x-1, y, prevC, newC);
    this->floodFillUntil(x, y+1, prevC, newC);
    this->floodFillUntil(x, y-1, prevC, newC);
}

void Picture::createNewImage()
{
    int minX = this->imageWidth;
    int maxX = 0;
    int minY = this->imageHeight;
    int maxY = 0;

    Picture newObject;
    for ( int row = 0; row < this->imageWidth ; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            if(this->getPixel(col,row).getBW() == 100)
            {
                if(row < minX)
                    minX = row;
                if(row> maxX)
                    maxX = row;
                if(col<minY)
                    minY = col;
                if(col>maxY)
                    maxY = col;
            }
        }
    newObject = Picture(maxX-minX-2,maxY-minY-2);

    for ( int row = minX+1; row < maxX-1 ; ++row )
        for ( int col = minY+1; col < maxY-1 ; ++col )
        {
            if(this->getPixel(col,row).getBW() == 100)
               newObject.createPixel(Pixel(255),row-minX-1,col-minY-1);
            else
                newObject.createPixel(Pixel(0),row-minX-1,col-minY-1);
        }

    this->objectArray.push_back(newObject);
}

void Picture::dialate(int size)
{
    Picture newImage(this->imageWidth,this->imageHeight);


    for ( int row = 0; row < this->imageWidth; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            bool isWhite =  false;
            for ( int Frow = row - ((size-1)/2); Frow < row + ((size-1)/2) ; ++Frow )
                for ( int Fcol = col - ((size-1)/2); Fcol < col + ((size-1)/2) ; ++Fcol )
                {
                    if (Frow < 0 || Frow >= this->imageWidth|| Fcol < 0 || Fcol >= this->imageHeight)
                    {
                     break;
                    }
                    else
                    {
                        if(this->getPixel(Fcol,Frow).getBW() == 255)
                        {
                            isWhite = true;
                        }
                    }
                }
            if(isWhite)
            {
                newImage.createPixel(Pixel(255),row,col);
            }
            else
            {
                newImage.createPixel(Pixel(0),row,col);
            }

        }
    for ( int row = 0; row < this->imageWidth ; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            this->setPixel('W',newImage.getPixel(col,row).getBW(),row,col);
        }
}

void Picture::invert()
{
    for ( int row = 0; row < this->imageWidth ; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            if(this->getPixel(col,row).getBW() == 255)
                this->setPixel('w',0,row,col);
            else
               this->setPixel('w',255,row,col);
        }
}

void Picture::getObjects()
{
    int test = 0;
    for ( int row = 0; row < this->imageWidth ; ++row )
        for ( int col = 0; col < this->imageHeight ; ++col )
        {
            if(this->getPixel(col,row).getBW() == 255 && test < 2)
            {

                floodFillUntil(row,col,this->getPixel(col,row).getBW(),100);
                createNewImage();
                floodFillUntil(row,col,this->getPixel(col,row).getBW(),254);
                 test++;
            }
        }
}
