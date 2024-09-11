/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-joystick
 */

#define VRX_PIN  36 // ESP32 pin GPIO36 (ADC0) connected to VRX pin
#define VRY_PIN  39 // ESP32 pin GPIO39 (ADC0) connected to VRY pin
#define SW_PIN   4  // ESP32 pin GPIO4 connected to SW pin

int valueX = 0; // to store the X-axis value
int valueY = 0; // to store the Y-axis value
bool buttonState = 0; // to store the button state

void setup() {
  Serial.begin(9600);

  // Set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);

  // Set the ADC resolution to 12-bit (0-4095)
  analogSetWidth(12);

  // Set the VRX_PIN and VRY_PIN as input
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);

  // Set the SW_PIN as input with internal pull-up resistor
  pinMode(SW_PIN, INPUT_PULLUP);

  // print the message to Serial Monitor on Arduino IDE
  Serial.println("ESP32 Joystick Test");
}

void loop() {
  // read X and Y analog values
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
  buttonState = digitalRead(SW_PIN);

  // print data to Serial Monitor on Arduino IDE
  Serial.print("Button = ");
  Serial.print(buttonState);
  Serial.print("x = ");
  Serial.print(valueX);
  Serial.print(", y = ");
  Serial.println(valueY);
  delay(200);
}

