# CPPND: Capstone Repo Simulated Evolution

This is the repo for my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

In this project, a simulated evolution is run, based on https://beltoforion.de/en/simulated_evolution/. 
As a summary:
- In this evolution, microbes spend energy by moving, gain energy by easting food, reproduce themselves when they have gained enough energy, and die when their energy level becomes too low. Food is spawn randomly. 
- The microbes have a genome which basically determines what the preferred direction to move is.
- When a microbe reproduces, the genome of the child is slightly mutated compared to the parent.
- When changing the way the food is spawned, the genes of the population adopt after a while. For example, if the food is spawned in lines, the microbes "learn" to move along the food lines.
See https://beltoforion.de/en/simulated_evolution/ formore details.

This project is mainly to demonstrate my skills regarding concurrency. This means a lot is running in saparate threads, e.g. each microbe run in its own thread, etc. There are probably more efficient solutions, but it is amzing to see that it works!

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