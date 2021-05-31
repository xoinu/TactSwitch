#ifndef TactSwitch_h
#define TactSwitch_h
#include <Arduino.h>
//
// TactSwitch is a utility to process tactile switch events.
// It can handle not only simple press/release events but also hold/release,
// which enables a switch to have multiple functions.
//
class TactSwitch
{
public:
  typedef void (*Callback)(uint32_t tick);

public:
  TactSwitch();
  void begin(uint8_t pin, uint32_t holdThresholdMsec, Callback onPress, Callback onRelease, Callback onHold, Callback onHoldRelease);
  void processTick(uint32_t tick);

private:
  uint8_t pin_;
  uint32_t holdThreshold_;
  uint32_t downTick_;
  uint32_t upTick_;
  Callback onPress_;
  Callback onRelease_;
  Callback onHold_;
  Callback onHoldRelease_;
};

#endif
