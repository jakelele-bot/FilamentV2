/*
// START 1 STOR MOTOR(BOR MOTOR)

// Som sagt er vores pin til motorne blevet reserveret fra 42 til 53 på arduino megaen (DIGITAL PINS). 
//Globals
#define STEPPIN 42
#define DIRPIN 43
#define ENAPIN 44

const int STEPTIME = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(STEPPIN,OUTPUT);
  pinMode(DIRPIN,OUTPUT);
  pinMode(ENAPIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(200);

}

void forward(int steps){
  int i;
  digitalWrite(ENAPIN,LOW);//ENABLE IS ACTIVE LOW
  digitalWrite(DIRPIN,HIGH);//SET DIRECTION 
  for(i=0;i<steps;i++){
    digitalWrite(STEPPIN,HIGH);
    delay(STEPTIME);
    digitalWrite(STEPPIN,LOW);
    delay(STEPTIME);
  }
  digitalWrite(ENAPIN,HIGH);//DISABLE STEPPER
}

*/