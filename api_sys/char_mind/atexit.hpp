/* What is ATEXIT?

   ATEXIT is a C++ library that makes a function do certain things before the exit of your program.

   1. At a bottom of ANY function you desire, put any atexit function listed here (NOTE: This should be BEFORE your return.)

   atexitregister(); (Registers the function to happen right at the exit of the program)
   atexiteject(); (Takes the function off the atexit registry)


   atexit is considered a BOOLEAN. so for example instead of atexiteject you could do:

   atexitregisterbool = false;
   or
   atexitrejectbool = true;

   have fun!
*/

#ifndef ATEXIT_HPP
#define ATEXIT_HPP

bool atexitregisterbool = false;
bool atexitrejectbool = false;
// makes atexit at stalemate

bool atexitregister()
{
  

