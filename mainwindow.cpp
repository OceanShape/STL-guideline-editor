#include "mainwindow.h"
#include "ui_mainwindow.h"

QString fileName[] = {"AP_sample02.jpg", "LAT_sample02.jpg"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    lbl[Screen::AP] = ui->labelAP;
    lbl[Screen::LAT] = ui->labelLAT;

    this->setCentralWidget(ui->widget);

    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(New()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(Open()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(Close()));


    ui->widget->setContentsMargins(0,0,0,0);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::New() {
    for (int scr = 0; scr < 2; ++scr) {
        QString dir = QFileDialog::getOpenFileName(this,
                                   "Select image",
                                   QDir::currentPath(),
                                   "*.jpg ;; *.jpeg");

        QImage img;
        img.load(dir);
        QPixmap buf = QPixmap::fromImage(img);
        buf = buf.scaled(img.width(), img.height());
        float ratio = (float)img.width() / (float)img.height();

        int h = lbl[scr]->height();
        lbl[scr]->setPixmap(buf.scaled(h * ratio, h, Qt::KeepAspectRatio));
    }
}

void MainWindow::Open() {
}

void MainWindow::Close() {
    QMessageBox MsgBox;
    MsgBox.setText(tr("Save all changes?"));
    MsgBox.setStandardButtons(QMessageBox::Yes |QMessageBox::No);
    MsgBox.setDefaultButton(QMessageBox::Yes);

    if ( MsgBox.exec() == QMessageBox::Yes) {
        // Add saving data func later
    }
    this->close();
}
