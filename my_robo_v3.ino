#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <SoftwareSerial.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

SoftwareSerial myserial(A0, A1); //(rx, tx)
Adafruit_DCMotor *motor1 = AFMS.getMotor(1),
                  *motor2 = AFMS.getMotor(2),
                   *motor3 = AFMS.getMotor(3),
                    *motor4 = AFMS.getMotor(4);

Servo servo1, servo2;

// constants
char BLUETOOTH_CMD_DELIMETER = '\n';
String MOVE_PREFIX = "M:";
String ACT_PREFIX = "A:";
String MOVE_SPEED_PREFIX = "M:S:";
String ACT_SPEED_PREFIX = "A:S:";
int SERVO_STEP_SIZE = 5;
String lastServoCommand = "";


void setup() {
  Serial.begin(9600);
  Serial.println("test!");
  initServo();
  initMotor();
  initBluetooth();
}

void loop() {
  if (myserial.available()) {
    String  command = myserial.readStringUntil(BLUETOOTH_CMD_DELIMETER);
    Serial.println("Received command: " + command);
    process_commmand(command);
  }
  performServoActivityIfAvaliable();
}

// functions

void initServo() {
  servo1.attach(9);
  servo2.attach(10);
}

void initMotor() {
  AFMS.begin();
  String initial_speed = "200";
  setSpeed(initial_speed);
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
}


void initBluetooth() {
  myserial.begin(9600);
}



//// movement commands

void process_commmand(String command) {
  if (command.startsWith(MOVE_SPEED_PREFIX)) {
    //Serial.println(command);
    String commandVal = command.substring(MOVE_SPEED_PREFIX.length());
    setSpeed(commandVal);
  }
  else if (command.startsWith(MOVE_PREFIX)) {
    String commandVal = command.substring(MOVE_PREFIX.length());
    //  Serial.print("command val :" + commandVal);
    move_commands(commandVal);
  } else if (command.startsWith(ACT_PREFIX)) {
    lastServoCommand = command.substring(ACT_PREFIX.length());
    //Serial.print("command val :" + lastServoCommand);
  }

}

// moving
void move_commands(String command)
{
  if (command == "F") { // forward
    moveForward();
  }
  else if (command == "B") { //back
    moveBackward();
  }
  else if (command == "R") { //right
    turnRight();
  }
  else if (command == "L") { // left
    turnLeft();
  }
  else if (command == "S") {
    moveStop();
  }
  else {
    moveStop();
  }

}


void moveForward() {
  Serial.write("forwarding");
  motor1->run(FORWARD);
  motor4->run(FORWARD);
  motor2->run(FORWARD);
  motor3->run(FORWARD);
}

void moveBackward() {
  motor1->run(BACKWARD);
  motor4->run(BACKWARD);
  motor2->run(BACKWARD);
  motor3->run(BACKWARD);
}


void turnLeft() {
  motor3->run(FORWARD);
  motor4->run(FORWARD);
  motor1->run(BACKWARD);
  motor2->run(BACKWARD);
}

void turnRight() {
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor3->run(BACKWARD);
  motor4->run(BACKWARD); 
}


void moveStop() {
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor1->run(RELEASE);
  motor4->run(RELEASE);
}


void setSpeed(String speedness) {
  int speedval = speedness.toInt();
  motor1->setSpeed(speedval);
  motor2->setSpeed(speedval);
  motor3->setSpeed(speedval);
  motor4->setSpeed(speedval);
}


// servo actions


void performServoActivityIfAvaliable() {
  if (lastServoCommand == "F") { // forward
    angle_update(servo1, false);
  }
  else if (lastServoCommand == "B") { //back
    angle_update(servo1, true);
  }
  else if (lastServoCommand == "R") { //right
    angle_update(servo2, false);
  }
  else if (lastServoCommand == "L") { // left
    angle_update(servo2, true);
  }
  else {
    //Serial.print("setting empty  servo");
    lastServoCommand = "";
  }

}

void angle_update(Servo sev , bool increase) {
  int currentAngle = sev.read();
  if ( ((increase == true && currentAngle < 180) || (increase == false && currentAngle > 0)) && lastServoCommand != "" ) {
    Serial.write(currentAngle);
    sev.write(currentAngle + (SERVO_STEP_SIZE * (increase ? 1 : -1)));
    delay(50);
  }
}
