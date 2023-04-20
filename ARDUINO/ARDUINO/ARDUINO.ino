//------BIBLOTEKER------
#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C Frank de Brabander
#include <HX711.h> // HX711 Arduino Library af Bogdan Necula
#include <max6675.h> //af adafruit bliver brugt i "thermo.h"

//------HEADER FILER------

#include "LCD.h" //header fil til LCD display menuen
#include "thermo.h" //header fil til temperatur måling
#include "regPID.h" //header fil til PID regulering.
#include "setupOpstart.h" //header fil til start af LCD skærm


//Variabler til temperature
int temp_1 = 400;
int temp_2 = 200;
int temp_3 = 124;
int temp_4 = 180;
int motor_RPM = 500;
int average_Weight_Rulle = 0;
int stateRefresh = 1;
int analogPin = A0; //pin til analog read til hall effekt sensor
int analogReadHall;


int menu1_Value = 0; //value for afstand til væg
int menu2_Value = 0; //value for væg tykkelsen
int menu3_Value = 0; //value for højde
int menu4_Value = 0; //value for start af program

int PLA_TOP = 190;
int PLA_BUND = 175;
double temperature2;
double temperature1;
regPID pid1(115, 18, 0.5, 8);
regPID pid2(80.5, 90, 6, 10);

thermo thermo1(53, 51, 49);
thermo thermo2(52, 50, 48);
//indsæt pins på arduinoen der tilhører thermo(int SO, int CS, int SCK) SO,CS og SCK på max6675/breakout board

const long interval = 300;
unsigned long previousMillis = 0;



//float filament_Afstand = 20.667*log(analogReadHall)-125.59;
//float filament_Afstand = (0.0013*(analogReadHall*analogReadHall))-1.0646*analogReadHall+224.06;
float filament_Afstand = (0.0016*(analogReadHall*analogReadHall))-1.4604*analogReadHall+324.89;


void setup() {
  Serial.begin(9600);
  Serial.println("START TEMP");
  delay(5000); //initialize max6675 chip...
  setupStart();
}

void loop() {
  unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) { // hvis der er gået 300ms eller mere
        previousMillis = currentMillis; // opdaterer previousMillis med den aktuelle tid
          temperature2 = thermo2.readCelsius(); // udfører målingen
          temperature1 = thermo1.readCelsius(); // udfører målingen
          //Serial.println(temperature1);
          //Serial.println(temperature2);
      }
  pid1.update(temperature1,PLA_TOP);
  pid2.update(temperature2,PLA_BUND);

  //Til PID

  //Serial.println(analogReadHall);
  if(refreshLCD == true) //If we are allowed to update the LCD ...
  {
    updateLCD(); // ... we update the LCD ...

    //... also, if one of the menus are already selected...
    if(menu1_selected == true || menu2_selected == true || menu3_selected == true || menu4_selected == true)
    {
     // do nothing
    }
    else
    {
      updateCursorPosition(); //update the position
    }
    
    refreshLCD = false; //reset the variable - wait for a new trigger
  }

  if(refreshSelection == true) //if the selection is changed
  {
    updateSelection(); //update the selection on the LCD
    refreshSelection = false; // reset the variable - wait for a new trigger
  }
    if (menu4_Value == 1){
    ProgramStart(); 
  }

}

void ProgramStart(){
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
  average_Weight_Rulle = scale.get_units(10);
  analogReadHall = analogRead(analogPin);
  filament_Afstand = -0.0294*analogReadHall+19.882;

  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print(temp_1);

  //----------------------
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print(temp_2); 

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
}
