// Splitting off the MicroViewSlider from the main MicroView class file.

#pragma once
#ifndef __MICROVIEWSLIDER__
#define __MICROVIEWSLIDER__

#include "MicroViewWidget.h"

class MicroViewSlider: public MicroViewWidget{
public:
  MicroViewSlider(uint8_t newx, uint8_t newy, int16_t min, int16_t max);
  MicroViewSlider(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty);
  void draw();
  void drawFace();
private:
  uint8_t totalTicks, style;
  int16_t prevValue;
};

#endif //__MICROVIEWSLIDER__