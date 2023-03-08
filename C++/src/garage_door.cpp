#ifndef __GARAGEDOOR_CPP
#define __GARAGEDOOR_CPP

#include "../include/garage_door.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <map>


GarageDoor::GarageDoor(){
    done = false;
    current_state = "open";
    states.push_back(current_state);
    fmap.emplace("open", &GarageDoor::close);
    fmap.emplace("open-freeze", &GarageDoor::close);
    fmap.emplace("closed", &GarageDoor::open);
    fmap.emplace("closed-freeze", &GarageDoor::open);
}

bool GarageDoor::isFrozen(){
    return current_state.find("freeze") != std::string::npos;
}

bool GarageDoor::isInitialState(){
    return (current_state == "open" || current_state == "closed");
}

bool GarageDoor::close(){
  auto start = std::chrono::steady_clock::now();
  bool first_flag = true;
  while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)){
    if (first_flag) {printw("Closing door... \n"); first_flag = false;}
    
    int ch = getch();

    if (ch != ERR && ch == 'q') return false;
    else if (ch != ERR && ch == 'a'){
      printw("INTERRUPTION \n");
      refresh();
      current_state = "closed-freeze";
      return true;
    }
    else if (ch != ERR && ch == 's'){
      printw("SAFETY HAZARD \n");
      refresh();
      return open();
    }
  }
  current_state = "closed";
  return true;

}

bool GarageDoor::open(){
  auto start = std::chrono::steady_clock::now();
  bool first_flag = true;
  while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)){
    if (first_flag) {printw("Opening door... \n"); first_flag = false;}
    int ch = getch();
    if (ch != ERR && ch == 'q') return false;
    else if (ch != ERR && ch == 'a'){
      printw("INTERRUPTION \n");
      refresh();
      current_state = "open-freeze";
      return true;
    }
  }
  current_state = "open";
  return true;
}

std::string GarageDoor::getState(){return current_state;}

void GarageDoor::setDone(bool val){
  done = val;
}

void GarageDoor::run(){
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Set timeout for getch() to non-blocking mode
    timeout(0);

    bool state_changed = false;
    bool first_flag = true;
    while (true && !done){
        if (first_flag){
            printw(" Welcome to the garage door! your state is: %s\n", current_state.c_str());
            first_flag = false;
        }
        if (state_changed){
            if (isFrozen()) printw("frozen \n");
            else printw("%s \n", current_state.c_str());
            states.push_back(current_state);
            state_changed = false;
        }
        
        int ch = getch();
        if (ch != ERR && ch == 'q') break;

        else if (ch != ERR && ch == 'a'){
            //key press detected. cal transition function
            MFP fp = fmap[current_state];
            bool continuing = (this->*fp)();
            if (!continuing) break;
            state_changed = true;
        }
    }
    // Clean up ncurses                state_changed = false;

    endwin();
}

#endif