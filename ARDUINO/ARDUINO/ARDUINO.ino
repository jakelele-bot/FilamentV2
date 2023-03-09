


// Define the pins for the rotary encoder
#define CLK A0
#define DT A1
#define SW A2

// Define the maximum and minimum values for each parameter
#define MAX_DISTANCE 100
#define MIN_DISTANCE 0
#define MAX_THICKNESS 10
#define MIN_THICKNESS 0
#define MAX_HEIGHT 50
#define MIN_HEIGHT 0

// Class for each parameter with its own value and limits
class Parameter {
  private:
    int _value;
    int _minValue;
    int _maxValue;
  public:
    Parameter(int minValue, int maxValue) {
      _value = minValue;
      _minValue = minValue;
      _maxValue = maxValue;
    }
    void increment() {
      if (_value < _maxValue) {
        _value++;
      }
    }
    void decrement() {
      if (_value > _minValue) {
        _value--;
      }
    }
    int getValue() {
      return _value;
    }
};

// Initialize the rotary encoder object
Encoder encoder(CLK, DT);

// Initialize the parameters with their respective limits
Parameter distance(MIN_DISTANCE, MAX_DISTANCE);
Parameter thickness(MIN_THICKNESS, MAX_THICKNESS);
Parameter height(MIN_HEIGHT, MAX_HEIGHT);

// Initialize the current parameter and the previous state of the rotary encoder switch
int currentParam = 1;
int prevSwitchState = HIGH;

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