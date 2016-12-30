#ifndef DEBUG_
#define DEBUG_

#include <iostream>
#include <string>
#include <assert.h>

inline void DebugMessage(std::string message)
{ std::cout << message << "\n"; }

#endif