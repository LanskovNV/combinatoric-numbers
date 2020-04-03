#ifndef NUMBERS_H
#define NUMBERS_H

#include "error.h"

// counting functions
uint GetU(uint m, uint n, my_error_t &error);
uint GetA(uint m, uint n, my_error_t &error); 
uint GetP(uint n, my_error_t &error);
uint GetC(uint m, uint n, my_error_t &error);
uint GetS(uint m, uint n, my_error_t &error); 
uint GetB(uint n, my_error_t &error);

#endif // NUMBERS_H
