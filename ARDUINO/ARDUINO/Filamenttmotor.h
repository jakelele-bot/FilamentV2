//accelstepper constant speed example has been altered and is being used
// not using default 4 wires setup, but instead using step, direction, and enable pins
// using TB6600 4A 9-42V stepper driver at 6400 pulses/rev (32 microsteps)

#include <AccelStepper.h>

// defines pins numbers

const int stepPinFilament = 53;
const int directionPinFilament = 51;
const int enablePinFilament = 49;



//Vi laver lige å speed a variabler til tykkelsen af plastikfilamentet der kommer ud sådan vi kan bestemme speed til den ene motor ud fra dette.
float tykkelse = 0;
const float dspeed = 50;
const float hspeed = 100;
const float lspeed = 25;
extern filament_Afstand;


// Define a stepper and the pins it will use
// 1 or AccelStepper::DRIVER means a stepper driver (with Step and Direction pins)
AccelStepper stepperFilament(AccelStepper::DRIVER, stepPinFilament, directionPinFilament);



// Flag to indicate if button is pressed

void setup()
{
  Serial.begin(9600);

 stepperFilament.setEnablePin(enablePin1);
  stepperFilament.setPinsInverted(false, false, true);




  stepperFilament.enableOutputs();
  
  stepperFilament.setMaxSpeed(1000);
  //FIlament motor
  stepperFilament.setSpeed(0);
  

}

void loop()
{
   // Drejer hjulle æ ås
  stepperFilament.runSpeed();


  }
 

  if (filament_Afstand > 1.7) {
    stepperFilament.setSpeed(hspeed);
  } else if (filament_Afstand < 1.3) {
    stepperFilament.setSpeed(lspeed);
  } else {
    stepperFilament.setSpeed(dspeed);
  }

  // Drejer hjulle æ ås

