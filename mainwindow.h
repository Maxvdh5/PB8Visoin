#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pixel.h"
#include "picture.h"
#include <vector>
#include <iostream>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadImage(QString location); //plaatje inladen en omzetten naar een 2d pixelArray
    void loadMasks(QString location); // masks inladen en omzetten
    void viewImage(Picture imageToShow,int window); //plaatje weergeven in aangegeven window
private slots:
    //knoppen om de aplicatie te bedienen
    void on_openDobbelsteen_clicked();
    void on_Dobbelsteen_clicked();
    void on_kenteken_clicked();
    void on_openKenteken_clicked();

private:
    Ui::MainWindow *ui;

    Picture picture; //de te gebruiken afbeelding
    std::array<QLabel *, 2> labels;//array van labels om de plaatjes in weet te geven

};

#endif // MAINWINDOW_H
