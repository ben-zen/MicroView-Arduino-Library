#include "MicroViewSlider.h"


// -------------------------------------------------------------------------------------
// Slider Widget - start
// -------------------------------------------------------------------------------------

/** \brief MicroViewSlider class initialisation. 

  Initialise the MicroViewSlider widget with default style.
*/
MicroViewSlider::MicroViewSlider(uint8_t newx, uint8_t newy, int16_t min, int16_t max):MicroViewWidget(newx, newy, min, max) {
  style=0;
  totalTicks=30;
  prevValue=getMinValue();
  needFirstDraw=true;
  drawFace();
  draw();
}

/** \brief MicroViewSlider class initialisation with style. 

  Initialise the MicroViewSlider widget with style WIDGETSTYLE0 or WIDGETSTYLE1 or WIDGETSTYLE2 (like 0, but vertical) or WIDGETSTYLE3 (like 1, but vertical). If this list gets any longer, it might be better as a switch/case statement.
*/
MicroViewSlider::MicroViewSlider(uint8_t newx, uint8_t newy, int16_t min, int16_t max, uint8_t sty):MicroViewWidget(newx, newy, min, max) {
  if (sty==WIDGETSTYLE1) {
    style=1;
    totalTicks=60;
  }
  else if (sty==WIDGETSTYLE2) {
    style=2;
    totalTicks=20;
  }
  else if (sty==WIDGETSTYLE3) {
    style=3;
    totalTicks=40;
  }
  else {    // Use style 0 if specified or invalid
    style=0;
    totalTicks=30;
  }

  prevValue=getMinValue();
  needFirstDraw=true;
  drawFace();
  draw();
}

/** \brief Draw widget face.

  Draw image/diagram representing the widget's face.
*/
void MicroViewSlider::drawFace() {
  uint8_t offsetX, offsetY, endOffset;
  offsetX=getX();
  offsetY=getY();

  //Horizontal styles, style 0 or 1
  if (style==0 || style==1) {
    endOffset = offsetX + totalTicks + 2;
    // Draw minor ticks
    for (uint8_t i=offsetX+1; i<endOffset; i+=2) {
      uView.lineV(i, offsetY+5, 3);
    }
    // Draw extensions for major ticks
    for (uint8_t i=offsetX+1; i<endOffset; i+=10) {
      uView.lineV(i, offsetY+3, 2);
    }
  }
  //Vertical styles, style 2 or 3
  else {
    endOffset = offsetY + totalTicks + 2;
    // Draw minor ticks
    for (uint8_t i=offsetY+1; i<=endOffset; i+=2) {
      uView.lineH(offsetX, i, 3);
    }
    // Draw extensions for major ticks
    for (uint8_t i=offsetY+1; i<=endOffset; i+=10) {
      uView.lineH(offsetX+3, i, 2);
    }
  }
}

/** \brief Draw widget value.

  Convert the current value of the widget and draw the ticker representing the value.
*/
void MicroViewSlider::draw() {
  uint8_t offsetX, offsetY;
  uint8_t tickPosition=0;
  char strBuffer[7];
  char formatStr[] = "%1d";

  formatStr[1] = '0' + getMaxValLen();  // Set the field width for the value range

  offsetX=getX();
  offsetY=getY();

  if (needFirstDraw) {
    if (style==0 || style==1){    //Horizontal
      tickPosition = ((float)(uint16_t)(prevValue-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks;
      uView.lineH(offsetX+tickPosition,offsetY, 3, WHITE, XOR);
      uView.pixel(offsetX+1+tickPosition,offsetY+1, WHITE, XOR);
    }
    else {          //Vertical
      tickPosition = ((float)(uint16_t)(getMaxValue()-prevValue)/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks;
      uView.lineV(offsetX+7, offsetY+tickPosition, 3, WHITE, XOR);
      uView.pixel(offsetX+6, offsetY+1+tickPosition, WHITE, XOR);
    }

    sprintf(strBuffer, formatStr, prevValue); // print with fixed width so that blank space will cover larger value
    needFirstDraw=false;
  }
  else {
    // Draw previous pointer in XOR mode to erase it
    if (style==0 || style==1){    //Horizontal
      tickPosition = ((float)(uint16_t)(prevValue-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks;
      uView.lineH(offsetX+tickPosition,offsetY, 3, WHITE, XOR);
      uView.pixel(offsetX+1+tickPosition,offsetY+1, WHITE, XOR);
    }
    else {          //Vertical
      tickPosition = ((float)(uint16_t)(getMaxValue()-prevValue)/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks;
      uView.lineV(offsetX+7, offsetY+tickPosition, 3, WHITE, XOR);
      uView.pixel(offsetX+6, offsetY+1+tickPosition, WHITE, XOR);
    }

    // Draw current pointer
    if (style==0 || style==1){    //Horizontal
      tickPosition = ((float)(uint16_t)(getValue()-getMinValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks;
      uView.lineH(offsetX+tickPosition,offsetY, 3, WHITE, XOR);
      uView.pixel(offsetX+1+tickPosition,offsetY+1, WHITE, XOR);
    }
    else {          //Vertical
      tickPosition = ((float)(uint16_t)(getMaxValue()-getValue())/(float)(uint16_t)(getMaxValue()-getMinValue()))*totalTicks;
      uView.lineV(offsetX+7, offsetY+tickPosition, 3, WHITE, XOR);
      uView.pixel(offsetX+6, offsetY+1+tickPosition, WHITE, XOR);
    }

    sprintf(strBuffer, formatStr, getValue());  // print with fixed width so that blank space will cover larger value
    prevValue=getValue();
  }

  // Draw value
  if (style==0)
    uView.setCursor(offsetX+totalTicks+4, offsetY+1);
  else if (style==1)
    uView.setCursor(offsetX, offsetY+10);
  else if (style==2)
    uView.setCursor(offsetX+1, offsetY+totalTicks+4);
  else //style==3
    uView.setCursor(offsetX+9, offsetY);

  uView.print(strBuffer);
}

// -------------------------------------------------------------------------------------
// Slider Widget - end
// -------------------------------------------------------------------------------------
