#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
//https://youtu.be/JFTJ2SS4xyA
class PIDController {
  public:
    PIDController(float _kp, float _ki, float _kd, int _mosfet_pin) {
      kp = _kp;
      ki = _ki;
      kd = _kd;
      period = 300;
      MOSFET = _mosfet_pin;
      time = millis();
      temp_previous_error = 0;
      PID_p = 0;
      PID_i = 0;
      PID_d = 0;
    }

    void update(float _setpoint, float current_temperature) {
      if (millis() > time + period) {}
        time = millis();
        setpoint = _setpoint;
        float tempError = setpoint - current_temperature;
        PID_p = kp * tempError;
        float temp_diference = tempError - temp_previous_error;
        PID_d = kd * ((tempError - temp_previous_error) / period);

        if (-3 < tempError && tempError < 3) {
          PID_i = PID_i + (ki * tempError);
        } else {
          PID_i = 0;
        }

        float PID_total = PID_p + PID_i + PID_d;
        PID_total = map(PID_total, -150, 150, 0, 150);

        if (PID_total < 20) {
          PID_total = 20;
        }
        if (PID_total > 200) {
          PID_total = 200;
        }

        analogWrite(MOSFET, PID_total + 30);
        Serial.println(PID_total + 30);
        temp_previous_error = tempError;
      
    }
    private:
    float kp;
    float ki;
    float kd;
    float period;
    float time;
    float setpoint;
    float temp_previous_error;
    float PID_p;
    float PID_i;
    float PID_d;
    int   MOSFET;
};
#endif