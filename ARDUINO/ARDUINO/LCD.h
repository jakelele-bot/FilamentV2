LiquidCrystal_I2C lcd(0x27, 20, 4);

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 8;
const int LOADCELL_SCK_PIN = 9;
HX711 scale;


int menuCounter = 0; //counts the clicks of the rotary encoder between menu items (0-3 in this case)


extern int menu1_Value; //value within menu 1
extern int menu2_Value; //value within menu 2
extern int menu3_Value; //value within menu 3
extern int menu4_Value; //value within menu 4

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

void rotate()
{  
  //-----MENU1--------------------------------------------------------------
  if(menu1_selected == true)
  {
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu1_Value < 100) //we do not go above 100
      {
        menu1_Value++;  
      }
      else
      {
        menu1_Value = 0;  
      }      
    } 
    else 
    {
      if(menu1_Value < 1) //we do not go below 0
      {
          menu1_Value = 100;
      }
      else
      {
      // Encoder is rotating B direction so decrease
      menu1_Value--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }
  //---MENU2---------------------------------------------------------------
  else if(menu2_selected == true)
  {
    CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu2_Value < 100) //we do not go above 100
      {
        menu2_Value++;  
      }
      else
      {
        menu2_Value = 0;  
      }      
    } 
    else 
    {
      if(menu2_Value < 1) //we do not go below 0
      {
          menu2_Value = 100;
      }
      else
      {
      // Encoder is rotating in B direction, so decrease
      menu2_Value--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }
  //---MENU3---------------------------------------------------------------
  else if(menu3_selected == true)
  {
    CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu3_Value < 100) //we do not go above 100
      {
        menu3_Value++;  
      }
      else
      {
        menu3_Value = 0;  
      }      
    } 
    else 
    {
      if(menu3_Value < 1) //we do not go below 0
      {
          menu3_Value = 100;
      }
      else
      {
      // Encoder is rotating B direction so decrease
      menu3_Value--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }
  //---MENU4----------------------------------------------------------------
  else if(menu4_selected == true)
  {
    CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu4_Value < 5) //we do not go above 100
      {
        menu4_Value++;  
      }
      else
      {
        menu4_Value = 0;  
      }      
    } 
    else 
    {
      if(menu4_Value < 1 ) //we do not go below 0
      {
          menu4_Value = 5;
          
      }
      else
      {
      // Encoder is rotating in B direction, so decrease
      menu4_Value--;      
      }      
    }    
  }

  CLKPrevious = CLKNow;  // Store last CLK state
  }
  else //MENU COUNTER----------------------------------------------------------------------------
  {
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menuCounter < 3) //we do not go above 3
      {
        menuCounter++;  
      }
      else
      {
        menuCounter = 0;  
      }      
    } 
    else 
    {
      if(menuCounter < 1) //we do not go below 0
      {
          menuCounter = 3;
      }
      else
      {
      // Encoder is rotating CW so decrease
      menuCounter--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }

  //Refresh LCD after changing the counter's value
  refreshLCD = true;
}

void pushButton()
{
  switch(menuCounter)
  {
     case 0:
     menu1_selected = !menu1_selected;  //we change the status of the variable to the opposite
     break;

     case 1:
     menu2_selected = !menu2_selected;
     break;

     case 2:
     menu3_selected = !menu3_selected;
     break;

     case 3:
     menu4_selected = !menu4_selected;
     break;
  } 
  
  refreshLCD = true; //Refresh LCD after changing the value of the menu
  refreshSelection = true; //refresh the selection ("X")
}

void printLCD()
{
  if (menu4_Value == 0 || menu4_Value == 1 || menu4_Value == 3 || menu4_Value == 5){
      //These are the values which are not changing the operation
  lcd.setCursor(1,0); //1st line, 2nd block
  lcd.print("AFS VEG"); //text
  //----------------------
  lcd.setCursor(1,1); //2nd line, 2nd block
  lcd.print("VEG TYK"); //text
  //----------------------
  lcd.setCursor(1,2); //3rd line, 2nd block
  lcd.print("HOJDE"); //text
  //----------------------
  lcd.setCursor(1,3); //4th line, 2nd block
  lcd.print("START"); //text
  //----------------------
  lcd.setCursor(13,0); //Her printer den enhederne for parameterne
  lcd.print("mm"); 
  lcd.setCursor(13,1); 
  lcd.print("mm"); 
  lcd.setCursor(13,2);
  lcd.print("mm");

  }

}

void updateLCD()
{  
  if (menu4_Value == 0 || menu4_Value == 1 || menu4_Value == 3 || menu4_Value == 5){
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print(menu1_Value); //print the value of menu1_Value variable

  lcd.setCursor(9,1);
  lcd.print("   ");
  lcd.setCursor(9,1);
  lcd.print(menu2_Value); //
  
  lcd.setCursor(9,2);
  lcd.print("   ");
  lcd.setCursor(9,2);
  lcd.print(menu3_Value); //

  lcd.setCursor(9,3);
  lcd.print("   ");
  lcd.setCursor(9,3);
  lcd.print(menu4_Value); //  
  }
}

void updateCursorPosition()
{
if (menu4_Value == 0 || menu4_Value == 1 || menu4_Value == 3 || menu4_Value == 5){
  //Clear display's ">" parts 
  lcd.setCursor(0,0); //1st line, 1st block
  lcd.print(" "); //erase by printing a space
  lcd.setCursor(0,1);
  lcd.print(" "); 
  lcd.setCursor(0,2);
  lcd.print(" "); 
  lcd.setCursor(0,3);
  lcd.print(" "); 
     
  //Place cursor to the new position
  switch(menuCounter) //this checks the value of the counter (0, 1, 2 or 3)
  {
    case 0:
    lcd.setCursor(0,0); //1st line, 1st block
    lcd.print(">"); 
    break;
    //-------------------------------
    case 1:
    lcd.setCursor(0,1); //2nd line, 1st block
    lcd.print(">"); 
    break;
    //-------------------------------    
    case 2:
    lcd.setCursor(0,2); //3rd line, 1st block
    lcd.print(">"); 
    break;
    //-------------------------------    
    case 3:
    lcd.setCursor(0,3); //4th line, 1st block
    lcd.print(">"); 
    break;
  }
}
}

void updateSelection()
{
  if (menu4_Value == 0 || menu4_Value == 1 || menu4_Value == 3 || menu4_Value == 5){
  //When a menu is selected ">" becomes "X"

  if(menu1_selected == true)
  {
    lcd.setCursor(0,0); //1st line, 1st block
    lcd.print("X"); 
  }
  //-------------------
   if(menu2_selected == true)
  {
    lcd.setCursor(0,1); //2nd line, 1st block
    lcd.print("X"); 
  }
  //-------------------
  if(menu3_selected == true)
  {
    lcd.setCursor(0,2); //3rd line, 1st block
    lcd.print("X"); 
  }
  //-------------------
  if(menu4_selected == true)
  {
    lcd.setCursor(0,3); //4th line, 1st block
    lcd.print("X"); 
  }
  }
}

