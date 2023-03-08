#ifndef GARAGEDOOR_H
#define GARAGEDOOR_H

#include <vector>
#include <map>
#include <string>
class GarageDoor{
    public:
        bool isFrozen(); //check if state is one of the frozens
        bool isInitialState(); //check if state is opened or closed
        void close();
        void open();
        void run(); // control loop of sim
    private:
        std::vector<std::string> states = {"open", "closed", "opening", "open-freeze", "close-freeze"};
        std::string current_state;
        
    
};

#endif