void setupStart(){
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

