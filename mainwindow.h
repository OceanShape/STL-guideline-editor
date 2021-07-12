#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QScrollArea>
#include <QPalette>

#include "ZoomScreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //bool loadFile(const QString &);
    ~MainWindow();

private slots:
    void openAP();
    void openLAT();

    void zoomIn();
    void zoomOut();
    void scaleImage(double rate);
    void openFile(Screen screen);

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QImage image[2];
    QLabel imageLabel[2];
    QScrollArea scrollArea[2];

    int imageWidth;
    int imageHeight;

    double scaleFactor;

    Screen zoomScreen;
};
#endif // MAINWINDOW_H
