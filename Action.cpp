#include "Arduino.h"
#include <avr/pgmspace.h> //PROGMEM
#include "Type.h"
#include "Action.h"

//g++
//#include <iostream>
//using namespace std;

/*ostream& operator<<(ostream& os, const HW hw)
{
    os << HW2string(hw);
    return os;
}*/

Action::Action()
{
  _head = -1;
  _tail = -1;
  _size = SIZE;
  
  //int i;
  byte i;
  for (i = 0;i < _size; i++)
  {
      _list[i]._hw = VOID;
      _list[i]._value = -1;
  }
}

action Action::get()
{
  action temp;
  
  if(_head != -1)
  {
    temp = _list[_head];
    remove();
    return temp;
  }
  else
  {
    /*
     * la lista è vuota quindi
     * ogni elemento contiene VOID -1
     * ed è indifferente quale si ritorna
     */
    return _list[0];
  }
}

/*
 * add an action to the list
 * return 1 if success
 * return 0 if there's no space available
 */
byte Action::add(HW hw, int value)
{
  if (_head > 0) shift();
  
  if(_head == -1)
  {
    _head = 0;
    _tail = _head;
    _list[_head]._hw = hw;
    _list[_head]._value = value;
    return 1;
  }
  else
  {
    if (_tail < _size-1)
    {
      _tail++;
      _list[_tail]._hw = hw;
      _list[_tail]._value = value;
      return 1;
    }
    else
    {
      //cout << "Actions: not enough space" << endl;
      //Serial.println("Actions: no space");
      return 0;
    }
  }
}

void Action::remove()
{
  _list[_head]._hw = VOID;
  _list[_head]._value = -1;
  if (_head == _tail) {
    _head = -1;
    _tail = -1;
  }
  else
  {
    _head++;
  }
}

//move the list's head at the list's beginnig
void Action::shift()
{
  int i;//byte i;
  _tail = _tail-_head;
  for(i = 0; i <= _tail; i++)
    {
      _list[i] = _list[_head+i];
    }
    _head = 0;
}

void Action::print()
{
  //int i;
  byte i;
  byte tail = _tail-_head;
  if (_head != -1)
  {
    for(i = 0; i <= tail; i++)
    {
      Serial.print(HWstr[_list[i]._hw]);
      Serial.print("\t");
    }
    for(i = 0; i <= tail; i++)
    {
      Serial.print(_list[i]._value);
      Serial.print("\t");
    }
    Serial.println();
  }
  else //cout << "VOID" << endl;
       Serial.println("VOID");
}

void Action::stat() {
    //int i;
    byte i;
    //cout << "list..." << endl;
    for (i = 0; i < _size; i++)
    {
      Serial.print(HWstr[_list[i]._hw]);
      Serial.print("\t");
      //cout << _list[i]._hw << "\t";
    }
    //cout << endl;
    Serial.println();
    for (i = 0; i < _size; i++)
    {
      Serial.print(_list[i]._value);
      Serial.print("\t");
      //cout << _list[i]._value << "\t";
    }
    //cout << endl;
    Serial.println();
    //cout << "_head: " << _head << endl;
    Serial.print("head :");
    Serial.println(_head);
    //cout << "_tail: " << _tail << endl<< endl;
    Serial.print("tail :");
    Serial.println(_tail);
}
