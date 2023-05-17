// Button
int buttonPin = 34;

// Motor DC
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;


// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  //set the Button as input sign
  pinMode(buttonPin, INPUT_PULLUP);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {

  int buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);

  if (buttonValue == 0)
  {// Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  }

  else
  
  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(5);
  

  // Move DC motor backwards at maximum speed
  //Serial.println("Moving Backwards");
  //digitalWrite(motor1Pin1, HIGH);
  //digitalWrite(motor1Pin2, LOW); 
  //delay(2000);

}