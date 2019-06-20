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

    void loadImage();
    void viewImage(Picture imageToShow,int window);
private:
    Ui::MainWindow *ui;

    Picture picture;
    std::array<QLabel *, 2> labels;
};

#endif // MAINWINDOW_H
