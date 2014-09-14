#include "MicroViewGauge.h"


// -------------------------------------------------------------------------------------
// Gauge Widget - start
// -------------------------------------------------------------------------------------

/** \brief MicroViewGauge class initilisation.

  Initialise the MicroViewGauge widget with default style.
*/
MicroViewGauge::MicroViewGauge(uint8_t newx, uint8_t newy, int16_t min, int16_t max):MicroViewWidget(newx, newy, min, max) {
  style=0;
  radius=15;
  prevValue=getMinValue();
  needFirstDraw=true;
  drawFace();
  draw();
}

/** \brief MicroViewGauge class initialisation with style.

  Initialise the MicroViewGauge widget with style WIDGETSTYLE0 or WIDGETSTYLE1.
*/
MicroViewGauge::MicroViewGauge(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty):MicroViewWidget(newx, newy, min, max) {
  if (sty==WIDGETSTYLE0) {
    style=0;
    radius=15;
  }
  else {
    style=1;
    radius=23;
  }
  prevValue=getMinValue();
  needFirstDraw=true;
  drawFace();
  draw();
}

/** \brief Draw widget face.

  Draw image/diagram representing the widget's face.
*/
void MicroViewGauge::drawFace() {
  uint8_t offsetX, offsetY;
  float degreeSec, fromSecX, fromSecY, toSecX, toSecY;
  offsetX=getX();
  offsetY=getY();

  uView.circle(offsetX,offsetY,radius);
  
  for (int i=150;i<=390;i+=30) {  // Major tick from 150 degree to 390 degree
    degreeSec=i*(PI/180);
    fromSecX = cos(degreeSec) * (radius / 1.5);
    fromSecY = sin(degreeSec) * (radius / 1.5);
    toSecX = cos(degreeSec) * (radius / 1);
    toSecY = sin(degreeSec) * (radius / 1);
    uView.line(1+offsetX+fromSecX,1+offsetY+fromSecY,1+offsetX+toSecX,1+offsetY+toSecY);
  }
  
  if(radius>15) {
    for (int i=150;i<=390;i+=15) {  // Minor tick from 150 degree to 390 degree
      degreeSec=i*(PI/180);
      fromSecX = cos(degreeSec) * (radius / 1.3);
      fromSecY = sin(degreeSec) * (radius / 1.3);
      toSecX = cos(degreeSec) * (radius / 1);
      toSecY = sin(degreeSec) * (radius / 1);
      uView.line(1+offsetX+fromSecX,1+offsetY+fromSecY,1+offsetX+toSecX,1+offsetY+toSecY);
    }
  }
}

/** \brief Draw widget value.

  Convert the current value of the widget and draw the ticker representing the value.
*/
void MicroViewGauge::draw() {
  uint8_t offsetX, offsetY;
  uint8_t maxValLen, valOffset;
  float degreeSec, toSecX, toSecY;
  char strBuffer[7];
  char formatStr[] = "%1d"; // The 1 will be replaced later by the proper length

  maxValLen = getMaxValLen();
  formatStr[1] = '0' + maxValLen; // Set the field width for the value range
  valOffset = maxValLen * 3 - 1;  // Offset left of centre to print the value

  offsetX=getX();
  offsetY=getY();

  if (needFirstDraw) {
    degreeSec = ((float)(uint16_t)(prevValue-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*240;  // total 240 degree in the widget
    degreeSec = (degreeSec+150) * (PI/180);   // 150 degree starting point
    toSecX = cos(degreeSec) * (radius / 1.2);
    toSecY = sin(degreeSec) * (radius / 1.2);
    uView.line(offsetX,offsetY,1+offsetX+toSecX,1+offsetY+toSecY, WHITE,XOR);
    sprintf(strBuffer, formatStr, prevValue); // print with fixed width so that blank space will cover larger value
    needFirstDraw=false;
  }
  else {
    // Draw previous pointer in XOR mode to erase it
    degreeSec = ((float)(uint16_t)(prevValue-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*240;  // total 240 degree in the widget
    degreeSec = (degreeSec+150) * (PI/180);
    toSecX = cos(degreeSec) * (radius / 1.2);
    toSecY = sin(degreeSec) * (radius / 1.2);
    uView.line(offsetX,offsetY,1+offsetX+toSecX,1+offsetY+toSecY, WHITE,XOR);
    
    // draw current pointer
    degreeSec = ((float)(uint16_t)(getValue()-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*240; // total 240 degree in the widget
    degreeSec = (degreeSec+150) * (PI/180);   // 150 degree starting point
    toSecX = cos(degreeSec) * (radius / 1.2);
    toSecY = sin(degreeSec) * (radius / 1.2);
    uView.line(offsetX,offsetY,1+offsetX+toSecX,1+offsetY+toSecY, WHITE,XOR);

    sprintf(strBuffer, formatStr, getValue());  // print with fixed width so that blank space will cover larger value
    prevValue=getValue();
  }

  // Draw value
  if (style>0) 
  uView.setCursor(offsetX-valOffset, offsetY+10);
  else
  uView.setCursor(offsetX-valOffset, offsetY+11);
  
  uView.print(strBuffer);
}

// -------------------------------------------------------------------------------------
// Gauge Widget - end
// -----------------