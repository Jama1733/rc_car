#include <Servo.h>

Servo steering;

const int servo_pin = 2;
const int r_button = 7;
const int l_button = 4;

int r_state = 0;
int l_state = 0;

void setup() {
  // put your setup code here, to run once:
  steering.attach(servo_pin);

  pinMode(r_button, INPUT);
  pinMode(l_button, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  r_state = digitalRead(r_button);
  l_state = digitalRead(l_button);

  if (r_state == HIGH){
    steering.write(180);
  }else if (l_state == HIGH){
    steering.write(0);
  }else{
    steering.write(90);
  }
}
