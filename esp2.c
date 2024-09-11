#define buttona 13 // Yes, this is in the correct order, ask espressif why
#define buttonb 12  
#define buttonc 14
#define LED_BUILTIN 2

bool buttona_state = false;
bool buttonb_state = false;
bool buttonc_state = false;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(buttona, INPUT);
  pinMode(buttonb, INPUT);
  pinMode(buttonc, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttona_state = digitalRead(buttona);
  buttonb_state = digitalRead(buttonb);
  buttonc_state = digitalRead(buttonc);

  if (buttona_state || buttonb_state || buttonc_state) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
}