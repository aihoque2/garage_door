#include "../include/garage_door.h"
/*
test_close.cpp
file to test close() of 
the garage door
*/


int main(){
    
    //test open function
    bool close_flag = false;
    GarageDoor myDoor;
    myDoor.close();
    if (myDoor.getState() == "closed") close_flag = true;
    if (close_flag) return 0;    
    else return 1;
    
}