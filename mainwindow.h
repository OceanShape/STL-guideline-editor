#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

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
//    void open();
//    void zoomIn();
//    void zoomOut();
//    void fitToWindow();
//    void about();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap mImage[3];
};
#endif // MAINWINDOW_H
