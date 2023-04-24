
//------BIBLOTEKER------
#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C Frank de Brabander
#include <HX711.h> // HX711 Arduino Library af Bogdan Necula
#include <max6675.h> //af adafruit bliver brugt i "thermo.h"
#include <AccelStepper.h>
#include <Stepper.h>
#include <ezButton.h>


//------HEADER FILER------

#include "LCD.h" //header fil til LCD display menuen
#include "thermo.h" //header fil til temperatur måling
#include "PIDcontroller.h" //header fil til PID regulering.
#include "setupOpstart.h" //header fil til start af LCD skærm
#include "Filamenttmotor.h" //header fil til start af LCD skærm


//-----OPNED MOTOR-----
ezButton buttonPin(31);
ezButton STARTKNAP(42);

//Variabler til menu værdier
int menu1_Value = 117; //value for afstand til væg
int menu2_Value = 3; //value for væg tykkelsen
int menu3_Value = 55; //value for højde
int menu4_Value = 0; //value for start af program

bool PLA=false;

float filamentTykkelse = 2;
int stepsRev=200;
int tilSteps = 10;
int opTilSpole = menu1_Value;
int indreSpoleHeight = menu3_Value;
int spoolOuterWall = menu2_Value;
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
/*
const int stepPin3 = 48;
const int dirPin3 = 50;
const int enablePin3 = 52;
*/
bool iBund = false;
bool home = false;
bool hasMoved = false;
bool hasMoved2 = false;
bool iTopSpole = false;
bool iBundSpole = true;
int stepsTaken;

AccelStepper stepper1(AccelStepper::DRIVER, stepPin, dirPin);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin1, dirPin1);
//AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);
//Stepper myStepper(200,stepPin3,dirPin3);


int motor_RPM = 500;
int average_Weight_Rulle = 0;
int stateRefresh = 1;
int analogPin = A0; //pin til analog read til hall effekt sensor
int analogReadHall;




int PLA_TOP = 150;
int PLA_BUND = 175;
double temperature2;
double temperature1;
//regPID pid1(115, 18, 0.5, 13);
//regPID pid2(105.5, 70, 6, 10);
thermo thermo1(41, 43, 45);
thermo thermo2(23, 25, 27);
//indsæt pins på arduinoen der tilhører thermo(int SO, int CS, int SCK) SO,CS og SCK på max6675/breakout board



const long interval = 300;
unsigned long previousMillis = 0;

PIDController newPid1(650,0.8,20,13);
PIDController newPid2(495,1.4,15,10);
//PIDController(float _kp, float _ki, float _kd, int _mosfet_pin)

float filament_Afstand;


void setup() {
  Serial.begin(9600);
  Serial.println("START TEMP");
  delay(2000); //initialize max6675 chip...
  setupStart();
  SetupMotor();
  
  stepper1.setEnablePin(enablePin);
  stepper2.setEnablePin(enablePin1);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // enable the driver
  
  pinMode(enablePin1, OUTPUT);
  digitalWrite(enablePin1, LOW); // enable the driver

  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(90);
  stepper3.setMaxSpeed(50);
  stepper1.setAcceleration(30000);
  stepper2.setAcceleration(30000);
  stepper3.setAcceleration(30000);
  //setupTilNEDOP();
}

void loop() {
  buttonPin.loop();
  buttonPin.setDebounceTime(200);
  STARTKNAP.loop();
  STARTKNAP.setDebounceTime(50);
  unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) { // hvis der er gået 300ms eller mere
        previousMillis = currentMillis; // opdaterer previousMillis med den aktuelle tid
          temperature2 = thermo2.readCelsius(); // udfører målingen
          temperature1 = thermo1.readCelsius(); // udfører målingen
          Serial.print("overste varme: ");
          Serial.println(temperature1);
          Serial.print("nederste varme: ");
          Serial.println(temperature2);
          //Serial.println(temperature1);
          //Serial.println(temperature2);
      }
  if(PLA==true){
    stepper3.move(200);
    stepper3.run();
    newPid1.update(PLA_TOP,temperature1);
    newPid2.update(PLA_BUND,temperature2);
  }
  

  //Til PID

  //Serial.println(analogReadHall);
  if(refreshLCD == true) //If we are allowed to update the LCD ...
  {
    buttonPin.loop();
    updateLCD(); // ... we update the LCD ...

    //... also, if one of the menus are already selected...
    if(menu1_selected == true || menu2_selected == true || menu3_selected == true || menu4_selected == true)
    {
     // do nothing
    }
    else
    {
      updateCursorPosition(); //update the position
      buttonPin.loop();
    }
    
    refreshLCD = false; //reset the variable - wait for a new trigger
  }

  if(refreshSelection == true) //if the selection is changed
  {
    updateSelection(); //update the selection on the LCD
    buttonPin.loop();
    refreshSelection = false; // reset the variable - wait for a new trigger
  }
    if (menu4_Value == 2){
      buttonPin.loop();
      home2();
      opNed();
      lcd.clear();
      ProgramStart(); 
      PLA=true;
  }
     if (menu4_Value == 4){
       buttonPin.loop();
       lcd.clear();
       ProgramStart(); 

  }


}

void ProgramStart(){
  buttonPin.loop();
  if (stateRefresh == 1){
    lcd.clear();
    stateRefresh = 0;
  }
  
  lcd.setCursor(0,0); //1st line, 2nd block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(0,0);
  lcd.print("TEMP"); //text
  //----------------------
  lcd.setCursor(0,1); //3rd line, 2nd block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(0,1);
  lcd.print(">RPM"); //text
  //----------------------
  lcd.setCursor(0,2); //4th line, 2nd block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(0,2);
  lcd.print("TYKK"); //text

  lcd.setCursor(0,3); //4th line, 2nd block 
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(0,3);
  lcd.print("VEGT"); //text

  ValueUpdater();
}

void ValueUpdater(){  
  //Vægt updater:
  //average_Weight_Rulle = scale.get_units(10);
  analogReadHall = analogRead(analogPin);
  filament_Afstand = -0.0294*analogReadHall+19.882;
    //Funktioner
  MotorLoop();
  /*

  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print(temperature1);

  //----------------------
  lcd.setCursor(11,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(11,0); //1st line, 10th block
  lcd.print(temperature1); 

  //----------------------
  lcd.setCursor(9,2); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,2); //1st line, 10th block
  lcd.print(filament_Afstand); //text
  Serial.println(filament_Afstand);
  
  Serial.print(analogReadHall);

  //----------------------
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print("      "); //erase the content by printing space over it
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print(average_Weight_Rulle); //text
*/
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
void opNed(){}
/*
  if(STARTKNAP.getState() == 1 && home == true){
    for(int i = 0; i < antalRotation; i++){
      stepper2.move(Gearing);
      stepper2.run();
      stepper3.move(200);
      stepper3.run();
      for(int j = 0; j < antalOpNedSteps; j++){
        stepper1.move(-100);
        stepper1.runSpeed();
      }
    }
    for(int i = 0; i < antalRotation; i++){
      stepper2.move(Gearing);
      stepper2.runToPosition();
      for(int j = 0; j < antalOpNedSteps; j++){
        stepper1.move(100);
        stepper1.runSpeed();
      }
    }
  }
  
}
*/

