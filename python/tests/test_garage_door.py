import unittest
from src.garage_door import GarageDoor

class TestRun(unittest.TestCase):
    def test_garage_door_done(self):
        door = GarageDoor()
        door.done = True
        door.run() #ensure run works properly
        return
    
if __name__=="__main__":
    unittest.main()