#ifndef Arm_h
#define Arm_h

#include "Arduino.h"
#include <Servo.h>

class Arm
{

  public:
    Arm(int pin_servo, int pin_onoff, int pin_dir);
    void initialize(int current);

    //servo
    void goTo(int target);
    int position();
    boolean run();

    //clamp
    boolean take();     //da fare
    boolean release();  //da fare
    boolean toggle();   //da fare
    boolean state();    //da fare
    
  private:
    //servo
    Servo _servo;
    int _pin_servo;
    int _current;
    int _target;
    boolean sem;

    //clamp
    int _pin_onoff;
    int _pin_dir;
    boolean _state;
};

#endif
