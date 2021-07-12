#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showMaximized();

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionOpenAP, SIGNAL(triggered()), this, SLOT(openAP()));
    connect(ui->actionOpenLAT, SIGNAL(triggered()), this, SLOT(openLAT()));

    image[Screen::AP].load("AP_sample01.jpg");
    image[Screen::LAT].load("LAT_sample01.jpg");


    imageLabel[Screen::AP].setPixmap(QPixmap::fromImage(image[Screen::AP]));
    imageLabel[Screen::LAT].setPixmap(QPixmap::fromImage(image[Screen::LAT]));

    scrollArea[Screen::AP].setWidget(&imageLabel[Screen::AP]);
    scrollArea[Screen::LAT].setWidget(&imageLabel[Screen::LAT]);

    ui->centralWidget->layout()->addWidget(&scrollArea[Screen::AP]);
    ui->centralWidget->layout()->addWidget(&scrollArea[Screen::LAT]);

    imageWidth = 0;
    imageHeight = 0;
    scaleFactor = 1.0;
    zoomScreen = Screen::AP;
}

MainWindow::~MainWindow()
{
//    for (QPixmap* p : mImage)
//    {
//        delete p;
//    }

    //delete ui;
}

void MainWindow::openFile(Screen screen)
{
//    QString dir = QFileDialog::getOpenFileName(this,
//                               "Select image",
//                               QDir::currentPath(),
//                               "*.jpg ;; *.jpeg");
//    mImage[screen] = new QPixmap;
//    mImage[screen]->load(dir);

//    int w = mLabel[screen]->width();
//    int h = mLabel[screen]->height();

//    mLabel[screen]->setPixmap(mImage[screen]->scaled(w, h, Qt::KeepAspectRatio));

//    qDebug() << "width" << w<< endl;
//    qDebug() << "height" << h << endl;
}

void MainWindow::openAP()
{
    openFile(Screen::AP);

    //mLabel[Screen::AP]->setStyleSheet("background-color: #000000");
}

void MainWindow::openLAT()
{
    openFile(Screen::LAT);
}

void MainWindow::scaleImage(double factor)
{
    qDebug() << factor;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q) zoomIn();
    else if(event->key() == Qt::Key_W) zoomOut();
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}
