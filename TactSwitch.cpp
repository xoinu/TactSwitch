#include <TactSwitch.h>

TactSwitch::TactSwitch()
    : pin_(0), holdThreshold_(0), downTick_(0), onPress_(nullptr), onRelease_(nullptr), onHold_(nullptr)
{
}

void TactSwitch::begin(uint8_t pin, uint32_t holdThresholdMsec, Callback onPress, Callback onRelease, Callback onHold, Callback onHoldRelease)
{
  pin_ = pin;
  holdThreshold_ = holdThresholdMsec > 750 ? holdThresholdMsec : 750;
  downTick_ = 1;
  upTick_ = 0;
  onPress_ = onPress;
  onRelease_ = onRelease;
  onHold_ = onHold;
  onHoldRelease_ = onHoldRelease;

  pinMode(pin, INPUT_PULLUP);
}

void TactSwitch::processTick(uint32_t tick)
{
  if (tick - upTick_ < 50)
    return;

  if (tick - downTick_ < 50)
    return;

  switch (downTick_)
  {
  case 0:
    // Button was held longer than threashold. Check if it is UP.
    if (digitalRead(pin_) == HIGH)
    {
      downTick_ = 1;
      upTick_ = tick;
      if (onHoldRelease_)
        onHoldRelease_(tick);
    }
    break;
  case 1:
    // Check if it is DOWN.
    if (digitalRead(pin_) == LOW)
    {
      downTick_ = tick;
      if (onPress_)
        onPress_(tick);
    }
    break;
  default:
    // Button was DOWN. Check if it is UP.
    if (digitalRead(pin_) == HIGH)
    {
      downTick_ = 1;
      upTick_ = tick;
      if (onRelease_)
        onRelease_(tick);
    }
    else if (tick - downTick_ > holdThreshold_)
    {
      downTick_ = 0;
      if (onHold_)
        onHold_(tick);
    }
    break;
  }
}
