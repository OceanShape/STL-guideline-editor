#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  ui.setupUi(this);
  showMaximized();

  this->setCentralWidget(ui.widget);

  connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(New()));
  connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(Open()));
  connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(Save()));
  connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(Close()));
  connect(ui.actionBaseLine, SIGNAL(triggered()), this, SLOT(BaseLine()));
  connect(ui.actionSpine, SIGNAL(triggered()), this, SLOT(Spine()));
  connect(ui.actionSpinousProcess, SIGNAL(triggered()), this,
          SLOT(SpinousProcess()));
  connect(ui.actionPelvis, SIGNAL(triggered()), this, SLOT(Pelvis()));
  connect(ui.actionTailbone, SIGNAL(triggered()), this, SLOT(Tailbone()));
  connect(ui.viewAP, SIGNAL(updateSignal()), this, SLOT(Update()));
  connect(ui.viewLAT, SIGNAL(updateSignal()), this, SLOT(Update()));

  ui.viewAP->scr = SCR::AP;
  ui.viewLAT->scr = SCR::LAT;

  ui.viewAP->setScene(new QGraphicsScene);
  ui.viewLAT->setScene(new QGraphicsScene);

  view[0] = ui.viewAP;
  view[1] = ui.viewLAT;

  scene[0] = ui.viewAP->scene();
  scene[1] = ui.viewLAT->scene();
}

MainWindow::~MainWindow() {
  delete ui.viewAP->scene();
  delete ui.viewLAT->scene();
}

void MainWindow::New() {
  QString dir[2];
  for (int i = 0; i < 2; ++i) {
    dir[i] = QFileDialog::getOpenFileName(
        this, "Select image", QDir::currentPath(), "*.jpg ;; *.jpeg ;; *.png");
  }
  openImage(dir);
}

void MainWindow::Open() {
  QString dir = QFileDialog::getOpenFileName(this, "Select .csv file",
                                             QDir::currentPath(), "*.csv");
  QFile file(dir);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    return;
  }
  QTextStream OpenFile(&file);
  QVector<QString> totalData;
  for (int i = 0; !OpenFile.atEnd(); ++i) {
    QString str = OpenFile.readLine();
    if (i == 0 || i == 2) continue;
    totalData.push_back(str);
  }
  file.close();

  for (int line = 0; line < totalData.size(); ++line) {
    QStringList lineData = totalData[line].split(',');
    lineData.removeAll("");
    QString tmpStr[2];
    QPoint tmpPoint;

    if (line == 0) {
      tmpStr[0] = lineData[0];
      tmpStr[1] = lineData[1];
      if (!openImage(tmpStr)) return;
      ui.symptomEdit->setText(lineData[3]);
      ui.remarksEdit->setText(lineData[4]);
    } else if (line == 1) {
      tmpPoint.setX(lineData[1].toFloat());
      tmpPoint.setY(IMAGE_HEIGHT - lineData[2].toFloat());
      view[0]->redrawBaseLine(tmpPoint, VERTICAL);
      view[0]->redrawBaseLine(tmpPoint, HORIZONTAL);
    } else if (line == 2) {
      tmpPoint.setX(lineData[1].toFloat());
      tmpPoint.setY(IMAGE_HEIGHT - lineData[2].toFloat());
      view[1]->redrawBaseLine(tmpPoint, VERTICAL);
      view[1]->redrawBaseLine(tmpPoint, HORIZONTAL);
    }
  }
}

bool MainWindow::openImage(const QString dir[2]) {
  for (int i = 0; i < 2; ++i) {
    if (dir[i] == nullptr) return false;
    QImage* img = new QImage();
    if (!img->load(dir[i])) return false;
    imageFileName[i] = QFileInfo(dir[i]).fileName();

    delete scene[i];
    scene[i] = new QGraphicsScene;
    view[i]->setScene(scene[i]);
    scene[i]->addPixmap(QPixmap::fromImage(*img));
    view[i]->fitInView(QRectF(0, 0, scene[i]->sceneRect().width(),
                              scene[i]->sceneRect().height()),
                       Qt::KeepAspectRatio);
    view[i]->drawDefaultBaseLine(defaultBaseLinePoint[i]);
  }
  return true;
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

void MainWindow::setPointText(QTextBrowser* tb1, QTextBrowser* tb2,
                              const point& p) {
  if (gs.isDataValid(p)) {
    tb1->setText(QString::number(p.position.x() - basePoint.x()));
    tb2->setText(QString::number(basePoint.y() - p.position.y()));
  } else {
    tb1->setText("invalid");
    tb2->setText("invalid");
  }
}

void MainWindow::setSpinousProcessPointText(QTextBrowser* tb1,
                                            QTextBrowser* tb2,
                                            QTextBrowser* tb3,
                                            const point& apPoint,
                                            const point& latPoint) {
  if (gs.isDataValid(apPoint) && gs.isDataValid(latPoint)) {
    tb1->setText(
        QString::number(apPoint.position.x() - ui.viewAP->getBasePoint().x()));
    tb2->setText(
        QString::number(ui.viewAP->getBasePoint().y() - apPoint.position.y()));
    tb3->setText(QString::number(latPoint.position.x() -
                                 ui.viewLAT->getBasePoint().x()));
  } else {
    tb1->setText("invalid");
    tb2->setText("invalid");
    tb3->setText("invalid");
  }
}

void MainWindow::setAngleAPText(QTextBrowser* alpha) {
  if (gs.isDataValid(gs.pelvisPoint[0]) && gs.isDataValid(gs.pelvisPoint[1])) {
    alpha->setText(QString::number(ui.viewAP->getPelvisAlpha()));
  } else {
    alpha->setText("invalid");
  }
}

void MainWindow::setAngleLATText(QTextBrowser* alpha, QTextBrowser* beta) {
  if (gs.isDataValid(gs.tailbonePoint[0]) &&
      gs.isDataValid(gs.tailbonePoint[1]) &&
      gs.isDataValid(gs.tailbonePoint[2])) {
    alpha->setText(QString::number(ui.viewLAT->getTailboneAlpha()));
    beta->setText(QString::number(ui.viewLAT->getTailboneBeta()));
  } else {
    alpha->setText("invalid");
    beta->setText("invalid");
  }
}

void MainWindow::setBaseLineText(QTextBrowser* tb1, QTextBrowser* tb2,
                                 const QGraphicsLineItem* baseLineX,
                                 const QGraphicsLineItem* baseLineY) {
  tb1->setText(QString::number(baseLineX->line().p1().x()));
  tb2->setText(QString::number(IMAGE_HEIGHT - baseLineY->line().p1().y()));
}

void MainWindow::setSpineRotateText(QTextBrowser* tb, const int& spineIdx) {
  if (gs.isDataValid(gs.spinePoint[0][spineIdx][0]) &&
      gs.isDataValid(gs.spinePoint[0][spineIdx][1]) &&
      gs.isDataValid(gs.spinePoint[0][spineIdx][2]) &&
      gs.isDataValid(gs.spinePoint[0][spineIdx][3])) {
    tb->setText(QString::number(ui.viewAP->getSpineRotateZ(spineIdx)));
  } else {
    tb->setText("invalid");
  }
}

void MainWindow::Update() {
  // update ui.status

  // BaseLine
  setBaseLineText(ui.textBrowserAPBASE_1, ui.textBrowserAPBASE_2,
                  gs.baseLine[0][0], gs.baseLine[0][1]);
  setBaseLineText(ui.textBrowserLATBASE_2, ui.textBrowserLATBASE_1,
                  gs.baseLine[1][0], gs.baseLine[1][1]);

  // AP SPINE
  basePoint = {ui.viewAP->getBasePoint().x(), ui.viewAP->getBasePoint().y()};
  setPointText(ui.textBrowserAPSPINE11_1, ui.textBrowserAPSPINE11_2,
               gs.spinePoint[0][0][0]);
  setPointText(ui.textBrowserAPSPINE12_1, ui.textBrowserAPSPINE12_2,
               gs.spinePoint[0][0][1]);
  setPointText(ui.textBrowserAPSPINE13_1, ui.textBrowserAPSPINE13_2,
               gs.spinePoint[0][0][2]);
  setPointText(ui.textBrowserAPSPINE14_1, ui.textBrowserAPSPINE14_2,
               gs.spinePoint[0][0][3]);
  setPointText(ui.textBrowserAPSPINE21_1, ui.textBrowserAPSPINE21_2,
               gs.spinePoint[0][1][0]);
  setPointText(ui.textBrowserAPSPINE22_1, ui.textBrowserAPSPINE22_2,
               gs.spinePoint[0][1][1]);
  setPointText(ui.textBrowserAPSPINE23_1, ui.textBrowserAPSPINE23_2,
               gs.spinePoint[0][1][2]);
  setPointText(ui.textBrowserAPSPINE24_1, ui.textBrowserAPSPINE24_2,
               gs.spinePoint[0][1][3]);
  setPointText(ui.textBrowserAPSPINE31_1, ui.textBrowserAPSPINE31_2,
               gs.spinePoint[0][2][0]);
  setPointText(ui.textBrowserAPSPINE32_1, ui.textBrowserAPSPINE32_2,
               gs.spinePoint[0][2][1]);
  setPointText(ui.textBrowserAPSPINE33_1, ui.textBrowserAPSPINE33_2,
               gs.spinePoint[0][2][2]);
  setPointText(ui.textBrowserAPSPINE34_1, ui.textBrowserAPSPINE34_2,
               gs.spinePoint[0][2][3]);
  setPointText(ui.textBrowserAPSPINE41_1, ui.textBrowserAPSPINE41_2,
               gs.spinePoint[0][3][0]);
  setPointText(ui.textBrowserAPSPINE42_1, ui.textBrowserAPSPINE42_2,
               gs.spinePoint[0][3][1]);
  setPointText(ui.textBrowserAPSPINE43_1, ui.textBrowserAPSPINE43_2,
               gs.spinePoint[0][3][2]);
  setPointText(ui.textBrowserAPSPINE44_1, ui.textBrowserAPSPINE44_2,
               gs.spinePoint[0][3][3]);
  setPointText(ui.textBrowserAPSPINE51_1, ui.textBrowserAPSPINE51_2,
               gs.spinePoint[0][4][0]);
  setPointText(ui.textBrowserAPSPINE52_1, ui.textBrowserAPSPINE52_2,
               gs.spinePoint[0][4][1]);
  setPointText(ui.textBrowserAPSPINE53_1, ui.textBrowserAPSPINE53_2,
               gs.spinePoint[0][4][2]);
  setPointText(ui.textBrowserAPSPINE54_1, ui.textBrowserAPSPINE54_2,
               gs.spinePoint[0][4][3]);

  // AP PELVIS
  setPointText(ui.textBrowserAPPELVIS1_1, ui.textBrowserAPPELVIS1_2,
               gs.pelvisPoint[0]);
  setPointText(ui.textBrowserAPPELVIS2_1, ui.textBrowserAPPELVIS2_2,
               gs.pelvisPoint[1]);

  // AP PELVIS ANGLE
  setAngleAPText(ui.textBrowserAPPELVISANGLE_1);

  // AP SPINE ROTATE
  setSpineRotateText(ui.textBrowserAPSPINE11_3, 0);
  setSpineRotateText(ui.textBrowserAPSPINE21_3, 1);
  setSpineRotateText(ui.textBrowserAPSPINE31_3, 2);
  setSpineRotateText(ui.textBrowserAPSPINE41_3, 3);
  setSpineRotateText(ui.textBrowserAPSPINE51_3, 4);

  // LAT SPINE
  basePoint = {ui.viewLAT->getBasePoint().x(), ui.viewLAT->getBasePoint().y()};
  setPointText(ui.textBrowserLATSPINE11_2, ui.textBrowserLATSPINE11_1,
               gs.spinePoint[1][0][0]);
  setPointText(ui.textBrowserLATSPINE12_2, ui.textBrowserLATSPINE12_1,
               gs.spinePoint[1][0][1]);
  setPointText(ui.textBrowserLATSPINE13_2, ui.textBrowserLATSPINE13_1,
               gs.spinePoint[1][0][2]);
  setPointText(ui.textBrowserLATSPINE14_2, ui.textBrowserLATSPINE14_1,
               gs.spinePoint[1][0][3]);
  setPointText(ui.textBrowserLATSPINE21_2, ui.textBrowserLATSPINE21_1,
               gs.spinePoint[1][1][0]);
  setPointText(ui.textBrowserLATSPINE22_2, ui.textBrowserLATSPINE22_1,
               gs.spinePoint[1][1][1]);
  setPointText(ui.textBrowserLATSPINE23_2, ui.textBrowserLATSPINE23_1,
               gs.spinePoint[1][1][2]);
  setPointText(ui.textBrowserLATSPINE24_2, ui.textBrowserLATSPINE24_1,
               gs.spinePoint[1][1][3]);
  setPointText(ui.textBrowserLATSPINE31_2, ui.textBrowserLATSPINE31_1,
               gs.spinePoint[1][2][0]);
  setPointText(ui.textBrowserLATSPINE32_2, ui.textBrowserLATSPINE32_1,
               gs.spinePoint[1][2][1]);
  setPointText(ui.textBrowserLATSPINE33_2, ui.textBrowserLATSPINE33_1,
               gs.spinePoint[1][2][2]);
  setPointText(ui.textBrowserLATSPINE34_2, ui.textBrowserLATSPINE34_1,
               gs.spinePoint[1][2][3]);
  setPointText(ui.textBrowserLATSPINE41_2, ui.textBrowserLATSPINE41_1,
               gs.spinePoint[1][3][0]);
  setPointText(ui.textBrowserLATSPINE42_2, ui.textBrowserLATSPINE42_1,
               gs.spinePoint[1][3][1]);
  setPointText(ui.textBrowserLATSPINE43_2, ui.textBrowserLATSPINE43_1,
               gs.spinePoint[1][3][2]);
  setPointText(ui.textBrowserLATSPINE44_2, ui.textBrowserLATSPINE44_1,
               gs.spinePoint[1][3][3]);
  setPointText(ui.textBrowserLATSPINE51_2, ui.textBrowserLATSPINE51_1,
               gs.spinePoint[1][4][0]);
  setPointText(ui.textBrowserLATSPINE52_2, ui.textBrowserLATSPINE52_1,
               gs.spinePoint[1][4][1]);
  setPointText(ui.textBrowserLATSPINE53_2, ui.textBrowserLATSPINE53_1,
               gs.spinePoint[1][4][2]);
  setPointText(ui.textBrowserLATSPINE54_2, ui.textBrowserLATSPINE54_1,
               gs.spinePoint[1][4][3]);

  // LAT TAILBONE
  setPointText(ui.textBrowserLATTAILBONE1_2, ui.textBrowserLATTAILBONE1_1,
               gs.tailbonePoint[0]);
  setPointText(ui.textBrowserLATTAILBONE2_2, ui.textBrowserLATTAILBONE2_1,
               gs.tailbonePoint[1]);
  setPointText(ui.textBrowserLATTAILBONE3_2, ui.textBrowserLATTAILBONE3_1,
               gs.tailbonePoint[2]);

  // LAT TAILBONE ANGLE
  setAngleLATText(ui.textBrowserLATTAILBONEANGLE_1,
                  ui.textBrowserLATTAILBONEANGLE_2);

  // SPINOUS PROCESS
  setSpinousProcessPointText(
      ui.textBrowserSPINOUSPROCESS1_1, ui.textBrowserSPINOUSPROCESS1_2,
      ui.textBrowserSPINOUSPROCESS1_3, gs.spinousProcessPoint[0][0],
      gs.spinousProcessPoint[1][0]);
  setSpinousProcessPointText(
      ui.textBrowserSPINOUSPROCESS2_1, ui.textBrowserSPINOUSPROCESS2_2,
      ui.textBrowserSPINOUSPROCESS2_3, gs.spinousProcessPoint[0][1],
      gs.spinousProcessPoint[1][1]);
  setSpinousProcessPointText(
      ui.textBrowserSPINOUSPROCESS3_1, ui.textBrowserSPINOUSPROCESS3_2,
      ui.textBrowserSPINOUSPROCESS3_3, gs.spinousProcessPoint[0][2],
      gs.spinousProcessPoint[1][2]);
  setSpinousProcessPointText(
      ui.textBrowserSPINOUSPROCESS4_1, ui.textBrowserSPINOUSPROCESS4_2,
      ui.textBrowserSPINOUSPROCESS4_3, gs.spinousProcessPoint[0][3],
      gs.spinousProcessPoint[1][3]);
  setSpinousProcessPointText(
      ui.textBrowserSPINOUSPROCESS5_1, ui.textBrowserSPINOUSPROCESS5_2,
      ui.textBrowserSPINOUSPROCESS5_3, gs.spinousProcessPoint[0][4],
      gs.spinousProcessPoint[1][4]);
}

void MainWindow::Save() {
  ViewAP* ap = (ViewAP*)view[0];
  ViewLAT* lat = (ViewLAT*)view[1];

  if (!GlobalState::getIncetance().isAllDataSet()) return;

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
  QString dir = QFileDialog::getSaveFileName(
      this, "Select .csv file", QDir::currentPath() + '/' + fileName, "*.csv");

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
      << ',' << ui.symptomEdit->text() << ',' << ui.remarksEdit->text() << ','
      << '\n';
  out << ",x(x-y),y(x-y),y(y-z),z(y-z),y(rot),z(rot),x(x-y-z),"
         "y(x-y-z),z(x-y-z),"
         "alpha,beta"
      << endl;
  int baseAPx = ap->getBasePoint().x();
  int baseAPy = ap->getBasePoint().y();
  int baseLATy = lat->getBasePoint().y();
  int baseLATz = lat->getBasePoint().x();
  out << dataType[0] << ',' << baseAPx << ", " << IMAGE_HEIGHT - baseAPy
      << endl;
  out << dataType[1] << ",,," << IMAGE_HEIGHT - baseLATy << ", " << baseLATz
      << endl;

  for (int i = 0; i < SPINE_COUNT; ++i) {
    for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
      QPointF tmp = ap->getSpinePoint(i, j);
      int x = tmp.x() - baseAPx;
      int y = baseAPy - tmp.y();
      out << dataType[2] << '_' << i + 1 << '_' << j + 1 << ',' << x << ','
          << y;
      if (j == 0) {
        // ¡Ø NOTICE: Put Yrot value in here
        out << ",,,," << ap->getSpineRotateZ(i);
      }
      out << endl;
    }
  }

  for (int i = 0; i < SPINE_COUNT; ++i) {
    for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
      QPointF tmp = lat->getSpinePoint(i, j);
      int y = baseLATy - tmp.y();
      int z = tmp.x() - baseLATz;
      out << dataType[3] << '_' << i + 1 << '_' << j + 1 << ",,," << y << ", "
          << z << endl;
    }
  }

  for (int i = 0; i < PELVIS_POINT_COUNT; ++i) {
    QPointF tmp = ap->getPelvisPoint(i);
    int x = tmp.x() - baseAPx;
    int y = baseAPy - tmp.y();
    out << dataType[4] << '_' << i + 1 << ',' << x << ',' << y << endl;
  }
  out << dataType[5] << ",,,,,,,,,," << ap->getPelvisAlpha() << endl;

  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i) {
    QPointF tmp = lat->getTailbonePoint(i);
    int y = baseLATy - tmp.y();
    int z = tmp.x() - baseLATz;
    out << dataType[6] << '_' << i + 1 << ",,," << y << ',' << z << endl;
  }
  out << dataType[7] << ",,,,,,,,,," << lat->getTailboneAlpha() << ','
      << lat->getTailboneBeta() << endl;

  for (int i = 0; i < SPINOUS_PROCESS_POINT_COUNT; ++i) {
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

void MainWindow::BaseLine() {
  ui.viewAP->currentMode = Mode::BASE_LINE;
  ui.viewLAT->currentMode = Mode::BASE_LINE;
}

void MainWindow::Spine() {
  ui.viewAP->currentMode = Mode::SPINE;
  ui.viewLAT->currentMode = Mode::SPINE;
}

void MainWindow::SpinousProcess() {
  ui.viewAP->currentMode = Mode::SPINOUS_PROCESS;
  ui.viewLAT->currentMode = Mode::SPINOUS_PROCESS;
}

void MainWindow::Pelvis() {
  ui.viewAP->currentMode = Mode::PELVIS_OR_TAILBONE;
  ui.viewLAT->currentMode = Mode::PELVIS_OR_TAILBONE;
}

void MainWindow::Tailbone() {
  ui.viewAP->currentMode = Mode::PELVIS_OR_TAILBONE;
  ui.viewLAT->currentMode = Mode::PELVIS_OR_TAILBONE;
}
