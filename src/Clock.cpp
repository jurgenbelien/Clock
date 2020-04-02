#include <core_pins.h>
#include "Clock.h"

void Clock::init() {
  pinMode(pinClock, INPUT_PULLUP);
  state = getHardwareState();
}

void Clock::update() {
  stateChanged = false;
  unsigned int stateChangeDuration = durationSince(stateChangeTimestamp);
  unsigned int previousStateChangeDuration = durationSince(previousStateChangeTimestamp);
  bool exceedsThrottledDuration = stateChangeDuration > previousStateChangeDuration / 4;

  if (!state || (state && exceedsThrottledDuration)) {
    stateChanged = getHardwareState() != state;
    if (stateChanged) {
      previousStateChangeTimestamp = stateChangeTimestamp;
      stateChangeTimestamp = millis();
      state = !state;
    }
  }

  // Execute registered callback
  if (callback != NULL) {
    callback();
  }
}

bool Clock::ticked() {
  return stateChanged && state;
}

void Clock::addCallback(void (*callback)()) {
  this->callback = callback;
}
void Clock::removeCallback() {
  this->callback = NULL;
}

bool Clock::getHardwareState() {
  return !digitalRead(pinClock); // with INPUT_PULLUP, down is 1, up is 0;
}
unsigned int Clock::durationSince(unsigned long timestamp) {
  return (timestamp == 0) ? 0 : millis() - timestamp;
}
