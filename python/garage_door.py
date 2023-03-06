import time
import sys
import termios
import tty
from threading import Thread


def get_key():
    file_descriptor = sys.stdin.fileno()
    old_settings = termios.tcgetattr(file_descriptor)
    try:
        tty.setcbreak(file_descriptor)
        while True:
            # Listen for keyboard input
            key = sys.stdin.read(1)
            break

    finally:
        termios.tcsetattr(file_descriptor, termios.TCSADRAIN, old_settings)


class GarageDoor:
    def __init__(self):
        self.states = ["open", "closed", "opening", "open-freeze", "close-freeze"]
        self.current_state = "closed"
        self.button_handler = {"open":self.close, "open-freeze": self.close, "closed": self.open, "close-freeze": self.open}
        self.listener = Thread(target=get_key)


    def is_frozen(self):
        return "freeze" in self.current_state

    def open(self):
        self.current_state = "opening"
        print("STATE: ", self.current_state)
        end_time = time.monotonic() + 5
        while (time.monotonic() < end_time):
            if not self.listener.is_alive():
                self.current_state = "open-freeze"
                print("STATE: ", self.current_state)
                self.listener = Thread(target=get_key)
                self.listener.start()
                return
        self.current_state = "open"
        print("the door has fully opened!")

    def close(self):
        self.current_state = "closing"
        print("STATE: ", self.current_state)
        end_time = time.monotonic() + 5
        while (time.monotonic() < end_time):
            if not self.listener.is_alive():
                self.current_state = "close-freeze"
                print("STATE: ", self.current_state)
                self.listener = Thread(target=get_key)
                self.listener.start()
                return
        self.current_state = "closed"
        print("the door has fully closed!")
    
    def in_initial(self):
        return self.current_state == "open" or self.current_state == "closed"

    def run(self):
        self.listener.start()
        print("The garage door is closed! press any key to continue")
        while True:
            if not self.listener.is_alive() and self.in_initial():
                self.listener = Thread(target=get_key)
                self.listener.start()
                self.button_handler[self.current_state]()
            
            if not self.listener.is_alive() and self.is_frozen():
                self.listener = Thread(target=get_key)
                self.listener.start()
                self.button_handler[self.current_state]()

if __name__=="__main__":
    door = GarageDoor()
    door.run()