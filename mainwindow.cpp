#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    this->setCentralWidget(ui->widget);

    img[0].load("AP_sample02.jpg");
    buf[0] = QPixmap::fromImage(img[0]);
    buf[0] = buf[0].scaled(img[0].width(), img[0].height());

    img[1].load("LAT_sample02.jpg");
    buf[1] = QPixmap::fromImage(img[1]);
    buf[1] = buf[1].scaled(img[1].width(), img[1].height());


    ui->labelAP->setPixmap(
                buf[0].scaled(ui->labelAP->height() * 0.8, ui->labelAP->height(), Qt::KeepAspectRatio));
    ui->labelLAT->setPixmap(
                buf[1].scaled(ui->labelLAT->height() * 0.8, ui->labelLAT->height(), Qt::KeepAspectRatio));


    ui->widget->setContentsMargins(0,0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

