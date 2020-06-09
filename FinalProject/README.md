# Capstone: ATC(Air Traffic Control) Computer Game

This implementation is a demo of a minimalist computer game, through which explains several concepts related with POO, management memory and concurrency in C++.

The goal of game is simulate one Air Traffic Controller (ATC), that avoid crashes and to achieve successful landings of planes.


# Context of Scene & Play instructions: ATC Computer Game

The context of game is the airspace around an airport, which is represented by two trajectories compoused how explains follow:

* Direct to one of three tracks in airport (Left , Center and Right). The selection of which track is random, made by game.

* Wait. Sometimes the tracks are bussy, in consecuence, is necesary to fly in circles, the game makes decision if keep one plane in wait or if plane is redirected to a specific track. This desicion can affected the air landings, generating possibles crashes.

The trajectories are represented by six paths:  horizontal line (sense right to left for the arrives of airplanes), one semi-elipitic for veer toward airport tracks, one elipse for wait (to fly in circles) , two sigmoides curves and one horizontal line for arrive to tracks.  The paths are drawn on cartesian axis which convergin on origin. 


Interaction

1. User control: 
   * Arrow left key. Generate a new airplane posicioned on path of arrived.
   * Arrow right key.  End the game, after 3 seconds the window is closed.
   
2. How to game: 
   * Each game last 60 seconds.
   
   *  One crash happen when two airplane aproximing between them, according an specific default distance, which is defined based on size of airplanes.
   
   * When exist a crash, both airplane are switched red, a few seconds later, the airplanes are switched gray. When this happen the airplanes  are as ghost, only are visualiced but no produce damage to others ones.

   * Those airplanes that arrive to final, in yellow, are considered as successful landings.

   * The score is placed on the title of window.


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

* SDL 2.0 
  * [click here for installation instructions](https://wiki.libsdl.org/Installation)
  
  The above instructions were tested on linux Ubuntu 18.04, Cmake 3.17.2, g++ 7.5.0. and SDL Library 2.0.
  

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory (FinalProject): `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./MyGame`.
