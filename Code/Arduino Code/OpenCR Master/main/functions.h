#include <Servo.h>
#include <Dynamixel2Arduino.h>
int motor_position;
//Useful functions for movement sequence
void extensionFrontLeft(Dynamixel2Arduino dxl, int id);
void extensionFrontRight(Dynamixel2Arduino dxl, int id);
void extensionRearLeft(Dynamixel2Arduino dxl, int id);
void extensionRearRight(Dynamixel2Arduino dxl, int id);

void retractionFrontLeft(Dynamixel2Arduino dxl, int id);
void retractionFrontRight(Dynamixel2Arduino dxl, int idn);
void retractionRearLeft(Dynamixel2Arduino dxl, int id);
void retractionRearRight(Dynamixel2Arduino dxl, int id);

void raiseFrontLeft(Dynamixel2Arduino dxl, int id);
void raiseFrontRight(Dynamixel2Arduino dxl, int id);
void raiseRearLeft(Dynamixel2Arduino dxl, int id);
void raiseRearRight(Dynamixel2Arduino dxl, int id);

void pullFrontLeft(Dynamixel2Arduino dxl, int id);
void pullFrontRight(Dynamixel2Arduino dxl, int id);
void pullRearLeft(Dynamixel2Arduino dxl, int id);
void pullRearRight(Dynamixel2Arduino dxl, int id);


void robotStep(Dynamixel2Arduino dxl, int idFL,int idFR,int idRL,int idRR,int direction, int speed);
void encoderPosition(Dynamixel2Arduino dxl, int id);
int encoderCount(Dynamixel2Arduino dxl, int id);
void findLegMode(Dynamixel2Arduino dxl, int id);

void controlMagnet(bool power, int magnet);
void home(Servo servo[],Dynamixel2Arduino dxl);
void init(Servo servomotors[],Dynamixel2Arduino dxl);

void setServoPosition(Servo servo, int angle);
int getServoPosition(Servo servo);

/*
 * Fully extends front left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionFrontLeft(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, nbTurnsFrontLeft*4096+FRONT_LEFT_EXTENDED);

  if(!synchro){while(dxl.getPresentPosition(id)>nbTurnsFrontLeft*4096+FRONT_LEFT_EXTENDED+50||dxl.getPresentPosition(id)<nbTurnsFrontLeft*4096+FRONT_LEFT_EXTENDED-50){};};
  frontLeftMode = EXTENDED;
}

/*
 * Fully extends front right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionFrontRight(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, -nbTurnsFrontRight*4096+FRONT_RIGHT_EXTENDED);
  if(!synchro){while(dxl.getPresentPosition(id)>-nbTurnsFrontRight*4096+FRONT_RIGHT_EXTENDED+50||dxl.getPresentPosition(id)<-nbTurnsFrontRight*4096+FRONT_RIGHT_EXTENDED-50){};};
  frontRightMode = EXTENDED;
}

/*
 * Fully extends rear left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionRearLeft(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, nbTurnsRearLeft*4096+REAR_LEFT_EXTENDED);
  if(!synchro){while(dxl.getPresentPosition(id)>nbTurnsRearLeft*4096+REAR_LEFT_EXTENDED+50||dxl.getPresentPosition(id)<nbTurnsRearLeft*4096+REAR_LEFT_EXTENDED-50){};};
  rearLeftMode = EXTENDED;
}

/*
 * Fully extends rear right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionRearRight(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, -(nbTurnsRearRight*4096-REAR_RIGHT_EXTENDED));
  if(!synchro){while(dxl.getPresentPosition(id)>-nbTurnsRearRight*4096+REAR_RIGHT_EXTENDED+50||dxl.getPresentPosition(id)<-nbTurnsRearRight*4096+REAR_RIGHT_EXTENDED-50){};};
  rearRightMode = EXTENDED;
}


/*
 * Fully retracts front left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void retractionFrontLeft(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, nbTurnsFrontLeft*4096+FRONT_LEFT_RETRACTED);
  if(!synchro){while(dxl.getPresentPosition(id)>nbTurnsFrontLeft*4096+FRONT_LEFT_RETRACTED+50||dxl.getPresentPosition(id)<nbTurnsFrontLeft*4096+FRONT_LEFT_RETRACTED-50){};};
  frontLeftMode = RETRACTED;
}

/*
 * Fully retracts front right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void retractionFrontRight(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, -nbTurnsFrontRight*4096+FRONT_RIGHT_RETRACTED);
  if(!synchro){while(dxl.getPresentPosition(id)>-nbTurnsFrontRight*4096+FRONT_RIGHT_RETRACTED+50||dxl.getPresentPosition(id)<-nbTurnsFrontRight*4096+FRONT_RIGHT_RETRACTED-50){};};
  frontRightMode = RETRACTED;
}


/*
 * Fully retracts rear left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void retractionRearLeft(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, nbTurnsRearLeft*4096+REAR_LEFT_RETRACTED);
  if(!synchro){while(dxl.getPresentPosition(id)>nbTurnsRearLeft*4096+REAR_LEFT_RETRACTED+50||dxl.getPresentPosition(id)<nbTurnsRearLeft*4096+REAR_LEFT_RETRACTED-50){};};
  rearLeftMode = RETRACTED;
}

/*
 * Fully retracts rear right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void retractionRearRight(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, -nbTurnsRearRight*4096+REAR_RIGHT_RETRACTED);
  if(!synchro){while(dxl.getPresentPosition(id)>-nbTurnsRearRight*4096+REAR_RIGHT_RETRACTED+50||dxl.getPresentPosition(id)<-nbTurnsRearRight*4096+REAR_RIGHT_RETRACTED-50){};};
  rearRightMode = RETRACTED;
}

/*
 * Fully raises front left leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseFrontLeft(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, nbTurnsFrontLeft*4096+FRONT_LEFT_RAISED);
  if(!synchro){while(dxl.getPresentPosition(id)>nbTurnsFrontLeft*4096+FRONT_LEFT_RAISED+50||dxl.getPresentPosition(id)<nbTurnsFrontLeft*4096+FRONT_LEFT_RAISED-50){};};
  frontLeftMode = RAISED;
}

/*
 * Fully raises front right leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseFrontRight(Dynamixel2Arduino dxl, int id){
   dxl.setGoalPosition(id, -nbTurnsFrontRight*4096+FRONT_RIGHT_RAISED);
   if(!synchro){while(dxl.getPresentPosition(id)>-nbTurnsFrontRight*4096+FRONT_RIGHT_RAISED+50||dxl.getPresentPosition(id)<-nbTurnsFrontRight*4096+FRONT_RIGHT_RAISED-50){};};
   frontRightMode = RAISED;
}

/*
 * Fully raises rear left leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseRearLeft(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, nbTurnsRearLeft*4096+REAR_LEFT_RAISED);
  if(!synchro){while(dxl.getPresentPosition(id)>nbTurnsRearLeft*4096+REAR_LEFT_RAISED+50||dxl.getPresentPosition(id)<nbTurnsRearLeft*4096+REAR_LEFT_RAISED-50){};};
  rearLeftMode = RAISED;
}

/*
 * Fully raises rear right leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseRearRight(Dynamixel2Arduino dxl, int id){
  dxl.setGoalPosition(id, -nbTurnsRearRight*4096+REAR_RIGHT_RAISED);
  if(!synchro){while(dxl.getPresentPosition(id)> -nbTurnsRearRight*4096+REAR_RIGHT_RAISED+50||dxl.getPresentPosition(id)< -nbTurnsRearRight*4096+REAR_RIGHT_RAISED-50){};};
  rearRightMode = RAISED;
}

void pullFrontLeft(Dynamixel2Arduino dxl, int id)
{
  if(frontLeftMode==RAISED)
  {
    retractionFrontLeft(dxl,id);
    digitalWrite(12,HIGH);
    delay(500);
  }
  dxl.setGoalPosition(id,dxl.getPresentPosition(DXL_ID_FRONT_LEFT)-500);
}

void pullFrontRight(Dynamixel2Arduino dxl, int id)
{
  if(frontRightMode==RAISED)
  {
    retractionFrontRight(dxl,id);
    digitalWrite(13,HIGH);
    delay(500);
  }
  dxl.setGoalPosition(id,dxl.getPresentPosition(DXL_ID_FRONT_RIGHT)-500);
}

void pullRearLeft(Dynamixel2Arduino dxl, int id)
{
  if(rearLeftMode==RAISED)
  {
    retractionRearLeft(dxl,id);
    digitalWrite(10,HIGH);
    delay(500);
  }
  dxl.setGoalPosition(id,dxl.getPresentPosition(DXL_ID_REAR_LEFT)-500);
}

void pullRearRight(Dynamixel2Arduino dxl, int id)
{
  if(rearRightMode==RAISED)
  {
    retractionRearRight(dxl,id);
    digitalWrite(11,HIGH);
    delay(500);
  }
  dxl.setGoalPosition(id,dxl.getPresentPosition(DXL_ID_REAR_RIGHT)+500);
}
/*
 *This function completes one full robot step in the inputede direction 
 * 
 * @param dxl dynamixel object for motor control
 * @param idFL robot's front left motor id
 * @param idFR robot's front right motor id
 * @param idRL robot's rear left motor id
 * @param idRR robot's rear right motor id
 * @param direction movement direction (±1)
 * @param speed desired speed for motor movement (in percentage)
 */
void robotStep(Dynamixel2Arduino dxl, int direction){
    if(direction >=0){
      if(rearLeftMode!=RETRACTED){
        digitalWrite(10,LOW);
        delay(1500);
        retractionRearLeft(dxl,DXL_ID_REAR_LEFT);
        digitalWrite(10,HIGH);
        delay(1500);
        
      }
      
      if(rearRightMode!=RETRACTED){
        digitalWrite(11,LOW);
        delay(1500);
        retractionRearRight(dxl, DXL_ID_REAR_RIGHT);
        digitalWrite(11,HIGH);;
        delay(1500);
        
      }
      
      if(frontLeftMode!=EXTENDED){
        digitalWrite(12,LOW);
        delay(1500);
        raiseFrontLeft(dxl,DXL_ID_FRONT_LEFT);
        nbTurnsFrontLeft++;
        pullFrontRight(dxl,DXL_ID_FRONT_RIGHT);
        delay(1000);
        extensionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
        digitalWrite(12,HIGH);;
        delay(1500);
      }
      
      if(frontRightMode!=EXTENDED){
        digitalWrite(13,LOW);
        delay(1500);
        raiseFrontRight(dxl,DXL_ID_FRONT_RIGHT);
        pullFrontLeft(dxl,DXL_ID_FRONT_LEFT);
        delay(1000);
        extensionFrontRight(dxl,DXL_ID_FRONT_RIGHT);
        digitalWrite(13,HIGH);
        delay(1000);
        extensionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
        delay(1500);
      }
      
      nbTurnsRearLeft++;
      nbTurnsFrontRight++;
      nbTurnsRearRight++;

      synchro=true;
      retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
      retractionFrontRight(dxl,DXL_ID_FRONT_RIGHT);
      extensionRearLeft(dxl,DXL_ID_REAR_LEFT);
      extensionRearRight(dxl,DXL_ID_REAR_RIGHT);
      synchro=false;

      delay(4000);
    }
    else{
      if(frontLeftMode!=RETRACTED){
        digitalWrite(12,LOW);
        delay(1500);
        retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
        digitalWrite(12,HIGH);
        delay(1500);
      }
      
      if(frontRightMode!=RETRACTED){
        digitalWrite(13,LOW);
        delay(1500);
        retractionFrontRight(dxl, DXL_ID_FRONT_RIGHT);
        digitalWrite(13,HIGH);
        delay(1500);
      }
     
      if(rearLeftMode!=EXTENDED){
        digitalWrite(10,LOW);
        delay(1500);
        raiseRearLeft(dxl,DXL_ID_REAR_LEFT);
        pullRearRight(dxl,DXL_ID_REAR_RIGHT);
        delay(1000);
        extensionRearLeft(dxl,DXL_ID_REAR_LEFT);
        digitalWrite(10,HIGH);
        delay(1500);
      }
      
      if(rearRightMode!=EXTENDED){
        digitalWrite(11,LOW);
        delay(1500);
        raiseRearRight(dxl,DXL_ID_REAR_RIGHT);
        pullRearLeft(dxl,DXL_ID_REAR_LEFT);
        delay(1000);
        extensionRearRight(dxl,DXL_ID_REAR_RIGHT);
        digitalWrite(11,HIGH);
        delay(1500);
        extensionRearLeft(dxl,DXL_ID_REAR_LEFT);
      }
      
      nbTurnsFrontRight--;
      nbTurnsRearLeft--;
      nbTurnsRearRight--;

      synchro=true;
      retractionRearLeft(dxl,DXL_ID_REAR_LEFT);
      retractionRearRight(dxl,DXL_ID_REAR_RIGHT);
      extensionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
      extensionFrontRight(dxl,DXL_ID_FRONT_RIGHT);
      synchro = false;
      
      nbTurnsFrontLeft--;
      delay(4000);
    }
}

/*
 * Reads the encoder value of selected motor to find the position in a single motor turn
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void encoderPosition(Dynamixel2Arduino dxl, int id){
  motor_position = dxl.getPresentPosition(id);
  motor_position = abs(motor_position) % 4096;
}

/*
 * Reads and returns the encoder value of selected motor
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * 
 * @return encoder value
 */
int encoderCount(Dynamixel2Arduino dxl, int id){
  return dxl.getPresentPosition(id);
}

void setServoPosition(Servo servo, int angle){
  servo.write(angle);

  delay(200);
}

int getServoPosition(Servo servo){
  return servo.read();
}

void setAngle(Servo servomotors[],Dynamixel2Arduino dxl, int angle)
{
  if (angle >= 0)
  {
    digitalWrite(12,LOW);
    delay(1000);
    raiseFrontLeft(dxl,DXL_ID_FRONT_LEFT);
    servomotors[FRONT_LEFT_SERVO].write(FRONT_LEFT_SERVO_HOME + angle);
    delay(500);
    retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
    digitalWrite(12,HIGH);
    delay(1000);

    digitalWrite(11,LOW);
    delay(1000);
    raiseRearRight(dxl,DXL_ID_REAR_RIGHT);
    servomotors[REAR_RIGHT_SERVO].write(REAR_RIGHT_SERVO_HOME + angle);
    delay(500);
    retractionRearRight(dxl,DXL_ID_REAR_RIGHT);
    digitalWrite(11,HIGH);
    delay(1000);

    digitalWrite(13,LOW);
    delay(1000);
    raiseFrontRight(dxl,DXL_ID_FRONT_RIGHT);
    servomotors[FRONT_RIGHT_SERVO].write(FRONT_RIGHT_SERVO_HOME + angle);
    delay(500);
    retractionFrontRight(dxl,DXL_ID_FRONT_RIGHT);
    digitalWrite(13,HIGH);
    delay(1000);

    digitalWrite(10,LOW);
    delay(1000);
    raiseRearLeft(dxl,DXL_ID_REAR_LEFT);
    servomotors[REAR_LEFT_SERVO].write(REAR_LEFT_SERVO_HOME + angle);
    delay(500);
    retractionRearLeft(dxl,DXL_ID_REAR_LEFT);
    digitalWrite(10,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(13,LOW);
    delay(1000);
    raiseFrontRight(dxl,DXL_ID_FRONT_RIGHT);
    servomotors[FRONT_RIGHT_SERVO].write(FRONT_RIGHT_SERVO_HOME + angle);
    delay(500);
    retractionFrontRight(dxl,DXL_ID_FRONT_RIGHT);
    digitalWrite(13,HIGH);
    delay(1000);

    digitalWrite(10,LOW);
    delay(1000);
    raiseRearLeft(dxl,DXL_ID_REAR_LEFT);
    servomotors[REAR_LEFT_SERVO].write(REAR_LEFT_SERVO_HOME + angle);
    delay(500);
    retractionRearLeft(dxl,DXL_ID_REAR_LEFT);
    digitalWrite(10,HIGH);
    delay(1000);

    digitalWrite(12,LOW);
    delay(1000);
    raiseFrontLeft(dxl,DXL_ID_FRONT_LEFT);
    servomotors[FRONT_LEFT_SERVO].write(FRONT_LEFT_SERVO_HOME + angle);
    delay(500);
    retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
    digitalWrite(12,HIGH);
    delay(1000);

    digitalWrite(11,LOW);
    delay(1000);
    raiseRearRight(dxl,DXL_ID_REAR_RIGHT);
    servomotors[REAR_RIGHT_SERVO].write(REAR_RIGHT_SERVO_HOME + angle);
    delay(500);
    retractionRearRight(dxl,DXL_ID_REAR_RIGHT);
    digitalWrite(11,HIGH);
    delay(1000);
  }
}

void home(Servo servomotors[],Dynamixel2Arduino dxl){
    
    digitalWrite(12,LOW);
    delay(1000);
    raiseFrontLeft(dxl,DXL_ID_FRONT_LEFT);
    servomotors[FRONT_LEFT_SERVO].write(FRONT_LEFT_SERVO_HOME);
    delay(500);
    retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT);
    digitalWrite(12,HIGH);
    delay(1000);

   digitalWrite(13,LOW);
    delay(1000);
    raiseFrontRight(dxl,DXL_ID_FRONT_RIGHT);
    servomotors[FRONT_RIGHT_SERVO].write(FRONT_RIGHT_SERVO_HOME);
    delay(500);
    retractionFrontRight(dxl,DXL_ID_FRONT_RIGHT);
    digitalWrite(13,HIGH);
    delay(1000);

    digitalWrite(10,LOW);
    delay(1000);
    raiseRearLeft(dxl,DXL_ID_REAR_LEFT);
    servomotors[REAR_LEFT_SERVO].write(REAR_LEFT_SERVO_HOME);
    delay(500);
    retractionRearLeft(dxl,DXL_ID_REAR_LEFT);
    digitalWrite(10,HIGH);
    delay(1000);

    digitalWrite(11,LOW);
    delay(1000);
    raiseRearRight(dxl,DXL_ID_REAR_RIGHT);
    servomotors[REAR_RIGHT_SERVO].write(REAR_RIGHT_SERVO_HOME);
    delay(500);
    retractionRearRight(dxl,DXL_ID_REAR_RIGHT);
    digitalWrite(11,HIGH);
    delay(1000);
}

void controlMagnet(bool power, int pinmagnet){
  pinMode(pinmagnet, OUTPUT);

  if(power = 1){  
    digitalWrite(pinmagnet, HIGH); 
  }
  
  if(power = 0){  
    digitalWrite(pinmagnet, 0); 
  }  
}

/*
 * Finds if a leg is extended, raised or retracted
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void findLegMode(Dynamixel2Arduino dxl, int id){
    encoderPosition(dxl, id);

    if(id==DXL_ID_REAR_LEFT){
      if(abs(motor_position - REAR_LEFT_RETRACTED) < abs(motor_position - REAR_LEFT_EXTENDED) && abs(motor_position - REAR_LEFT_RETRACTED) < abs(motor_position - REAR_LEFT_RAISED)){
        rearLeftMode = RETRACTED;
      }
      else if(abs(motor_position - REAR_LEFT_EXTENDED) <abs(motor_position - REAR_LEFT_RETRACTED)  && abs(motor_position - REAR_LEFT_EXTENDED) < abs(motor_position - REAR_LEFT_RAISED)){
        rearLeftMode = EXTENDED;
      }
      else if(abs(motor_position - REAR_LEFT_RAISED) <abs(motor_position - REAR_LEFT_RETRACTED)  && abs(motor_position - REAR_LEFT_RAISED) < abs(motor_position - REAR_LEFT_EXTENDED)){
        rearLeftMode = RAISED;
      }
    }
    else if(id==DXL_ID_REAR_RIGHT){
      if(abs(motor_position - REAR_RIGHT_RETRACTED) < abs(motor_position - REAR_RIGHT_EXTENDED) && abs(motor_position - REAR_RIGHT_RETRACTED) < abs(motor_position - REAR_RIGHT_RAISED)){
        rearRightMode = RETRACTED;
      }
      else if(abs(motor_position - REAR_RIGHT_EXTENDED) <abs(motor_position - REAR_RIGHT_RETRACTED)  && abs(motor_position - REAR_RIGHT_EXTENDED) < abs(motor_position - REAR_RIGHT_RAISED)){
        rearRightMode = EXTENDED;
      }
      else if(abs(motor_position - REAR_RIGHT_RAISED) <abs(motor_position - REAR_RIGHT_RETRACTED)  && abs(motor_position - REAR_RIGHT_RAISED) < abs(motor_position - REAR_RIGHT_EXTENDED)){
        rearRightMode = RAISED;
      }
    }
    else if(id==DXL_ID_FRONT_LEFT){
      if(abs(motor_position - FRONT_LEFT_RETRACTED) < abs(motor_position - FRONT_LEFT_EXTENDED) && abs(motor_position - FRONT_LEFT_RETRACTED) < abs(motor_position - FRONT_LEFT_RAISED)){
        frontLeftMode = RETRACTED;
      }
      else if(abs(motor_position -FRONT_LEFT_EXTENDED) <abs(motor_position - FRONT_LEFT_RETRACTED)  && abs(motor_position -FRONT_LEFT_EXTENDED) < abs(motor_position - FRONT_LEFT_RAISED)){
        frontLeftMode = EXTENDED;
      }
      else if(abs(motor_position - FRONT_LEFT_RAISED) <abs(motor_position - FRONT_LEFT_RETRACTED)  && abs(motor_position - FRONT_LEFT_RAISED) < abs(motor_position - FRONT_LEFT_EXTENDED)){
        frontLeftMode = RAISED;
      }
    }
    else if(id==DXL_ID_FRONT_RIGHT){
      if(abs(motor_position - FRONT_RIGHT_RETRACTED) < abs(motor_position - FRONT_RIGHT_EXTENDED) && abs(motor_position - FRONT_RIGHT_RETRACTED) < abs(motor_position - FRONT_RIGHT_RAISED)){
        frontRightMode = RETRACTED;
      }
      else if(abs(motor_position - FRONT_RIGHT_EXTENDED) <abs(motor_position - FRONT_RIGHT_RETRACTED)  && abs(motor_position - FRONT_RIGHT_EXTENDED) < abs(motor_position - FRONT_RIGHT_RAISED)){
        frontRightMode = EXTENDED;
      }
      else if(abs(motor_position - FRONT_RIGHT_RAISED) <abs(motor_position - FRONT_RIGHT_RETRACTED)  && abs(motor_position - FRONT_RIGHT_RAISED) < abs(motor_position - FRONT_RIGHT_EXTENDED)){
        frontRightMode = RAISED;
      }
    }

}

void init(Servo servomotors[], Dynamixel2Arduino dxl){
  //Associate magnets
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(10,0);
  digitalWrite(11,0);
  digitalWrite(12,0);
  digitalWrite(13,0);

  //Servomotors
  servomotors[FRONT_LEFT_SERVO].attach(PIN_FRONT_LEFT_SERVO_PWM);
  servomotors[FRONT_RIGHT_SERVO].attach(PIN_FRONT_RIGHT_SERVO_PWM);
  servomotors[REAR_LEFT_SERVO].attach(PIN_REAR_LEFT_SERVO_PWM);
  servomotors[REAR_RIGHT_SERVO].attach(PIN_REAR_RIGHT_SERVO_PWM);

  //Steppers
  pinMode(BDPIN_DXL_PWR_EN, OUTPUT);
  digitalWrite(BDPIN_DXL_PWR_EN, HIGH);

  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(57600);
  
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

  dxl.torqueOff(DXL_ID_FRONT_LEFT);
  dxl.setOperatingMode(DXL_ID_FRONT_LEFT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_FRONT_LEFT);

  dxl.torqueOff(DXL_ID_FRONT_RIGHT);
  dxl.setOperatingMode(DXL_ID_FRONT_RIGHT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_FRONT_RIGHT);
  
  dxl.torqueOff(DXL_ID_REAR_LEFT);
  dxl.setOperatingMode(DXL_ID_REAR_LEFT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_REAR_LEFT);
  
  dxl.torqueOff(DXL_ID_REAR_RIGHT);
  dxl.setOperatingMode(DXL_ID_REAR_RIGHT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_REAR_RIGHT);

  dxl.writeControlTableItem(PROFILE_VELOCITY,DXL_ID_FRONT_LEFT,45);
  dxl.writeControlTableItem(PROFILE_VELOCITY,DXL_ID_FRONT_RIGHT,45);
  dxl.writeControlTableItem(PROFILE_VELOCITY,DXL_ID_REAR_LEFT,45);
  dxl.writeControlTableItem(PROFILE_VELOCITY,DXL_ID_REAR_RIGHT,45);

  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  
  nbTurnsFrontLeft=0;
  nbTurnsFrontRight=0;
  nbTurnsRearLeft=0;
  nbTurnsRearRight=0;
  synchro = false;
  home(servomotors,dxl);
}
