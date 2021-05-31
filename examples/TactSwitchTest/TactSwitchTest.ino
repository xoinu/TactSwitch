#include <TactSwitch.h>

TactSwitch s_switch;

int s_press, s_release, s_hold, s_holdRelease;

static void LF_onPress(uint32_t tick)
{
  Serial.println("Pushed");
  Serial.println(++s_press);
}

static void LF_onRelease(uint32_t tick)
{
  Serial.println("Released");
  Serial.println(++s_release);
}

static void LF_onHold(uint32_t tick)
{
  Serial.println("Held");
  Serial.println(++s_hold);
}

static void LF_onHoldRelease(uint32_t tick)
{
  Serial.println("Held-n-Released");
  Serial.println(++s_holdRelease);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("UNO is ready!");
  s_switch.begin(7, 1500, &LF_onPress, &LF_onRelease, &LF_onHold, &LF_onHoldRelease);
}

void loop() {
  const uint32_t tick = millis();
  s_switch.processTick(tick);
}
