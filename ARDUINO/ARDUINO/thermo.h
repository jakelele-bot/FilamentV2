#ifndef THERMO_H
#define THERMO_H

#include <max6675.h> //af adafruit

//inspiration https://www.instructables.com/Arduino-and-Thermocouple-K-MAX6675/
// kort biblotek tutorial: https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide


class thermo {
  //laver klasse
  public:
  //laver public variabler som kan tilgås af andre dele af programmet
    thermo(int SO, int CS, int SCK) {
      //laver en klasse der gør at man kan bruge flere thermocoupler, ved at indsætte digitale pins
      thermoSO = SO;
      thermoCS = CS;
      thermoSCK = SCK;
      thermocouple = new MAX6675(thermoSCK, thermoCS, thermoSO);
      //laver en ny thermocouple med det pins der er oplyst
    }
    //Denne funktion returnerer temperaturen i Celsius der læses fra termoelementet ved hjælp af MAX6675-IC'en.
    double readCelsius() {
      //https://arduinogetstarted.com/reference/arduino-double
      //double i arduiono er en float værdi "precision float"
      return thermocouple->readCelsius();
      //pilen "peger" fra instansen/klassen thermocuple til at retunere readCelsius. Dette er på grund af at det er en pointer som har allokeret hukomelse.
      //altså man peger fra en pointer til en værdi. Fra en klasse til en værdi
      //her står lidt: https://www.geeksforgeeks.org/arrow-operator-in-c-c-with-examples/ 
      //retunere værdien der bliver aflæset af thermocouple
    }
  private:
    int thermoSO;
    int thermoCS;
    int thermoSCK;
    MAX6675 *thermocouple;
    //En pointer af max6675 pege på det max6675 der bliver oprettet og giver det adgang til bibloteket "max6675"
    //En pointer er en variabel der indeholder en hukommelsesadresse - i dette tilfælde den "instans/klasse" der bliver oprettet
    //https://en.wikipedia.org/wiki/Pointer_%28computer_programming%29
};

#endif