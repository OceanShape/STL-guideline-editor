class GlobalState {
 public:
  static GlobalState& instance() {
    static GlobalState* instance = new GlobalState();
    return *instance;
  }

  int baseLineCount = 2;
  int spineCount = 5;
  int pointCountForOneSpine = 4;
  int spinousProcessPointCount = 5;
  qreal clickCorrectionWidth = 20;
  qreal clickRangeWidth = 50;
  qreal pointRadius = 50;
  qreal defaultBaseLineAPX = 1920;
  qreal defaultBaseLineAPY = 2800;
  qreal defaultBaseLineLATY = 2876;
  qreal defaultBaseLineLATZ = 1513;

  BaseLineStatus baseLineStatus;
  //QGraphicsLineItem* baseLine[baseLineCount];

  //point spinePoint[spineCount][pointCountForOneSpine];
  //QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
  //QPointF spineCenter[spineCount];
  int currentSpine;
  int currentSpinePoint;
  std::stack<std::pair<int, int>> removedSpinePoint;
  //point spinousProcessPoint[spinousProcessPointCount];
  int currentSpinousProcessPoint;
  std::stack<int> removedSpinousProcessPoint;

  QPen* pen;
  QBrush* brush;

  // LAT
  point tailbonePoint[tailbonePointCount];
  QGraphicsItem* tailboneLine[tailbonePointCount];
  int currentTailbonePoint;
  std::stack<int> removedTailbonePoint;

  // AP
  point pelvisPoint[pelvisPointCount];
  QGraphicsItem* pelvisLine;
  QPointF pelvisCenter;
  int currentPelvisPoint;
  std::stack<int> removedPelvisPoint;

 private:
  GlobalState() {}
};