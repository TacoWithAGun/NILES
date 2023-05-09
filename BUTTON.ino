// Define the pin connected to the pushbutton
const int buttonPin = 34;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set the button pin as an input with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the value of the pushbutton
  int buttonValue = digitalRead(buttonPin);

  // Print the value of the pushbutton to the serial monitor
  Serial.println(buttonValue);

  // Wait a short time before reading the button value again
  delay(500);
}