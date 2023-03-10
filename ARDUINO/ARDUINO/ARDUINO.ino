#include "libs/Encoder/Encoder.h"
  //der er mange fejl boel men jeg (JAKOB) har fået lavet så at vi har biblotekerne inde i en mappe "libs"
  //man kalder biblotekerne ved at gøre således "libs/Encoder/Encoder.h"
  //DET SKAL VÆRE EN KLASSE BOEL!! JEG TROR IKKE DU KAN BRUGE SÅ MEGET AF DET HER...... Pls lav noget nyt og smart:)
void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  // Read the state of the rotary encoder and the switch
  int encoderValue = encoder.read();
  int switchState = digitalRead(SW);

  // Increment or decrement the current parameter based on the direction of the rotary encoder
  if (encoderValue > 0) {
    switch (currentParam) {
      case 1:
        distance.increment();
        break;
      case 2:
        thickness.increment();
        break;
      case 3:
        height.increment();
        break;
    }
    encoder.write(0);
  } else if (encoderValue < 0) {
    switch (currentParam) {
      case 1:
        distance.decrement();
        break;
      case 2:
        thickness.decrement();
        break;
      case 3:
        height.decrement();
        break;
    }
    encoder.write(0);
  }

  // If the switch is clicked, go to the next parameter
  if (switchState == LOW && prevSwitchState == HIGH) {
    currentParam++;
    if (currentParam > 3) {
      currentParam = 1;
      Serial.print("Afstanden til væggen: ");
      Serial.println(distance.getValue());
      Serial.print("Væg tykkelsen: ");
      Serial.println(thickness.getValue());
      Serial.print("Højden: ");
      Serial.println(height.getValue());
    }
  }

  // Update the previous state of the switch
  prevSwitchState = switchState;
}