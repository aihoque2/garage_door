#include "../include/garage_door.h"
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <map>

/*
test_open.cpp
file to test open() of 
the garage door
*/


int main(){
    
    //test open function
    bool open_flag = false;
    GarageDoor myDoor;
    myDoor.close();
    myDoor.open();
    if (myDoor.getState() == "closed") open_flag = true;
    if (open_flag) return 0;    
    else return 1;
    
}