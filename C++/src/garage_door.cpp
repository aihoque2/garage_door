#ifndef __GARAGEDOOR_CPP
#define __GARAGEDOOR_CPP

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <map>
#include "../include/garage_door.h"

GarageDoor::GarageDoor(){
    current_state = "open";
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
    if (ch != ERR){
      printw("INTERRUPTION \n");
      refresh();
      current_state = "closed-freeze";
      return false;
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
    if (ch != ERR){
      printw("INTERRUPTION \n");
      refresh();
      current_state = "open-freeze";
      return false;
    }
  }
  current_state = "open";
  return true;
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
    while (true){
        if (first_flag){
            printw(" Welcome to the garage door! your state is: %s\n", current_state.c_str());
            first_flag = false;
        }
        if (state_changed){
            printw("%s \n", current_state.c_str());
            state_changed = false;
        }
        
        int ch = getch();
        if (ch != ERR && ch == 'q') break;

        else if (ch != ERR){
            //key press detected. print to screen
            MFP fp = fmap[current_state];
            (this->*fp)();
            state_changed = true;
        }
    }
    // Clean up ncurses
    endwin();
}

#endif