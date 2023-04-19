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
//float filament_Afstand = 20.667*log(analogReadHall)-125.59;
//float filament_Afstand = (0.0013*(analogReadHall*analogReadHall))-1.0646*analogReadHall+224.06;
float filament_Afstand = (0.0016*(analogReadHall*analogReadHall))-1.4604*analogReadHall+324.89;

//Vi reservere pin fra 42 til 53 digital på arduino mega, til stepper drivers(TB6600)
thermo thermo1(1, 2, 3);
//indsæt pins på arduinoen der tilhører thermo(int SO, int CS, int SCK) SO,CS og SCK på max6675/breakout board

//for at læse data skal man bruge strukturen nedenfor
//Serial.println(thermo1.readCelsius());
//sættes ind i void loop thermo1.updateCelsius();
//aktuelle læsning af græder i celsius opdateret hver 300ms thermo1.getTemperature();

//IKKE TESTET MED PAUSE ENDNU

regPID pid1(200.6, 30.1, 4.0, 6); //(float _Kp, float _Ki, float _Kd, int _mosfet_pin)

void setup() {
  delay(5000); //initialize max6675 chip...
  setupStart();
}

void loop() {
  thermo1.updateCelsius();
  thermo1.getTemperature();
  Serial.println(analogReadHall);
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
  filament_Afstand = 20.667*log(analogReadHall)-125.59;

  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print(temp_1);

  //----------------------
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print(temp_2); 

  lcd.setCursor(13,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(13,0); //1st line, 10th block
  lcd.print(temp_3); 

  lcd.setCursor(17,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(17,0); //1st line, 10th block
  lcd.print(temp_4); 

  //----------------------
  lcd.setCursor(9,2); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,2); //1st line, 10th block
  lcd.print(filament_Afstand); //text
  Serial.println(filament_Afstand);
  
  Serial.println(analogReadHall);

  //----------------------
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print("      "); //erase the content by printing space over it
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print(average_Weight_Rulle); //text
}
