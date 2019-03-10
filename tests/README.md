# sqlibembeddedC test suite
This directory contains the tests for the sqlibembedded library. My own minimal [minunit](https://github.com/Squantor/squantorMinUnitC.git) variant is used to implement tests.
# Limitations
Building the tests will use my own private libc implementation.
# Usage
Uses Make as its buildsystem, using ```make``` will make release for the default platform of the PC with -ffreestanding. There are two build targets, release and debug differing in included debugging information and optimization level.

Example run:
```ShellSession
$ ./bin/bare_PC/debug/sqlibembeddedC_tests.elf 
All tests passed.
```
To debug or see more detailed statistics, load the program into a debugger and watch the statistics global variables:
```C
int minunitRun; /* tests run */
int minunitFailures; /* tests failed */
int minunitAsserts; /* asserts run */
```
# To do
* Coverage system
* automated build system via buildbot
