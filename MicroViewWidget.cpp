// MicroViewWidget class, separate from the main MicroView class.

#include "MicroViewWidget.h"

// -------------------------------------------------------------------------------------
// MicroViewWidget Class - start
// -------------------------------------------------------------------------------------

/** \brief MicroView widget parent class.

  The MicroViewWidget class is the parent class for child widget like MicroViewSlider and MicroViewGauge.
*/
MicroViewWidget::MicroViewWidget(uint8_t newx, uint8_t newy, int16_t min, int16_t max) {
  setX(newx);
  setY(newy);
  value=0;
  setMinValue(min);
  setMaxValue(max);
}

/** \brief Get widget x position. */
uint8_t MicroViewWidget::getX() { return x; }

/** \brief Get widget y position. */
uint8_t MicroViewWidget::getY() { return y; }

/** \brief Set widget x position. */
void MicroViewWidget::setX(uint8_t newx) { x = newx; }

/** \brief Set widget y position. */
void MicroViewWidget::setY(uint8_t newy) { y = newy; }

/** \brief Get minimum value.

  Return the minimum value of the widget.
*/
int16_t MicroViewWidget::getMinValue() { return minValue; }

/** \brief Get maximum value.

  Return the maximum value of the widget.
*/
int16_t MicroViewWidget::getMaxValue() { return maxValue; }

/** \brief Get current value.

  Return the current value of the widget.
*/
int16_t MicroViewWidget::getValue() { return value; }

/** \brief Set minimum value.

  The minimum value of the widget is set to the variable passed in.
*/
void MicroViewWidget::setMinValue(int16_t min) { minValue=min; }

/** \brief Set maximum value.

  The maximum value of the widget is set to the variable passed in.
*/
void MicroViewWidget::setMaxValue(int16_t max) { maxValue=max; }

/** \brief Get the maximum possible print lenth of the value

  Return the maximum number of characters that would be printed using printf("%d", value) for the current value range.
*/
uint8_t MicroViewWidget::getMaxValLen() {
  uint8_t minLen, maxLen;

  maxLen = getInt16PrintLen(maxValue);
  minLen = getInt16PrintLen(minValue);
  return maxLen >= minLen ? maxLen : minLen;
}

/** \brief Set current value.

  The current value of the widget is set to the variable passed in.
*/
void MicroViewWidget::setValue(int16_t val) { 
  if ((val<=maxValue) && (val>=minValue)){ 
    value=val; 
    this->draw();
  }
}

/** \brief MicroView Widget reDraw routine.
  
  Redraws the widget.
*/
void MicroViewWidget::reDraw() {
  needFirstDraw=true;
  this->drawFace();
  this->draw();
}