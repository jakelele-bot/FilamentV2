#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C Frank de Brabander
#include <HX711.h> // HX711 Arduino Library af Bogdan Necula
#include <Arduino.h>
#include "LCD.h" //header fil til LCD display menuen



LiquidCrystal_I2C lcd(0x27, 20, 4);

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 8;
const int LOADCELL_SCK_PIN = 9;
HX711 scale;


//Variabler til temperature
int temp_1 = 400;
int temp_2 = 200;
int temp_3 = 124;
int temp_4 = 180;
int motor_RPM = 500;
int filament_Afstand = 10;
int average_Weight_Rulle = 0;
int stateRefresh = 1;

int menuCounter = 0; //counts the clicks of the rotary encoder between menu items (0-3 in this case)

int menu1_Value = 0; //value within menu 1
int menu2_Value = 0; //value within menu 2
int menu3_Value = 0; //value within menu 3
int menu4_Value = 0; //value within menu 4

bool menu1_selected = false; //enable/disable to change the value of menu item
bool menu2_selected = false;
bool menu3_selected = false;
bool menu4_selected = false;
//Note: if a menu is selected ">" becomes "X".

//Defining pins
//Arduino interrupt pins: 2, 3.
const int RotaryCLK = PB2; //CLK pin on the rotary encoder
const int RotaryDT = PB4; //DT pin on the rotary encoder
const int PushButton = PB3; //Button to enter/exit menu

//Statuses for the rotary encoder
int CLKNow;
int CLKPrevious;

int DTNow;
int DTPrevious;

bool refreshLCD = true; //refreshes values
bool refreshSelection = false; //refreshes selection (> / X)


void setup() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(567.916);  // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  pinMode(PB2, INPUT_PULLUP); //RotaryCLK
  pinMode(PB4, INPUT_PULLUP); //RotaryDT
  pinMode(PB3, INPUT_PULLUP); //Button

  //------------------------------------------------------
  lcd.init();                      // initialize the lcd   
  lcd.backlight();
  //------------------------------------------------------
  lcd.setCursor(0,0); //Defining positon to write from first row, first column .
  lcd.print("Menu for");
  lcd.setCursor(0,1); //Second row, first column
  lcd.print("Filament Extruder"); 
  lcd.setCursor(0,2); //Second row, first column
  lcd.print("Version: v1.1"); 
  delay(5000); //wait 2 sec
  
  lcd.clear(); //clear the whole LCD
  
  printLCD(); //print the stationary parts on the screen
  //------------------------------------------------------
  //Store states of the rotary encoder
  CLKPrevious = digitalRead(RotaryCLK);
  DTPrevious = digitalRead(RotaryDT);
      
  attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE); //CLK pin is an interrupt pin
  attachInterrupt(digitalPinToInterrupt(PushButton), pushButton, FALLING); //PushButton pin is an interrupt pin
}

void loop() 
{
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


void ProgramStart()
{
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

void ValueUpdater()
{  
//Vægt updater:
average_Weight_Rulle = scale.get_units(10);

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

  //----------------------
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print("      "); //erase the content by printing space over it
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print(average_Weight_Rulle); //text
}
