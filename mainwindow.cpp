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
  View* view[2] = {ui.viewAP, ui.viewLAT};
  QPointF defaultBaseLinePoint[2] = {
      {defaultBaseLineAPX, defaultBaseLineAPY},
      {defaultBaseLineLATZ, defaultBaseLineLATY}};
  QGraphicsScene* scene[2] = {ui.viewAP->scene(), ui.viewLAT->scene()};

  for (int i = 0; i < 2; ++i) {
    QString dir = QFileDialog::getOpenFileName(
        this, "Select image", QDir::currentPath(), "*.jpg ;; *.jpeg ;; *.png");
    if (dir == nullptr) return;
    QImage* img = new QImage(dir);

    delete scene[i];
    scene[i] = new QGraphicsScene;
    view[i]->setScene(scene[i]);
    scene[i]->addPixmap(QPixmap::fromImage(*img));
    view[i]->fitInView(QRectF(0, 0, scene[i]->sceneRect().width(),
                              scene[i]->sceneRect().height()),
                       Qt::KeepAspectRatio);
    view[i]->drawDefaultBaseLine(defaultBaseLinePoint[i]);
  }
}

void MainWindow::Open() {}

void MainWindow::Save() {
  ViewAP* ap = ui.viewAP;
  ViewLAT* lat = ui.viewLAT;
  QGraphicsScene* s[2] = { ui.viewAP->scene(), ui.viewLAT->scene() };

  QFile file("output.csv");
  if (!file.open(QFile::WriteOnly | QFile::Text)){
    return;
  }
  QTextStream out(&file);
  QString str[9] = { "AP_BASE", "LAT_BASE", "AP_SPINE", "LAT_SPINE", "AP_PELVIS", "LAT_TAILBONE", "LAT_TAILBONE_ANGLE_ALPHA", "LAT_TAILBONE_ANGLE_BETA", "SPINOUS_PROCESS"};
  out << ", x(x-y), y(x-y), y(y-z), z(y-z), x(x-y-z), y(x-y-z), z(x-y-z), alpha, beta" << endl;
  int baseAPx = ap->getBasePoint().x();
  int baseAPy = ap->getBasePoint().y();
  int baseLATy = lat->getBasePoint().y();
  int baseLATz = lat->getBasePoint().x();
  out << str[0] << ',' << baseAPx << ", " << 4480 - baseAPy << endl;
  out << str[1] << ",,," << 4480 - baseLATy << ", " << baseLATz << endl;
  for (int i = 0; i < spineCount; ++i) {
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      QPointF tmp = ap->getSpinePoint(i, j);
      int x = tmp.x() - baseAPx;
      int y = baseAPy - tmp.y();
      out << str[2] << '_' << i + 1 << '_' << j + 1 << ',' << x << ',' << y << endl;
    }
  }

  for (int i = 0; i < spineCount; ++i) {
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      QPointF tmp = lat->getSpinePoint(i, j);
      int y = baseLATy - tmp.y();
      int z = tmp.x() - baseLATz;
      out << str[3] << '_' << i + 1 << '_' << j + 1 << ",,," << y << ", " << z << endl;
    }
  }

  for (int i = 0; i < pelvisPointCount; ++i) {
    QPointF tmp = ap->getPelvisPoint(i);
    int x = tmp.x() - baseAPx;
    int y = baseAPy - tmp.y();
    out << str[4] << '_' << i + 1 << ',' << x << ',' << y << endl;
  }

  for (int i = 0; i < tailbonePointCount; ++i) {
    QPointF tmp = lat->getTailbonePoint(i);
    int y = baseLATy - tmp.y();
    int z = tmp.x() - baseLATz;
    out << str[5] << '_' << i + 1 << ",,," << y << ',' << z << endl;
  }
  out << str[6] << ",,,,,,,," << lat->getTailboneAlpha() << endl;
  out << str[7] << ",,,,,,,,," << lat->getTailboneBeta() << endl;

  for (int i = 0; i < spinousProcessPointCount; ++i) {
    QPointF tmpAP = ap->getSpinousProcessPoint(i);
    QPointF tmpLAT = lat->getSpinousProcessPoint(i);
    int x = tmpAP.x() - baseAPx;
    int y = baseAPy - tmpAP.y();
    int z = tmpLAT.x() - baseLATz;
    out << str[8] << '_' << i + 1 << ',' << "  ,  ,  ,  ," << x << ',' << y << ',' << z << endl;
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
    Save();
    this->close();
  } else if (msg == QMessageBox::No) {
    this->close();
  }
}