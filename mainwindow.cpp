#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << mImage[0].load("AP_sample01.jpg") << endl;
    mImage[1].load("LAT_sample01.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int w = ui->apLabel->width();
    int h = ui->apLabel->height();
    ui->apLabel->setPixmap(mImage[0].scaled(w * 2, h * 2, Qt::KeepAspectRatio));


}
