#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QKeyEvent>

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

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QPixmap* mImage[2];

    QString mAPName;
    int mAPwidth;
    int mAPheight;

    QString mLATName;
    int mLATwidth;
    int mLATheight;

    double mScaleFactor = 1.0f;

    Screen mZoomScreen = Screen::AP;
};
#endif // MAINWINDOW_H
