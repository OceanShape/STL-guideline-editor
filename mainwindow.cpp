#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    showMaximized();

    lbl[Screen::AP] = ui.labelAP;
    lbl[Screen::LAT] = ui.labelLAT;

    this->setCentralWidget(ui.widget);

    connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(New()));
    connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(Open()));
    connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(Close()));
}

void MainWindow::New() {
    for (int scr = 0; scr < 2; ++scr) {
        QString dir = QFileDialog::getOpenFileName(this,
            "Select image",
            QDir::currentPath(),
            "*.jpg ;; *.jpeg ;; *.png");

        QImage img;
        img.load(dir);
        QPixmap buf = QPixmap::fromImage(img);
        buf = buf.scaled(img.width(), img.height());
        float ratio = (float)img.width() / (float)img.height();

        int h = lbl[scr]->height();
        int w = h * ratio;

        lbl[scr]->resize(w, h);
        lbl[scr]->setPixmap(buf.scaled(w, h, Qt::KeepAspectRatio));
    }
}

void MainWindow::Open() {
}

void MainWindow::Close() {
    QMessageBox msgBox;
    msgBox.setText(tr("Save all changes?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    if (msgBox.exec() == QMessageBox::Yes) {
        // Add saving data func later
    }
    this->close();
}
