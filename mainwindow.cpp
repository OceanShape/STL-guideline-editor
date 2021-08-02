#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ui.setupUi(this);
  showMaximized();

  this->setCentralWidget(ui.widget);

  connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(New()));
  connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(Open()));
  connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(Close()));
}

void MainWindow::New() {
  View* v[2] = {ui.viewAP, ui.viewLAT};
  QGraphicsScene* s[2] = {new QGraphicsScene(), new QGraphicsScene()};

  for (int i = 0; i < 2; ++i) {
    QString dir = QFileDialog::getOpenFileName(
        this, "Select image", QDir::currentPath(), "*.jpg ;; *.jpeg ;; *.png");
    if (dir == nullptr) return;
    QImage* img = new QImage(dir);

    v[i]->setScene(s[i]);
    s[i]->addPixmap(QPixmap::fromImage(*img));
    v[i]->fitInView(
        QRectF(0, 0, s[i]->sceneRect().width(), s[i]->sceneRect().height()),
        Qt::KeepAspectRatio);
  }
}

void MainWindow::Open() {}

void MainWindow::Close() {
  QMessageBox msgBox;
  msgBox.setText(tr("Save all changes?"));
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No |
                            QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Yes);

  int msg = msgBox.exec();
  if (msg == QMessageBox::Yes) {
    // Add saving data func later
    this->close();
  } else if (msg == QMessageBox::No) {
    this->close();
  }
}