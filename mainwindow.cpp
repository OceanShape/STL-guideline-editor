#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ui.setupUi(this);
  showMaximized();

  this->setCentralWidget(ui.widget);

  connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(New()));
  connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(Open()));
  connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(Save()));
  connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(Close()));

  ui.viewAP->setScene(new QGraphicsScene);
  ui.viewLAT->setScene(new QGraphicsScene);
}

MainWindow::~MainWindow() {
  delete ui.viewAP->scene();
  delete ui.viewLAT->scene();
}

void MainWindow::New() {
  View* v[2] = {ui.viewAP, ui.viewLAT};
  QGraphicsScene* s[2] = {ui.viewAP->scene(), ui.viewLAT->scene()};

  for (int i = 0; i < 2; ++i) {
    QString dir = QFileDialog::getOpenFileName(
        this, "Select image", QDir::currentPath(), "*.jpg ;; *.jpeg ;; *.png");
    if (dir == nullptr) return;
    QImage* img = new QImage(dir);

    delete s[i];
    s[i] = new QGraphicsScene;
    v[i]->setScene(s[i]);
    s[i]->addPixmap(QPixmap::fromImage(*img));
    v[i]->fitInView(
        QRectF(0, 0, s[i]->sceneRect().width(), s[i]->sceneRect().height()),
        Qt::KeepAspectRatio);
  }
}

void MainWindow::Open() {}

void MainWindow::Save() {
  View* v[2] = { ui.viewAP, ui.viewLAT };
  QGraphicsScene* s[2] = { ui.viewAP->scene(), ui.viewLAT->scene() };

  QFile file("output.csv");
  if (!file.open(QFile::WriteOnly | QFile::Text)){
    return;
  }
  QTextStream out(&file);
  out << ", x, y, y, z" << '\n';
  out << "AP_BASE, 0, 0,," << '\n';
  out << "LAT_BASE,,, 0, 0" << '\n';

  out << "AP_SPINE_1, 0, 0,," << '\n';
  out << "AP_SPINE_2, 0, 0,," << '\n';
  out << "AP_SPINE_3, 0, 0,," << '\n';
  out << "AP_SPINE_4, 0, 0,," << '\n';
  out << "AP_SPINE_5, 0, 0,," << '\n';
  out << "LAT_SPINE_1,,, 0, 0" << '\n';
  out << "LAT_SPINE_2,,, 0, 0" << '\n';
  out << "LAT_SPINE_3,,, 0, 0" << '\n';
  out << "LAT_SPINE_4,,, 0, 0" << '\n';
  out << "LAT_SPINE_5,,, 0, 0" << '\n';

  out << "AP_PELVIS_1, 0, 0,," << '\n';
  out << "AP_PELVIS_2, 0, 0,," << '\n';

  file.flush();
  file.close();
}

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