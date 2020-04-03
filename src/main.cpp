// leins, 05.04.2018

#include <iostream>
#include "interface.h"

using namespace std;

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "rus");

  if (argc > 1) // auto mode
    ConsoleMode(argc, argv);
  else          // interactive processor mode
    ProcessorMode();

  return 0;
} // end of main
