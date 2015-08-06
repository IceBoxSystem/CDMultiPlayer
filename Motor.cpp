#include "Arduino.h"
#include "Motor.h"
#include <AccelStepper.h>


Motor::Motor(int pin1, int pin2){  
  _pin_step = pin1;
  _pin_dir = pin2;
  _stepper = AccelStepper(1, _pin_step, _pin_dir);
}

void Motor::moveMotor(int pos){
  if(pos <= _max_pos && pos >= MIN_POS){
	_pos = pos;
	_stepper.moveTo((long)_pos);
  } else {
	  Serial.println("Position not available.");
	  Serial.print("MAX..");
	  Serial.println(_max_pos);
	  Serial.print("MIN..");
	  Serial.println(MIN_POS);
	  Serial.println();
	  pos = _stepper.currentPosition();
	}
}

void Motor::moveOf(int totStep){
  _totStep = totStep;
  _stepper.move((long)_totStep);
}

void Motor::setMovement(long maxSpeed, long acceleration, long spee){
  _maxSpeed = maxSpeed;
  _acceleration = acceleration;
  _speed = spee;

  _stepper.setMaxSpeed((float)maxSpeed);
  _stepper.setAcceleration((float)acceleration);
  _stepper.setSpeed((float)spee);

  pinMode(PIN_END_MAX, INPUT);
  pinMode(PIN_END_MIN, INPUT);
  digitalWrite(PIN_END_MAX, HIGH);
  digitalWrite(PIN_END_MIN, HIGH);
}

int Motor::endStop(){
  
  Serial.println("Finding ZERO position...");
  while(1){
    go();
    if(digitalRead(PIN_END_MIN) == 0){
      _stepper.setCurrentPosition(MIN_POS);             //setta la posizione attule come ZERO
      Serial.println("ZERO posistion found and setted\n");
      break;
    }
    moveOf(END_RUN);  //corre finchè il PIN_END_MIN non è zero
  }

  Serial.println("Finding MAX position...");
  while(1){
    go();
    if(digitalRead(PIN_END_MAX) == 0){
      _max_pos = _stepper.currentPosition();
      _stepper.setCurrentPosition(_max_pos);  //setta la posizione attule come MAX
      Serial.print("Max posistion found and setted on..");
      Serial.println(_max_pos);
      Serial.println();
      break;
    }
    moveOf(MAX_RUN);  //corre finchè il PIN_END_MAX non è zero
  }

  moveMotor(0);
  while(_stepper.currentPosition() != 0) go();

  return _max_pos;
}

//return true if motor is moving
bool Motor::go(){
  return _stepper.run();
}
