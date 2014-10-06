// Splitting out the MicroViewWidget from the main class file

#ifndef __MICROVIEWWIDGET__
#define __MICROVIEWWIDGET__

#include "MicroView.h"

class MicroViewWidget {
public:

  MicroViewWidget(uint8_t newx, uint8_t newy, int16_t min, int16_t max);
  uint8_t getX();
  uint8_t getY();
  void setX(uint8_t newx);
  void setY(uint8_t newy);
  bool needsFirstDraw() const;
  
  int16_t getMinValue();
  int16_t getMaxValue();
  int16_t getValue();
  void setMaxValue(int16_t max);
  void setMinValue(int16_t max);
  void setValue(int16_t val);
  uint8_t getMaxValLen();
  virtual void draw() = 0;
  virtual void drawFace() = 0;
  void reDraw();

  bool needFirstDraw;
  
private:

  uint8_t x;
  uint8_t y;
  int16_t maxValue;
  int16_t minValue;
  int16_t value;
};

#endif //__MICROVIEWWIDGET__
