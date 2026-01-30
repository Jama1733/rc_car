#include <Servo.h>

Servo steering;

const int x_pin = A3;
const int y_pin = A5;
const int servo_pin = 3;

int x_val = 0;
int y_val = 0;

int steering_angle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  steering.attach(servo_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  x_val = analogRead(x_pin);
  delay(100);
  y_val = analogRead(y_pin);

  Serial.print("X-AXIS  ");
  Serial.println(x_val);

  Serial.print("Y-AXIS  ");
  Serial.print(y_val);

  steering_angle = map(x_val, 0, 1023, 0, 180);
  steering.write(steering_angle);

}
