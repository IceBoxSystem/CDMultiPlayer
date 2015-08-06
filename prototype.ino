#include <Servo.h>
#include <AccelStepper.h>
#include "Type.h"
#include "Arm.h"
#include "Motor.h"
#include "Action.h"

#define PIN_SERVO 9
Arm arm(PIN_SERVO, 45, 54);

Motor motor(5, 4);

boolean execute(action);

Action list;

boolean arm_stat;
boolean motor_stat;

action t;

void setup() {
  Serial.begin(9600);
  
  arm.initialize(0);
  motor.setMovement(9600, 80000, 9600);
  motor.endStop();
  
}

void loop() {
  arm_stat = arm.run();
  motor_stat = motor.go();
  /*
   * if everything is stopped
   * then a new action can be execute
   */
  if (!arm_stat && !motor_stat)
  {
    execute(list.get());
  }
  
}

void serialEvent()
{
  byte i = Serial.parseInt();
  if (i)
  {
    list.add(ARM, 90);
    list.add(MOTOR, 6000);
    list.add(ARM, 0);
    list.add(MOTOR, 0);
  }
  else
  {
    list.add(ARM, 180);
    list.add(MOTOR, 5000);
    list.add(MOTOR, 2000);
    list.add(ARM, 0);
  }
  Serial.print(i);
}


/*
 * return true if there was an action
 * return false if there wasn't an action
 */
boolean execute(action act)
{
  switch(act._hw)
  {
    case MOTOR:
      motor.moveMotor(act._value);
      return true;
      break;
      
    case ARM:
      arm.goTo(act._value);
      return true;
      break;

    case CLAMP:
      /*if (act._value != arm.state())
      {
        arm.toggle();
      }*/
      return true;
      break;

    case CDROM:
      //da mettere
      return true;
      break;
      
    default:
      return false;
      break;
  }
}
