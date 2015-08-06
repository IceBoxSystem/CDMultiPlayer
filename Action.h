#ifndef Action_h
#define Action_h

#include "Arduino.h"
#include <avr/pgmspace.h> //PROGMEM

#include "Type.h"

//g++
//#include <iostream>


#define SIZE 50

class Action
{
  public:
    Action();
    action get();
    byte add(HW, int);
    void remove();
    void print();
    void stat();
    
  private:
    void shift();
    
    action _list[SIZE] PROGMEM;
    byte _head; 
    //int _head;
    byte _tail; 
    //int _tail;
    byte _size;
    //int _size;
};

#endif
