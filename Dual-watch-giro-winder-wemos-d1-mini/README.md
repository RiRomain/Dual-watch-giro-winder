# Dual-watch-giro-winder for wemos D1 mini

![Wiring diagram](../fritzing-drawing/WemosD1Mini.png?raw=true "Wiring diagram")

## No serial output
Due to the limited number of GPIOs available, the TX and RX are used as input and cannot be used for serial communication.

## Change needed in stepper library
The Stepper library need to be modified a to work with the esp8266:

In your Arduino installation folder, open file libraries/Stepper/src/Stepper.cpp, and add `delay(0);` in the while loop of function `void Stepper::step(int steps_to_move)`

Here the code with the added delay:
```
/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void Stepper::step(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { this->direction = 1; }
  if (steps_to_move < 0) { this->direction = 0; }


  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {
    delay(0);
    unsigned long now = micros();
```
