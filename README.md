# PES Project 5 Readme
Jack Campbell

## Description
This repo contains custom sources and makefiles for Project 4 as well as adapted and generated code 
from MCUXpresso and the KL25Z SDK.

This project contains three configurations: Test, Debug, and Normal.

Test runs a suite of unit tests covering the state machine code.

## Installation/Execution Notes

These are the steps to build the project in MCUXpresso.

1) Clone the repo
2) In MCUXpresso, click `New > Project`.
3) Select `Makefile project with existing code...`
4) Unselect C++, enter a project name, browse to the directory of the repo, and select `NXP MCU Tools`, then hit next.
5) Now set up the configurations. Right click the project,
6) Hit Properties
7) Uncheck "Generate makefiles"
8) Add "Debug" to the build directory path in the same dialog.
9) Do the same for Normal and Test configurations.

### Running the FB builds

1) Right click on the project name in the file hierarchy, select `Debug as > Debug configurations...`
2) Select `GDB PEMicro Interface Debugging`
3) Hit `New launch configuration`
4) Select a name for the output configuration (you need one for both Release and Debug)
5) Set the `C/C++ Application` field to the binary you want to run, either `Debug/output/kl25z_debug.axf` for Debug or `Release/output/kl25z_run.axf` for Release
6) Hit Apply
7) Hit Debug
8) The program should run in the console below, provided the board is connected successfully.
