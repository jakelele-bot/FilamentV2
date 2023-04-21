//accelstepper constant speed example has been altered and is being used
// not using default 4 wires setup, but instead using step, direction, and enable pins
// using TB6600 4A 9-42V stepper driver at 6400 pulses/rev (32 microsteps)

#include <AccelStepper.h>

// defines pins numbers
const int stepPin1 = 37;
const int directionPin1 = 33;
const int enablePin1 = 35;

const int stepPin3 = 53;
const int directionPin3 = 51;
const int enablePin3 = 49;

const int stepPin2 = 48;
const int directionPin2 = 50;
const int enablePin2 = 52;

const int stepPin4 = 46;
const int directionPin4 = 47;
const int enablePin4 = 48;


//Vi laver lige å speed a variabler til tykkelsen af plastikfilamentet der kommer ud sådan vi kan bestemme speed til den ene motor ud fra dette.
float tykkelse = 0;
const float dspeed = 50;
const float hspeed = 100;
const float lspeed = 25;


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
  stepper2.setSpeed(0);
  stepper3.setSpeed(50);
  stepper4.setSpeed(50);

}

void loop()
{
  float tykkelse = analogRead(ÅÅÅÅÅ PIN DER BLIVER BRUGT);
  if (tykkelse > 1.7) {
    stepper3.setSpeed(hspeed);
  } else if (thickness < 1.3) {
    stepper3.setSpeed(lspeed);
  } else {
    stepper3.setSpeed(dspeed);
  }

  // Drejer hjulle æ ås
  stepper1.runSpeed();
  stepper2.runSpeed();
  stepper3.runSpeed();
  stepper4.runSpeed();
}