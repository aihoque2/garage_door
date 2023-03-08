#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <string>
#include <map>

void keyListener(){
    // Initialize ncurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Set timeout for getch() to non-blocking mode
  timeout(0);

  // Get start time
  auto start = std::chrono::system_clock::now();
  std::map<std::string, std::string> myMap;
  myMap["open"] = "closed";
  myMap["closed"] = "open";
  // Loop for 10 seconds
  bool state_changed = false;
  bool first_flag = true;
  std::string curr_state = "open";
  while (true){
    // Check for key press
    if (first_flag){
      printw(" welcome to door! your state is: %s\n", curr_state.c_str());
      first_flag = false;
    }
    if (state_changed){
      printw("%s \n", curr_state.c_str());
      state_changed = false;
      
    }
    int ch = getch();
    if (ch != ERR && ch =='q'){
      break;
    }
    else if (ch != ERR) {
      // Key press detected, print to screen
      printw("Key pressed: %c\n", ch);
      curr_state = myMap[curr_state];
      state_changed = true;
      refresh();    
    }
    
  }
  // Clean up ncurses
  endwin();
}

int main() {
  keyListener();
  std::cout << "hello world!" << std::endl;
  return 0;
}

