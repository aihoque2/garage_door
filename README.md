# Garage Door

welcome to my submission for the garage door challenge. below you'll see how to turn the python version and C++ version

### controls
use 'A' to press the garage door button, and 'S' to trigger a safety hazard


## C++

### requirements
`CMAKE >= 3.5`

`ncurses`

`ubuntu 18.04 or higher`

please ensure you have ncurses installed:

`sudo apt-get install libncurses5-dev libncursesw5-dev`

### to run
inside the `C++` directory, please run

`mkdir build && cd build && cmake .. && make`

then to execute the program, please type

`./main`

to execute unit tests, please run

`make test`


## Python

### requirements
`Python 3`

`ubuntu 18.04 or higher`


### to run
inside the `python` directory, please run

`python3 ./src/garage_door.py`

to run unittests, please type

`python3 -m unittest discover`

## Limitations and further work
Due to time constraints, I was unable to get a proper unit test that simulates keyboard inputs for the garage door. 
I would love to make a thorough unit test that types keyboard inputs on a separate thread. At least I am able to demonstrate
my knowledge of creating unittests in CMake and Python.