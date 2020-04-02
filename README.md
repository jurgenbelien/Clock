# Clock
Class for working with clock signals.

## Example usage

```cpp
#include <Clock.h>

#define PIN_CLOCK 15

Clock clock(PIN_CLOCK);

void setup() {
  Serial.begin(9600);
  clock.init();
}

void loop() {
  if (clock.ticked()) {
    Serial.println("Rising edge of clock signal received");
  }
}

```
