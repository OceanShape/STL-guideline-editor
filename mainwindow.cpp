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

    mLabel[Screen::AP] = ui->labelAP;
    mLabel[Screen::LAT] = ui->labelLAT;



    mImageWidth = 0;
    mImageHeight = 0;
    mScaleFactor = 1.0;
    mZoomScreen = Screen::AP; // use mouse tracking later
}

MainWindow::~MainWindow()
{
    for (QPixmap* p : mImage)
    {
        delete p;
    }

    delete ui;
}

void MainWindow::openFile(Screen screen)
{
    QString dir = QFileDialog::getOpenFileName(this,
                               "Select image",
                               QDir::currentPath(),
                               "*.jpg ;; *.jpeg");
    mImage[screen] = new QPixmap;
    mImage[screen]->load(dir);

    int w = mLabel[screen]->width();
    int h = mLabel[screen]->height();

    mLabel[screen]->setPixmap(mImage[screen]->scaled(w, h, Qt::KeepAspectRatio));
    //mLabel[screen]->adjustSize();
    //this->resize(1280,720);
    //this->adjustSize();
}

void MainWindow::openAP()
{
    openFile(Screen::AP);
}

void MainWindow::openLAT()
{
    openFile(Screen::LAT);
}

void MainWindow::scaleImage(double factor)
{
    QLabel* screen = nullptr;
    if (mZoomScreen == Screen::AP)
    {
//        screen = ui->APLabel;
    }
    else // mZoomScreen == ZoomScreen::LAT
    {
//        screen = ui->LATLabel;
    }

    if (screen == nullptr)
    {
        return;
    }


    qDebug() << factor;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        zoomIn();
    }
    else if(event->key() == Qt::Key_W)
    {
        zoomOut();
    }
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}
