#include "../include/garage_door.h"
/*
test_close.cpp
file to test rubn() of 
the garage door
*/


int main(){
    
    //test open function
    bool close_flag = false;
    GarageDoor myDoor;
    myDoor.setDone(true);

    myDoor.run();
    if (myDoor.getState() == "open") close_flag = true;
    if (close_flag) return 0;    
    else return 1;
    
}