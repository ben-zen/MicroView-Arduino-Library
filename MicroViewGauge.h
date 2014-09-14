// Splitting off MicroViewGauge from MicroView class file

#ifndef __MICROVIEWGAUGE__
#define __MICROVIEWGAUGE__

#include "MicroViewWidget.h"

class MicroViewGauge: public MicroViewWidget{
public:
  MicroViewGauge(uint8_t newx, uint8_t newy, int16_t min, int16_t max);
  MicroViewGauge(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty);
  void draw();
  void drawFace();
private:
  uint8_t radius, style;
  int16_t prevValue;
};

#endif //__MICROVIEWGAUGE__