#pragma once
#ifndef _INTERFACE_H
#define _INTERFACE_H

// leins, 05.04.2018

#include "error.h" 

// type to call any Get function from numbers.cpp
typedef uint (*get_numb_double_t)(uint, uint, my_error_t&);
typedef uint (*get_numb_uno_t)(uint, my_error_t&);

// main functions
void ProcessorMode();
void ConsoleMode(int argc, char *argv[]);

#endif 
