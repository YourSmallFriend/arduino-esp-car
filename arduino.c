#include <FastLED.h>
#define NUM_LEDS 10

const int motor2pin1 = 2;
const int motor2pin2 = 4;

const int motor1pin1 = 7;
const int motor1pin2 = 8;

const int motor1pwm = 10;
const int motor2pwm = 9;

const int trigPin = 12;
const int echoPin = 6;

const int maxDistance = 150;

const int contrastSensor1 = 11;
const int contrastSensor2 = 13;

#define DATA_PIN 3

CRGB leds[NUM_LEDS];

void setup()
{
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(motor2pwm, OUTPUT);
  pinMode(motor1pwm, OUTPUT);
  //(Optional)

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(contrastSensor1, INPUT);
  pinMode(contrastSensor2, INPUT);

  Serial.begin(9600);
  Serial.println("Cool Car Project 9000");

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); // GRB ordering is typical
}

const int max_power = 85;
const int turn_distance = 20;
const int hard_turn_distance = 10; // this is a full rotate.
float duration, distance;

void loop()
{
  bool contrast1 = digitalRead(contrastSensor1); // Right 
  bool contrast2 = digitalRead(contrastSensor2); // Left

  Serial.print("Contrast 1: ");
  Serial.print(contrast1);
  Serial.print(" Contrast 2: ");
  Serial.print(contrast2);

  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  if (distance > maxDistance)
  {
    distance = maxDistance;
  }

  // Speed between 50 (for low distance) and 255 (for max distance)
  int pwmValue = map(distance, 0, maxDistance, 0, max_power);

  // Controlling speed (0  = off and 255 = max speed):
  //(Optional)
  //(Optional)


  if (contrast2){
    // Right
    analogWrite(motor1pwm, 0);
    analogWrite(motor2pwm, max_power);

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

  }
  else if (contrast1){
    // Left
    analogWrite(motor1pwm, max_power);
    analogWrite(motor2pwm, 0);

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  }

  bool turn = distance < turn_distance; // soft turning by lowering the speed of one of the motors
  if (turn)
  {
    analogWrite(motor1pwm, max_power);
    analogWrite(motor2pwm, pwmValue);

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  }

  // This is emergency like turning
  bool hard_turn = distance < hard_turn_distance;
  if (distance < hard_turn_distance)
  {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

    analogWrite(motor1pwm, max_power);
    analogWrite(motor2pwm, max_power);
  }
  else if (!turn && !hard_turn && !contrast1 && !contrast2)
  {
    analogWrite(motor1pwm, max_power);
    analogWrite(motor2pwm, max_power);

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  }


  Serial.print(" Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Leds
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = turn ? CRGB::Red : leds[i];
  }

  // Turn every led red if it is turning
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = hard_turn ? CRGB::Green : leds[i];
  }

  FastLED.show();



  delay(100);
}