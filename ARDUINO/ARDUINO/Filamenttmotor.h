//accelstepper constant speed example has been altered and is being used
// not using default 4 wires setup, but instead using step, direction, and enable pins
// using TB6600 4A 9-42V stepper driver at 6400 pulses/rev (32 microsteps)

#include <AccelStepper.h>

// defines pins numbers

// defines pins numbers

const int stepPinFilament = 22;
const int directionPinFilament = 34;
const int enablePinFilament = 24;
const int analogPin1 = 0;

const int stepPin3 = 48;
const int dirPin3 = 50;
const int enablePin3 = 52;


//Vi laver lige å speed a variabler til tykkelsen af plastikfilamentet der kommer ud sådan vi kan bestemme speed til den ene motor ud fra dette.
float tykkelse = 0;
const float dspeed = 1000;
const float hspeed = 2000;
const float lspeed = 500;
float filament_Afstand1;

// Define a stepper and the pins it will use
// 1 or AccelStepper::DRIVER means a stepper driver (with Step and Direction pins)
AccelStepper stepperFilament(AccelStepper::DRIVER, stepPinFilament, directionPinFilament);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);

// Flag to indicate if button is pressed

void SetupMotor()
{
 Serial.println(filament_Afstand1);

  stepperFilament.setEnablePin(enablePinFilament);
  stepperFilament.setPinsInverted(false, false, true);
  stepperFilament.enableOutputs();
  stepperFilament.setMaxSpeed(400);
  stepper3.setMaxSpeed(50);
  stepper3.setSpeed(50);
  stepperFilament.setAcceleration(50);
}

void MotorLoop()
{
  stepper3.move(2000);
  stepper3.runSpeed();
  int analogReadHall = analogRead(analogPin1);
  filament_Afstand1 = -0.0294*analogReadHall+19.882;
  // Adjust motor speed based on filament_afstand value
  if (filament_Afstand1 >= 1.8) {
    stepperFilament.setMaxSpeed(hspeed);
    stepperFilament.move(2000);
    stepperFilament.runSpeed();
  } 
  else if (filament_Afstand1 <= 1.7) {
    stepperFilament.setMaxSpeed(lspeed);
    stepperFilament.move(1000);
    stepperFilament.runSpeed();
  } 
  else {
    float speed = (filament_Afstand1 - 1.75) * (hspeed - lspeed) / (1.8 - 1.7) + lspeed;
    stepperFilament.setMaxSpeed(dspeed);
    stepperFilament.move(2000);
    stepperFilament.run();
  }
  
  // Run the motor at the current speed
}
