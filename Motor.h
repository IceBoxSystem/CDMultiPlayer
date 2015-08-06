#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include <AccelStepper.h>

#define PIN_END_MAX 3
#define PIN_END_MIN 2
#define END_RUN -1500
#define MAX_RUN 500

#define MIN_POS 0

class Motor{
  public:
    Motor(int pin_dir, int pin_step);     //Motor constuctor; 
    void moveMotor(int pos);    //recall moveTo() form AccelStepper.h
    void setMovement(long maxSpeed, long acceleration, long spee);   //recall function(in order) setMaxSpeed(), setAcceleration(), setSpeed() form AccelStepper.h 
    int endStop();   //set max and min position's motor
    void moveOf(int totStep);
    
    bool go();    //recall function run() form AccelStepper.h
    
  private:

    //Motor()
    AccelStepper _stepper;
    int _pin_dir;
    int _pin_step;

    //moveMotor()
    int _pos;

    //moveOf()
    int _totStep;

    //setMovement()
    long _maxSpeed;
    long _acceleration;
    long _speed;

    //endStop()
    int _max_pos;
	//int _min_pos;
};

#endif
