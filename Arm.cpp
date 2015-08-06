#include "Arduino.h"
#include "Arm.h"
#include <Servo.h>

/*
 * pin_ servo set the pin to control the servo 
 * pin_onoff set the pin to turn on or turn off the dc motor
 * pin_dir set the pin to control the direction of the dc motor
 */
Arm::Arm(int pin_servo, int pin_onoff, int pin_dir)
{
  //servo
  _pin_servo = pin_servo;

  //clamp
  _pin_onoff = pin_onoff;
  _pin_dir = pin_dir;
}

/*
 * initial set up
 */
void Arm::initialize(int current)
{
  //servo
  _servo.attach(_pin_servo);
  _current = current;
  delay(5);
  _servo.write(_current);
  _target = current;
  sem = true;

  //clamp
}

/*
 * set the target postion
 * to activete the servo
 * if the servo is already active
 * this function do nothing
 */
void Arm::goTo(int target)
{
  if (_current != target && sem)
  {
    _target = target;
    sem = false;
  }
}

/*
 * return the current position of the servo
 */
int Arm::position()
{
  return _servo.read();
}

/*
 * call this in the main loop
 * return true if servo is active
 * return false if servo isn't active
 */
boolean Arm::run()
{
  if (_current != _target)
  {
    if (_current > _target ) _current--;
    else _current++;
    _servo.write(_current);
    delay(2);
    return true;
  }
  else
  {
    sem = true;
    return false;
  }
}
