#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <thread>

struct termios old_settings, new_settings;

void getKey(){
  // Save the current terminal settings
  tcgetattr(STDIN_FILENO, &old_settings);
  new_settings = old_settings;
  
  // Disable canonical mode and echo
  new_settings.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
  
  while (true) { // loop indefinitely
    char key;
    if (read(STDIN_FILENO, &key, 1) > 0) { // check if a key has been pressed
      std::cout << "Key pressed: " << key << std::endl; // print the key to the console
      return;
    }
  }
  
}

void some_func(){
    int i = 0;
    while ( i < 10000){
        std::cout << "here's i: " << i << std::endl;
        i++;
    }
}

int main() {
  std::cout << "Press any key to continue..." << std::endl; 
  std::thread t1(getKey);
  while(true){
    if (!t1.joinable()){
        t1.join();
        t1.detach();
        t1 = std::thread(getKey);
    }
  }
  // Restore the original terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
  return 0;
}