#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QKeyEvent>

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
    void scaleImage(double rate);
    void zoomIn()
    {
        scaleImage(1.25);
    }

    void zoomOut()
    {
        scaleImage(0.8);
    }

    void keyPressEvent(QKeyEvent *event);


private:
    Ui::MainWindow *ui;
    QPixmap mImage[3];
    QString LATName;
    QString APName;
    float scaleFactor = 1.0f;
};
#endif // MAINWINDOW_H
