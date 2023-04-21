#include <AccelStepper.h>
#include <ezButton.h>
ezButton buttonPin(9);

float filamentTykkelse = 1.9;
int stepsRev=200;
int tilSteps = 10;
int opTilSpole = 100;
int indreSpoleHeight = 54;
int spoolOuterWall = 3;
int blueThing = 20;
int startMovement = -1*((opTilSpole+blueThing)*tilSteps);
int antalRotation = indreSpoleHeight/filamentTykkelse;
int antalOpNedSteps = filamentTykkelse*tilSteps;
int Gearing = stepsRev*(10/7);

const int stepsPerRevolution = 200;
const int motorSpeed = 500;
const int stepPin = 53;
const int dirPin = 51;
const int enablePin = 49;


const int stepPin1 = 37;
const int dirPin1 = 33;
const int enablePin1 = 35;
const int motorSpeed2 = 60;

bool iBund = false;
bool home = false;
bool hasMoved = false;
bool hasMoved2 = false;
bool iTopSpole = false;
bool iBundSpole = true;
int stepsTaken;

AccelStepper stepper1(AccelStepper::DRIVER, stepPin, dirPin);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin1, dirPin1);


void setup() {
  stepper1.setEnablePin(enablePin);
  stepper2.setEnablePin(enablePin1);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // enable the driver
  
  pinMode(enablePin1, OUTPUT);
  digitalWrite(enablePin1, LOW); // enable the driver

  Serial.begin(9600);


  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(130);
  stepper1.setAcceleration(30000);
  stepper2.setAcceleration(30000);
}

void loop() {
  buttonPin.loop();
  buttonPin.setDebounceTime(50);
  home2();
  opNed();
}

void home2(){
    if(buttonPin.getState() == 0 && iBund == false){
    stepper1.move(200);
    stepper1.run();
  }
    if(buttonPin.getState() == 1 && iBund == false){
    stepper1.stop();
    iBund=true;
  }
    if(iBund == true && home == false){
    stepper1.move(startMovement);
    stepper1.runToPosition();
    home=true;
  }
}
void opNed(){
  if(home==true){
    for(int i = 0; i < antalRotation; i++){
      stepper2.move(Gearing);
      stepper2.runToPosition();
      stepper1.move(-antalOpNedSteps);
      stepper1.runToPosition();
    }
    for(int i = 0; i < antalRotation; i++){
      stepper2.move(Gearing);
      stepper2.runToPosition();
      stepper1.move(antalOpNedSteps);
      stepper1.runToPosition();
    }
  }
}