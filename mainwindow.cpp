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
    imageFileName[i] = QFileInfo(dir).fileName();
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

void MainWindow::Open() {
  QString dir = QFileDialog::getOpenFileName(this, "Select .csv file",
                                             QDir::currentPath(), "*.csv");
  QFile file(dir);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    return;
  }
  QTextStream OpenFile(&file);
  QVector<QString> buf;
  while (!OpenFile.atEnd()) {
    buf.push_back(OpenFile.readLine());
  }
  file.close();
}

void MainWindow::Save() {
  ViewAP* ap = ui.viewAP;
  ViewLAT* lat = ui.viewLAT;
  QGraphicsScene* s[2] = {ui.viewAP->scene(), ui.viewLAT->scene()};

  QString patientNum;
  bool ok;
  patientNum = QInputDialog::getText(this, tr("Input patient number"),
                                     tr("Patient number:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
  if (!ok) return;

  QDateTime currentTime = QDateTime::currentDateTimeUtc();
  currentTime = currentTime.addSecs(UTC_TIME_ASIA_SEOUL);
  QString currentTimeStr = currentTime.toString("yyyy-MM-dd");
  
  QString fileName = patientNum + '-' + currentTimeStr;
  QString dir = QFileDialog::getSaveFileName(this, "Select .csv file",
    QDir::currentPath() + '/' + fileName, "*.csv");

  QFile file(dir);
  if (!file.open(QFile::WriteOnly | QFile::Text)) return;
  QTextStream out(&file);
  QString dataType[11] = {"AP_BASE",
                          "LAT_BASE",
                          "AP_SPINE",
                          "LAT_SPINE",
                          "AP_PELVIS",
                          "AP_PELVIS_ANGLE",
                          "LAT_TAILBONE",
                          "LAT_TAILBONE_ANGLE",
                          "SPINOUS_PROCESS",
                          "SPINOUS_PROCESS_ROTATE_Y",
                          "SPINOUS_PROCESS_ROTATE_Z"};
  QString patientType[5] = {"AP_name", "LAT_name", "date", "symptom",
                            "remarks(proof)"};
  out << patientType[0] << ',' << patientType[1] << ',' << patientType[2] << ','
      << patientType[3] << ',' << patientType[4] << "\n";
  out << imageFileName[0] << ',' << imageFileName[1] << ',' << currentTimeStr
      << '\n';
  out << ", x(x-y), y(x-y), y(y-z), z(y-z), y(rot), z(rot), x(x-y-z), y(x-y-z), z(x-y-z), "
         "alpha, beta"
      << endl;
  int baseAPx = ap->getBasePoint().x();
  int baseAPy = ap->getBasePoint().y();
  int baseLATy = lat->getBasePoint().y();
  int baseLATz = lat->getBasePoint().x();
  out << dataType[0] << ',' << baseAPx << ", " << 4480 - baseAPy << endl;
  out << dataType[1] << ",,," << 4480 - baseLATy << ", " << baseLATz << endl;
  for (int i = 0; i < spineCount; ++i) {
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      QPointF tmp = ap->getSpinePoint(i, j);
      int x = tmp.x() - baseAPx;
      int y = baseAPy - tmp.y();
      out << dataType[2] << '_' << i + 1 << '_' << j + 1 << ',' << x << ','
          << y;
      if (j == 0) {
        out << ",,,," << ap->getSpineRotateZ(i);  // Yrot
      }
      out << endl;
    }
  }

  for (int i = 0; i < spineCount; ++i) {
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      QPointF tmp = lat->getSpinePoint(i, j);
      int y = baseLATy - tmp.y();
      int z = tmp.x() - baseLATz;
      out << dataType[3] << '_' << i + 1 << '_' << j + 1 << ",,," << y << ", "
          << z << endl;
    }
  }

  for (int i = 0; i < pelvisPointCount; ++i) {
    QPointF tmp = ap->getPelvisPoint(i);
    int x = tmp.x() - baseAPx;
    int y = baseAPy - tmp.y();
    out << dataType[4] << '_' << i + 1 << ',' << x << ',' << y << endl;
  }
  out << dataType[5] << ",,,,,,,,,," << ap->getPelvisAlpha() << endl;

  for (int i = 0; i < tailbonePointCount; ++i) {
    QPointF tmp = lat->getTailbonePoint(i);
    int y = baseLATy - tmp.y();
    int z = tmp.x() - baseLATz;
    out << dataType[6] << '_' << i + 1 << ",,," << y << ',' << z << endl;
  }
  out << dataType[7] << ",,,,,,,,,," << lat->getTailboneAlpha() << ','
      << lat->getTailboneBeta() << endl;

  for (int i = 0; i < spinousProcessPointCount; ++i) {
    QPointF tmpAP = ap->getSpinousProcessPoint(i);
    QPointF tmpLAT = lat->getSpinousProcessPoint(i);
    int x = tmpAP.x() - baseAPx;
    int y = baseAPy - tmpAP.y();
    int z = tmpLAT.x() - baseLATz;
    out << dataType[8] << '_' << i + 1 << ',' << ",,,,,," << x << ',' << y
        << ',' << z << endl;
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