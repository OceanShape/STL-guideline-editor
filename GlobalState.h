#pragma once

#define baseLineCount 2
#define spineCount 5
#define pointCountForOneSpine 4
#define spinousProcessPointCount 5
#define clickCorrectionWidth 20
#define clickRangeWidth 50
#define pointRadius 50
#define defaultBaseLineAPX 1920
#define defaultBaseLineAPY 2800
#define defaultBaseLineLATY 2876
#define defaultBaseLineLATZ 1513
#define screenCount 2
//#define pelvisPointCount 2
//#define tailbonePointCount 3

typedef struct {
  QGraphicsEllipseItem* item;
  QPointF position;
} point;

typedef enum Screen {
  AP,
  LAT
} SCR;

//BaseLineStatus baseLineStatus[screenCount];
//QGraphicsLineItem* baseLine[screenCount][baseLineCount];
//
//point spinePoint[screenCount][spineCount][pointCountForOneSpine];
//QGraphicsLineItem* spineLine[screenCount][spineCount][pointCountForOneSpine];
//QPointF spineCenter[screenCount][spineCount];
//int currentSpine[screenCount];
//int currentSpinePoint[screenCount];
//std::stack<std::pair<int, int>> removedSpinePoint[screenCount];
//point spinousProcessPoint[screenCount][spinousProcessPointCount];
//int currentSpinousProcessPoint[screenCount];
//std::stack<int> removedSpinousProcessPoint[screenCount];
//
//QPen* pen[screenCount];
//QBrush* brush[screenCount];

