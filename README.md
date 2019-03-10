# sqlibembeddedC
C code library with various functions geared for embedded systems development like:
* Ansi parsing
* Commandline parsing
* queues in various shapes
# Limitations
This library depends on LibC, it is continually tested with my [my own minimal LibC](https://github.com/Squantor/squantorLibC), but you can use any libc you like.
# Usage
Checking out is done with:
```
git clone https://github.com/Squantor/squantorLibEmbeddedC.git --recurse-submodules
```
This is to make sure that all submodules are checked out, my own private libc is checked out for instance.

Uses Make as its buildsystem, using ```make``` will make release for the default platform of the generic PC. There are two build targets, release and debug differing in included debugging information and optimization level. You can also build for different targets by using the argument ```PLATFORM=```, example debug build for cortex M0 microcontrollers ```make debug PLATFORM=CortexM0```. Support is present for CortexM0 to CortexM7, PC and PC with -ffreestanding.
## Unittests
Also present are unittests, see the tests directory for more information.
# To do
I still want to add a bunch of functionality.
* assertions
* debugging macros
* fixedpoint library
* Signal processing
* Various queue types
* Statemachine template
* Event handler template