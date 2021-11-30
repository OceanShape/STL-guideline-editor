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
  QString str[9] = { "AP_BASE", "LAT_BASE", "AP_SPINE", "LAT_SPINE", "AP_PELVIS", "LAT_TAILBONE", "LAT_TAILBONE_ANGLE_ALPHA", "LAT_TAILBONE_ANGLE_BETA", "SPINOUS_PROCESS"};
  out << ", x(x-y), y(x-y), y(y-z), z(y-z), x(x-y-z), y(x-y-z), z(x-y-z), alpha, beta" << endl;
  int x, y, z;
  x = v[0]->getBasePoint().x();
  y = v[0]->getBasePoint().y();
  out << str[0] << ',' << x << ", " << 4480 - y << ",  ,  ,  ,  ,  ,  ,  " << endl;
  y = v[1]->getBasePoint().y();
  z = v[1]->getBasePoint().x();
  out << str[1] << ',' << y << ", " << 4480 - z << ",  ,  ,  ,  ,  ,  ,  " << endl;

  for (int i = 1; i <= 5; ++i) {
    out << str[2] << '_' << i << ',' << " 0, 0,  ,  ,  ,  ,  ,  ,  " << endl;
  }
  for (int i = 1; i <= 5; ++i) {
    out << str[3] << '_' << i << ',' << "  ,  , 0, 0,  ,  ,  ,  ,  " << endl;
  }

  for (int i = 1; i <= 2; ++i) {
    out << str[4] << '_' << i << ',' << " 0, 0,  ,  ,  ,  ,  ,  ,  " << endl;
  }

  for (int i = 1; i <= 3; ++i) {
    out << str[5] << '_' << i << ',' << "  ,  , 0, 0,  ,  ,  ,  ,  " << endl;
  }
  out << str[6] << ',' << "  ,  ,  ,  ,  ,  ,  , 0, 0" << endl;
  out << str[7] << ',' << "  ,  ,  ,  ,  ,  ,  , 0, 0" << endl;

  for (int i = 1; i <= 5; ++i) {
    out << str[8] << '_' << i << ',' << "  ,  ,  ,  , 0, 0, 0,  ,  " << endl;
  }

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