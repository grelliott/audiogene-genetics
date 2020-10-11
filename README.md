# audiogene-genetics

An interactive audio generator that evolves the sound based on interactions.

This is the genetic algorithm component of the audiogene system.

## Build

**Note: This should be done on a Raspberry Pi**

Install the following dependencies:

`sudo apt-get install libgflags-dev libyaml-cpp-dev libspdlog-dev liblo-dev librtmidi-dev wiringpi cmake`

`mkdir _install && mkdir _build && cd _build`

`cmake -DCMAKE_INSTALL_PREFIX=../_install ..`

`make`

`make install`

