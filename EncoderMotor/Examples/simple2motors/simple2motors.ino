#include <EncoderMotor.h>
motor m1(19,13,10,9,11),m2(18,5,7,6,4);
void setup() {
  // put your setup code here, to run once:
  m1.setPWM(200);//Sets pwm of that wheel
  m1.forward();
  m1.setDirection_angle(3.14);
  m1.setAngular_offset(3.14);
  Serial.begin(115200);
  m2.setPWM(200);
  m2.setDirectional_offset(-1);//Multiplies Encoder Value with -1 default is 1
  m2.forward();
  m2.setDirection_angle(2*3.14/6);//Divides encoderValu with cos(Direction_angle + angular offset)

}
double prev = 0;
void loop() {
  double curr = m1.getReadings();//gets modified encoderValue
  Serial.println(curr-prev);
  prev = curr;
  delay(100);

}
