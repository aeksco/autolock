//www.elegoo.com
//2016.12.8

// Define RBG LED Pins
#define BLUE 3
#define GREEN 4
#define RED 6

// Sonic Distance Sensor Pins
#define trigPin 21
#define echoPin 22

//Potentiometer pins
#define POTENTIOMETER_READ 20

// Pushbutton Pins
#define PUSHBUTTON_READ 19

// Define Proximity Sensor pins
#define DISTANCE_READ 23

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(PUSHBUTTON_READ, INPUT);

  // Serial.begin to debug proximity sensor
  Serial.begin(9600);

}

// define variables
int redValue;
int greenValue;
int blueValue;

// Potentiometer reading val
long potVal;
int triggerDistance;

// Button Reading Value
int buttonToggled = 0;
int buttonHeldTime = 0;
int previousButtonState = 0;

void loop() {
  long duration, distance;
  int buttonState;

  potVal = analogRead(POTENTIOMETER_READ);
  //  Serial.print(potVal);
  //  Serial.println(" pot val");
  triggerDistance = potVal / 10;

  // READ PUSHBUTTON VALUE
  buttonState = digitalRead(PUSHBUTTON_READ);

  Serial.print(buttonState);
  Serial.println(" button state");

  //  Serial.print(buttonToggled);
  //  Serial.println(" button toggled");

  //  Serial.print(buttonHeldTime);
  //  Serial.println(" button held time");

  // If button pressed, check if held for 1000ms
  if (buttonState == 1 && buttonToggled == 0 && previousButtonState == 0) {
    buttonHeldTime += 50;
    if (buttonHeldTime >= 1000) {
      Serial.println("buttonToggled = 1");
      buttonToggled = 1;
      previousButtonState = 1;
      buttonHeldTime = 0;
    }
  } else if (buttonState == 1 && buttonToggled == 1 && previousButtonState == 0) {
    buttonHeldTime += 50;
    if (buttonHeldTime >= 1000) {
      Serial.println("buttonToggled = 0");
      buttonToggled = 0;
      previousButtonState = 1;
      buttonHeldTime = 0;
    }
  }

  // If button is not pressed, reset the buttonHeldTime and set the previousButtonState to 0
  if (buttonState == 0) {
    buttonHeldTime = 0;
    previousButtonState = 0;
    Serial.println("Reset buttonHeldTime");
  }

  // Updates previousButtonState
  //  Serial.print("currentButtonState: ");
  //  Serial.println(buttonState);
  //  previousButtonState = buttonState;

  // Check if button has been toggled - turn off detection
  if (buttonToggled == 1) {
    analogWrite(RED, 125);
    analogWrite(GREEN, 125);
    analogWrite(BLUE, 125);
  }

  // If button is toggled, wait one tick and return
  if (buttonToggled == 1) {
    delay(50);
    return;
  }

  //  Serial.println("CHECK DISTANCE");
  digitalWrite(trigPin, LOW);  // Added this line
  delay(2); // Added this line
  digitalWrite(trigPin, HIGH);

  //  delayMicroseconds(1000); - Removed this line
  delay(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  if (distance < triggerDistance) {  // This is where the LED On/Off happens
    analogWrite(RED, 0);
    analogWrite(GREEN, 255); // When the Red condition is met, the Green LED should turn off
    analogWrite(BLUE, 0);
  }
  else {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
  }
  //  if (distance >= 200 || distance <= 0){
  //    Serial.println("Out of range");
  //  }
  //  else {
  //    Serial.print(distance);
  //    Serial.println(" cm");
  //  }

  // Wait on tick
  delay(50);
}
