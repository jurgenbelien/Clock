#ifndef THROTTLE_INTERVAL
  #define THROTTLE_INTERVAL 5
#endif

#include <inttypes.h>
#include <core_pins.h>
#include <stddef.h>
#include <map>

typedef void (*function)();

class Clock {
  public:
    Clock(uint8_t pinClock)
    : pinClock(pinClock) {}

    void init();
    void update();

    bool rose();
    bool fell();
    bool ticked();

    // Callbacks
    void addCallback(function callback);
    void removeCallback();

  private:
    const uint8_t pinClock;

    bool state = 0;
    bool stateChanged = false;
    bool getHardwareState();
    unsigned long int stateChangeTimestamp = millis();
    unsigned long int previousStateChangeTimestamp = millis();
    unsigned int durationSince(unsigned long int timestamp);

    function callback;
};
