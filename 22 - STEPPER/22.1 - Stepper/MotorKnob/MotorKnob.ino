/***************************************************************************
 * MotorKnob
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 **************************************************************************/
#include <Stepper.h>
#define STEPS 48       // change this to the number of steps on your motor

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 10, 9, 11);
void setup()
{
    stepper.setSpeed(600);    // set the speed of the motor to 600 RPMs
}
void loop()
{
  stepper.step(1);
}
