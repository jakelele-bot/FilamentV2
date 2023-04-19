//Her er koderne til alle 4 stepper motor husk man skal have accelstepper.h library
//accelstepper constant speed example has been altered and is being used
// not using default 4 wires setup, but instead using step, direction, and enable pins
// using TB6600 4A 9-42V stepper driver at 6400 pulses/rev (32 microsteps)

#include <AccelStepper.h>

// defines pins numbers
const int stepPin1 = 37;
const int directionPin1 = 33;
const int enablePin1 = 35;

const int stepPin2 = 53;
const int directionPin2 = 51;
const int enablePin2 = 49;

const int stepPin3 = 48;
const int directionPin3 = 50;
const int enablePin3 = 52;

const int stepPin4 = 46;
const int directionPin4 = 47;
const int enablePin4 = 48;



// Define a stepper and the pins it will use
// 1 or AccelStepper::DRIVER means a stepper driver (with Step and Direction pins)
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, directionPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, directionPin2);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, directionPin3);
AccelStepper stepper4(AccelStepper::DRIVER, stepPin4, directionPin4);

void setup()
{
  Serial.begin(9600);

 stepper1.setEnablePin(enablePin1);
 stepper2.setEnablePin(enablePin2);
 stepper3.setEnablePin(enablePin3);
 stepper4.setEnablePin(enablePin4);
  stepper1.setPinsInverted(false, false, true);
  stepper2.setPinsInverted(false, false, true);
  stepper3.setPinsInverted(false, false, true);
  stepper4.setPinsInverted(false, false, true);




  stepper1.enableOutputs();
  stepper2.enableOutputs();
  stepper3.enableOutputs();
  stepper4.enableOutputs();

  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
  stepper3.setMaxSpeed(1000);
  stepper4.setMaxSpeed(1000);

  stepper1.setSpeed(50);
  stepper2.setSpeed(500);
  stepper3.setSpeed(50);
  stepper4.setSpeed(50);

}

void loop()
{
 stepper1.runSpeed();
 stepper2.runSpeed();
 stepper3.runSpeed();
 stepper4.runSpeed();
}