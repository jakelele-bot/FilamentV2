#ifndef REGPID_H
#define REGPID_H
class regPID {
  public:
    // Konstruktør til at initialisere PID-konstanterne og MOSFET gate pin-nummeret
    regPID(float _Kp, float _Ki, float _Kd, int _mosfet_pin) {
      Kp = _Kp;
      Ki = _Ki;
      Kd = _Kd;
      mosfet_pin = _mosfet_pin;
      error = 0;
      integral = 0;
      derivative = 0;
    }
    //https://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID
    // Funktion til at opdatere PID-kontrol algoritmen
    void update(float setpoint, float current_temperature) {
      // Beregn fejlen mellem den aktuelle temperatur og den ønskede temperatur
      error = setpoint - current_temperature;

      // Beregn integral af fejlen over tid
      integral = integral + error;

      // Beregn derivatet af fejlen over tid
      derivative = error - previous_error;

      // Beregn output ved hjælp af PID-kontrol algoritmen
      output = Kp * error + Ki * integral + Kd * derivative;

      // Send output fra PID-kontrol algoritmen til varmelegemet via MOSFET'en ved hjælp af PWM
      analogWrite(mosfet_pin, output);

      // Gem den aktuelle fejl til brug i næste iteration
      previous_error = error;
    }

  private:
    float Kp;
    float Ki;
    float Kd;
    int mosfet_pin;
    float error;
    float integral;
    float derivative;
    float previous_error;
    float output;
};
#endif