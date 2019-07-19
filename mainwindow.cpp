#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QImage>
#include <QDir>
#include <QDebug>
#include <iostream>
#include <QFileDialog>





//int *ary = new int[sizeX*sizeY];
// ary[i][j] is then rewritten as
//ary[i*sizeY+j]


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->labels = {ui->label1,ui->kentekenimg};


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::loadImage(QString location)
{
    QImage img(location);

    picture = Picture(img.width(),img.height());

    for ( int row = 0; row < picture.getWidth() ; ++row )
        for ( int col = 0; col < picture.getHeight() ; ++col )
        {
            QColor clrCurrent( img.pixel( row, col ) );
            picture.createPixel(Pixel(clrCurrent.red(),clrCurrent.green(),clrCurrent.blue()),row,col);
        }
}


void MainWindow::viewImage(Picture imageToShow,int window)
{
    QImage img(imageToShow.getWidth(),imageToShow.getHeight(),QImage::Format_ARGB32_Premultiplied);
    for ( int row = 0; row < imageToShow.getWidth() ; ++row )
        for ( int col = 0; col < imageToShow.getHeight() ; ++col )
        {
//            int gray = imageToShow.getPixel(col,row).getBW();
//            img.setPixel(row,col, QColor(gray,gray,gray).rgb());
            img.setPixel(row,col, QColor(imageToShow.getPixel(col,row).getR(), imageToShow.getPixel(col,row).getG(), imageToShow.getPixel(col,row).getB()).rgb());
        }
    this->labels[window]->setPixmap(QPixmap::fromImage(img));
    this->labels[window]->setScaledContents(true);
}




void MainWindow::on_openDobbelsteen_clicked()
{
    QString Filename = QFileDialog::getOpenFileName(this,"open a file",QDir::homePath()) ;
    loadImage(Filename);
       this->picture.toGrayscale();
       this->picture.toBW(this->picture.findThreshold());
       this->picture.getObjects();
        int count = 0;
        for(int i = 0; i<this->picture.getObjArrSize(); i++)
        {

            this->picture.getObject(i).floodFillUntil(2,2,0,255);
            this->picture.getObject(i).floodFillUntil(this->picture.getObject(i).getWidth()-2,2,0,255);
            this->picture.getObject(i).floodFillUntil(this->picture.getObject(i).getWidth()-2,this->picture.getObject(i).getHeight()-2,0,255);
            this->picture.getObject(i).floodFillUntil(2,this->picture.getObject(i).getHeight()-2,0,255);
            this->picture.getObject(i).close(9);
            this->picture.getObject(i).invert();
            count = count + this->picture.getObject(i).countObjects()-1;
        }

       viewImage(this->picture,0);
       ui->label->setText("Het aantal gegooide ogen is: " + QString::number(count));
}

void MainWindow::on_Dobbelsteen_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_kenteken_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_openKenteken_clicked()
{
    QString Filename = QFileDialog::getOpenFileName(this,"open a file",QDir::homePath()) ;
    loadImage(Filename);
    this->picture.toGrayscale();
    this->picture.findYellow();
    this->picture.toBW(255);
    this->picture.getObjects();
    int largest = this->picture.getLargestObject();
    Picture nummerplaat = this->picture.getObject(largest);
    nummerplaat.invert();
    nummerplaat.close(3);
    nummerplaat.getObjects();
    QString Kenteken;
    for(int i = 0; i<nummerplaat.getObjArrSize(); i++)
    {
        Picture letter = nummerplaat.getObject(i);
        letter.loadMasks();
        int test = letter.findMatch();
        Kenteken = Kenteken + letter.getID(test);
    }
    ui->label_5->setText(Kenteken);

    Picture let = nummerplaat.getObject(0);
    let.loadMasks();
    viewImage(this->picture,1);

}
