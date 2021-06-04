#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>

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
    QLabel* mLabel[2];
    QPixmap* mImage[2];

    int mImageWidth;
    int mImageHeight;

    double mScaleFactor;

    Screen mZoomScreen;
};
#endif // MAINWINDOW_H
