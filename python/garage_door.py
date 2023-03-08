import time
import sys
import termios
import tty
from threading import Thread


class GarageDoor:
    def __init__(self):
        self.states = ["open", "closed", "opening", "open-freeze", "close-freeze"]
        self.current_state = "open"
        self.button_handler = {"open":self.close, "open-freeze": self.close, "closed": self.open, "close-freeze": self.open}
        self.listener = Thread(target=self.get_key)
        self.pressed = 'c'

    def get_key(self):
        file_descriptor = sys.stdin.fileno()
        old_settings = termios.tcgetattr(file_descriptor)
        try:
            tty.setcbreak(file_descriptor)
            while True:
                # Listen for keyboard input
                key = sys.stdin.read(1)
                if (key == 'a' or key =='s' or key == 'q'):
                    self.pressed = key


        finally:
            termios.tcsetattr(file_descriptor, termios.TCSADRAIN, old_settings)

    def is_frozen(self):
        return "freeze" in self.current_state

    def open(self):
        self.current_state = "opening"
        print("opening...")
        end_time = time.monotonic() + 4
        while (time.monotonic() < end_time):
            if self.pressed == 'a':
                self.current_state = "open-freeze"
                print("INTERRUPTED: Door is frozen")
                self.pressed = 'c'
                return
        self.current_state = "open"

    def close(self):
        self.current_state = "closing"
        print("closing...")
        end_time = time.monotonic() + 4
        while (time.monotonic() < end_time):
            if (self.pressed == 's'):
                print("SAFETY HAZARD")
                self.pressed = 'c'
                self.open()
                return
            elif self.pressed == 'a':
                self.pressed = 'c'
                self.current_state = "close-freeze"
                print("INTERRUPTED: Door is frozen")
                return
                
        self.current_state = "closed"
    
    def in_initial(self):
        return self.current_state == "open" or self.current_state == "closed"

    def run(self):
        self.listener.start()
        print("The garage door is open! press any key to continue")
        state_changed = False
        while True:
            if (state_changed):
                print("the state is: ", self.current_state)
                state_changed = False
            if self.pressed == 'a':
                self.pressed = 'c'
                self.button_handler[self.current_state]()
                state_changed = True
            

if __name__=="__main__":
    door = GarageDoor()
    door.run()