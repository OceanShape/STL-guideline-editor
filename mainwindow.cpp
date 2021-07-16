#include "mainwindow.h"
#include "ui_mainwindow.h"

QString fileName[] = {"AP_sample02.jpg", "LAT_sample02.jpg"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    this->setCentralWidget(ui->widget);


    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(Open()));


    ui->widget->setContentsMargins(0,0,0,0);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::Open() {
    for (int scr = 0; scr < 2; ++scr) {
        QString dir = QFileDialog::getOpenFileName(this,
                                   "Select image",
                                   QDir::currentPath(),
                                   "*.jpg ;; *.jpeg");

        img[scr].load(fileName[scr]);
        buf[scr] = QPixmap::fromImage(img[scr]);
        buf[scr] = buf[scr].scaled(img[scr].width(), img[scr].height());

        ui->labelAP->setPixmap(
                    buf[scr].scaled(ui->labelAP->height() * 0.8, ui->labelAP->height(), Qt::KeepAspectRatio));
    }
}

void MainWindow::Close() {

}
