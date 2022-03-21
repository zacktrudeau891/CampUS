#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "functions.h"

#if defined(ARDUINO_OpenCR) // When using official ROBOTIS board with DXL circuit.
  // For OpenCR, there is a DXL Power Enable pin, so you must initialize and control it.
  #define DXL_SERIAL   Serial3
  #define DEBUG_SERIAL Serial
  const uint8_t DXL_DIR_PIN = 84; // OpenCR Board's DIR PIN.
#endif

#define FRONT_LEFT_SERVO 0
#define FRONT_RIGHT_SERVO 1
#define REAR_LEFT_SERVO 2
#define REAR_RIGHT_SERVO 3

#define PIN_FRONT_LEFT_SERVO_PWM 11
#define PIN_FRONT_RIGHT_SERVO_PWM 10
#define PIN_REAR_LEFT_SERVO_PWM 9
#define PIN_REAR_RIGHT_SERVO_PWM 6

//Movement modes
#define WAIT_MODE 0
#define EXTENSION_MODE 1
#define RETRACTION_MODE 2
uint8_t mode = WAIT_MODE;


Servo servo_test = Servo();
int angle = 0;

#define DXL_ID_REAR_LEFT 2
#define DXL_ID_REAR_RIGHT 9
#define DXL_ID_FRONT_LEFT 23
#define DXL_ID_FRONT_RIGHT 3

#define FRONT_LEFT_RETRACTED 993
#define FRONT_RIGHT_RETRACTED 0
#define REAR_LEFT_RETRACTED 2850
#define REAR_RIGHT_RETRACTED 0

const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
Servo servomotors[4] = {};

void setup() {
  //Associate pins
  pinMode(PIN_FRONT_LEFT_SERVO_PWM, INPUT);
  pinMode(PIN_FRONT_RIGHT_SERVO_PWM,INPUT);
  pinMode(PIN_REAR_LEFT_SERVO_PWM, INPUT);
  pinMode(PIN_REAR_RIGHT_SERVO_PWM, INPUT);

  
  //Servomotors
  

  servomotors[FRONT_LEFT_SERVO].attach(PIN_FRONT_LEFT_SERVO_PWM);
  servomotors[FRONT_RIGHT_SERVO].attach(PIN_FRONT_RIGHT_SERVO_PWM);
  servomotors[REAR_LEFT_SERVO].attach(PIN_REAR_LEFT_SERVO_PWM);
  servomotors[REAR_RIGHT_SERVO].attach(PIN_REAR_RIGHT_SERVO_PWM);

  //Steppers
  pinMode(BDPIN_DXL_PWR_EN, OUTPUT);
  digitalWrite(BDPIN_DXL_PWR_EN, HIGH);

  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID_FRONT_LEFT);
  dxl.ping(DXL_ID_FRONT_RIGHT);
  dxl.ping(DXL_ID_REAR_LEFT);
  dxl.ping(DXL_ID_REAR_RIGHT);

  // Turn off torque when configuring items in EEPROM area
  /*dxl.torqueOff(DXL_ID2);
  dxl.setOperatingMode(DXL_ID2, OP_POSITION);
  dxl.torqueOn(DXL_ID2);
  dxl.setGoalPosition(DXL_ID2, 0);*/


  delay(5000);
  dxl.torqueOff(DXL_ID_FRONT_LEFT);
  dxl.setOperatingMode(DXL_ID_FRONT_LEFT, OP_POSITION);
  dxl.torqueOn(DXL_ID_FRONT_LEFT);

  dxl.torqueOff(DXL_ID_FRONT_RIGHT);
  dxl.setOperatingMode(DXL_ID_FRONT_RIGHT, OP_POSITION);
  dxl.torqueOn(DXL_ID_FRONT_RIGHT);
  
  dxl.torqueOff(DXL_ID_REAR_LEFT);
  dxl.setOperatingMode(DXL_ID_REAR_LEFT, OP_POSITION);
  dxl.torqueOn(DXL_ID_REAR_LEFT);
  
  dxl.torqueOff(DXL_ID_REAR_RIGHT);
  dxl.setOperatingMode(DXL_ID_REAR_RIGHT, OP_POSITION);
  dxl.torqueOn(DXL_ID_REAR_RIGHT);
  
  
}

void loop() {
<<<<<<< Updated upstream
    
    encoderPosition(dxl,DXL_ID_FRONT_LEFT);
  DEBUG_SERIAL.println(motor_position);

  encoderPosition(dxl,DXL_ID_FRONT_RIGHT);
  DEBUG_SERIAL.println(motor_position);
  
  encoderPosition(dxl,DXL_ID_REAR_LEFT);
  DEBUG_SERIAL.println(motor_position);
  
  encoderPosition(dxl,DXL_ID_REAR_RIGHT);
  DEBUG_SERIAL.println(motor_position);
  
=======
  for(int i=0; i<4;i++){
    DEBUG_SERIAL.println(getServoPosition(servomotors[i]));
  }
>>>>>>> Stashed changes
  /*encoderPosition(dxl, DXL_ID2);
  

  DEBUG_SERIAL.println(mode);
  DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID2));
  if(mode == WAIT_MODE){
    extension(dxl,DXL_ID2,-10);
    DEBUG_SERIAL.println(mode);
  }

  if(mode == EXTENSION_MODE && motor_position>=2048){
    DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID2));
    finish(dxl,DXL_ID2);
    delay(500);
    retraction(dxl, DXL_ID2,-10);
  }
  if(mode == RETRACTION_MODE && motor_position<2048){
    DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID));
    finish(dxl,DXL_ID2);
    delay(500);
    extension(dxl, DXL_ID2,-10);
  }*/
}