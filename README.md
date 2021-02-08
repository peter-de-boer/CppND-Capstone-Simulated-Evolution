# CPPND: Capstone Repo Simulated Evolution

This is the repo for my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

In this project, a simulated evolution is run, based on https://beltoforion.de/en/simulated_evolution/. 
As a summary:
- In this evolution, microbes spend energy by moving, gain energy by eating food, reproduce themselves when they have gained enough energy, and die when their energy level becomes too low. New food is spawn randomly at regular time intervals.
- The microbes have a genome which basically determines what the preferred direction to move is.
- When a microbe reproduces, the genome of the child is slightly mutated compared to the parent.
- When changing the way the food is spawned, the genes of the population adopt after a while. For example, if the food is spawned in lines, the microbes "learn" to move along the food lines (might take a while!).
- When run, a window is shown with red dots, representing food, and blue moving dots, representing microbes. Clicking the buttons in the upper left corner will change the way food is spawn, whcih eventually leads to changing the way the microbes move. Watch and have fun!

See https://beltoforion.de/en/simulated_evolution/ for more details on the evolution model.

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

Each time a new microbe is created:
- the new microbe is added to the list of microbes (through a message queue).
- the "life" of the Microbe is run in a new thread; this new thread is added to the list of microbe threads.

Each time a microbe dies:
- its corresponding thread id is sent to the queue of finished thread id's.

This way, all finished threads are joined, and the lists of microbes and threads are kept as small as possible.
When the user quits the program, a flag is set to let all threads finish, so they can all be joined.

# Addressed rubric points

## Loops, Functions, I/O

Rubric point | Code
-------------|-----
The project demonstrates an understanding of C++ functions and control structures. | A variety of control structures are used in the project. The project code is clearly organized into functions.
The project reads data from a file and process the data, or the program writes data to a file.| The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
The project accepts user input and processes the input. | The project accepts input from a user as part of the necessary operation of the program.


## Object Oriented Programming

Rubric point | Code
-------------|-----
The project uses Object Oriented Programming techniques. | The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
Classes use appropriate access specifiers for class members.|All class data members are explicitly specified as public, protected, or private.
Class constructors utilize member initialization lists.|All class members that are set to argument values are initialized through member initialization lists.
Classes abstract implementation details from their interfaces.|All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
Classes encapsulate behavior.|Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.
Classes follow an appropriate inheritance hierarchy.|Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.
Overloaded functions allow the same function to operate on different parameters.|One function is overloaded with different signatures for the same function name.
Derived class functions override virtual base class functions.|One member function in an inherited class overrides a virtual base class member function.
Templates generalize functions in the project.|One function is declared with a template that allows it to accept a generic parameter.

## Memory Management

Rubric point | Code
-------------|-----
The project makes use of references in function declarations.|At least two variables are defined as references, or two functions use pass-by-reference in the project code.
The project uses destructors appropriately.|At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.|The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
The project follows the Rule of 5.|For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
The project uses move semantics to move data, instead of copying it, where possible.|For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
The project uses smart pointers instead of raw pointers.|The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.

## Concurrency

Rubric point | Code
-------------|-----
The project uses multithreading.|The project uses multiple threads in the execution.
A promise and future is used in the project.|A promise and future is used to pass data from a worker thread to a parent thread in the project code.
A mutex or lock is used in the project.|A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
A condition variable is used in the project.|A std::condition_variable is used in the project code to synchronize thread execution.

