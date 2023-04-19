//Variabler til temperature
int temp_1 = 400;
int temp_2 = 200;
int temp_3 = 124;
int temp_4 = 180;
int motor_RPM = 500;
int average_Weight_Rulle = 0;
int stateRefresh = 1;
int analogPin = A0; //pin til analog read til hall effekt sensor
double analogReadHall;
//float filament_Afstand = 20.667*log(analogReadHall)-125.59;
//float filament_Afstand = (0.0013*(analogReadHall*analogReadHall))-1.0646*analogReadHall+224.06;
//float filament_Afstand = (0.0016*(analogReadHall*analogReadHall))-1.4604*analogReadHall+324.89;
float filament_Afstand = -0.0294*analogReadHall+19.882;

// PORT 48-53 til TEMPERATUR SENSORER

void ValueUpdater(){  
  //Vægt updater:
  average_Weight_Rulle = scale.get_units(10);
  analogReadHall = analogRead(analogPin);
  filament_Afstand = -0.0294*analogReadHall+19.882;
  Serial.println(analogReadHall);

  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(5,0); //1st line, 10th block
  lcd.print(temp_1);

  //----------------------
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print(temp_2); 

/*
  lcd.setCursor(13,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(13,0); //1st line, 10th block
  lcd.print(temp_3); 

  lcd.setCursor(17,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(17,0); //1st line, 10th block
  lcd.print(temp_4); 
*/
  //----------------------
  lcd.setCursor(9,2); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,2); //1st line, 10th block
  lcd.print(filament_Afstand); //text
  Serial.print(filament_Afstand);
  
  //Serial.println(analogReadHall);

  //----------------------
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print("      "); //erase the content by printing space over it
  lcd.setCursor(9,3); //1st line, 10th block
  lcd.print(average_Weight_Rulle); //text
}
