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
        bool close(); //return true if state changes, false if quit is called
        bool open();
        void run(); // control loop of sim
        std::string getState();
    private:
        std::vector<std::string> states;
        std::string current_state;
        typedef bool (GarageDoor::*MFP)(); //boolean function pointers
        std::map <std::string, MFP> fmap; //map the state to its function call
    
};

#endif