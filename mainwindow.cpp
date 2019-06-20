#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QImage>
#include <QDir>
#include <QDebug>
#include <iostream>





//int *ary = new int[sizeX*sizeY];

//// ary[i][j] is then rewritten as
//ary[i*sizeY+j]


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->labels = {ui->label0,ui->label1};
    loadImage();
       this->picture.toGrayscale();
       this->picture.toBW();
       viewImage(this->picture,0);
       this->picture.getObjects();
       viewImage(this->picture.getObject(0),0);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::loadImage()
{
    QString homePath = QDir::homePath();
    QString url = homePath + "/Vision/TI8-vision/img/dobbelstenenOgen.jpg";
    QImage img(url);

    picture = Picture(img.width(),img.height());

    for ( int row = 0; row < picture.getWidth() ; ++row )
        for ( int col = 0; col < picture.getHeight() ; ++col )
        {
            QColor clrCurrent( img.pixel( row, col ) );
            picture.createPixel(Pixel(clrCurrent.red(),clrCurrent.green(),clrCurrent.blue()),row,col);
            //std::cout << imageArray[row*img.height()+col].getR()<<"," << imageArray[row*img.height()+col].getG() <<"," << imageArray[row*img.height()+col].getB() << std::endl;

        }


}

void MainWindow::viewImage(Picture imageToShow,int window)
{
    QImage img(imageToShow.getWidth(),imageToShow.getHeight(),QImage::Format_ARGB32_Premultiplied);
    for ( int row = 0; row < imageToShow.getWidth() ; ++row )
        for ( int col = 0; col < imageToShow.getHeight() ; ++col )
        {

            //QRgb rgb = qRgb(pixelArray[row*imageHeight+col].getR(),pixelArray[row*imageHeight+col].getG(),pixelArray[row*imageHeight+col].getB());
            int gray = imageToShow.getPixel(col,row).getBW();
            img.setPixel(row,col, QColor(gray, gray, gray).rgb());
        }
    this->labels[window]->setPixmap(QPixmap::fromImage(img));
    this->labels[window]->setScaledContents(true);
}

