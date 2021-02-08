# CPPND: Capstone Repo Simulated Evolution

This is the repo for my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

In this project, a simulated evolution is run, based on https://beltoforion.de/en/simulated_evolution/. 
As a summary:
- In this evolution, microbes spend energy by moving, gain energy by eating food, reproduce themselves when they have gained enough energy, and die when their energy level becomes too low. New food is spawn randomly at regular time intervals.
- The microbes have a genome which basically determines what the preferred direction to move is.
- When a microbe reproduces, the genome of the child is slightly mutated compared to the parent.
- When changing the way the food is spawned, the genes of the population adopt after a while. For example, if the food is spawned in lines, the microbes "learn" to move along the food lines (might take a while!).

See https://beltoforion.de/en/simulated_evolution/ for more details.

This project is mainly to demonstrate my skills regarding concurrency. This means a lot is running in separate threads, e.g. each microbe run in its own thread, etc. There are probably more efficient solutions, but it is amazing to see that it works!

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SimulatedEvolution`.

## Overview of code structure

- main.cpp
  * Initializes Renderer and Controller, and runs the simulated evolution.
- params.h
  * Configuration parameters, used throughout the program.
- evolution.h, evolution.cpp
  * Evolution class, see below.
- controller.h, controller.cpp
  * Class for handling user input (change food distribution, quit).
- renderer.h, renderer.cpp
  * Class for rendering the the simulation (microbes and food) using SDL2.
- microbe.h, microbe.cpp
  * Microbe class with methods for moving, reproducing etc.
- gene.h, gene.cpp
  * Class to represent the genes of the microbes
- queue.h, queue.tpp
  * template message queue, for handling new microbes and finished threads.
- food.h
  * Struct to keep the food array and the corresponding mutex together.
- microbelist.h
  * Struct to keep the list of microbes and the corresponding mutex together

### Evolution class

This class is the central part of the program, and mainly consists of managing the many threads.
It starts threads for:
- each microbe
- spawning food
- rendering
- cleaning up the microbe list: deleting the vector elements of "dead" microbes.
- cleaning up the list of microbe threads: joining the threads which are finished (i.e. those of dead microbes) and removing the respective vector elements.

Each time a new microbe is created (at initialization or when a microbe reproduces:
- the new microbe is added to the list of microbes (through a messagequeue).
- the "life" of the Microbe is run in a new thread, which is added to the list of microbe threads.

Each time a microbe dies:
- its corresponding thread id is sent to the queue of finished threads

This way, all finished threads are joined, and the lists of microbes and threads are kept as small as possible.
When the user quits the program, a flag is set to let all threads finish, so they can all be joined.
