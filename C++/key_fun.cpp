#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <string>
#include <map>

bool keyHelper(){
  auto start = std::chrono::steady_clock::now();
  bool first_flag = true;
  while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)){
    if (first_flag) {printw("operating on door... \n"); first_flag = false;}
    int ch = getch();
    if (ch != ERR){
      printw("you froze the function!... \n");
      refresh();
      return false;
    }
  }
  return true;
}

void keyListener(){
    // Initialize ncurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Set timeout for getch() to non-blocking mode
  timeout(0);

  // Get start time
  std::map<std::string, std::string> myMap;
  myMap["open"] = "closed";
  myMap["closed"] = "open";
  myMap["frozen"] = "closed";
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
      refresh();    
      if (!keyHelper()){
        curr_state = "frozen";
      }
      else curr_state = myMap[curr_state];
      state_changed = true;
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

