#ifndef __GARAGEDOOR_H
#define __GARAGEDOOR_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <map>

class GarageDoor{
    public:
        GarageDoor();
        bool isFrozen(); //check if state is one of the frozens
        bool isInitialState(); //check if state is opened or closed
        bool close();
        bool open();
        void run(); // control loop of sim
    private:
        std::vector<std::string> states = {"open", "closed", "opening", "open-freeze", "close-freeze"};
        std::string current_state;
        typedef bool (GarageDoor::*MFP)(); //boolean function pointers
        std::map <std::string, MFP> fmap; //map the state to its function call
    
};

#include "../src/garage_door.cpp"
#endif