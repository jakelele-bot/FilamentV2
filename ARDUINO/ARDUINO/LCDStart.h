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