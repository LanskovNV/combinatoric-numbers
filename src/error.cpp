// leins, 05.04.2018

#include <iostream>
#include <string>
#include "error.h"

using namespace std;

static string s_GetErrorString(my_error_t error)
{
  string s;

  switch(error)
  {
  case err_bad_command:
	s = "ERROR: unknown command, press h for help";
	break;
  case err_no_memory:
  s = "ERROR: unsigned int is too short for answer";
	break;
  case err_less_param:
	s = "ERROR: too few arguments";
	break;
  case err_bad_param:
	s = "ERROR: incorrect parameter, should be positive int";
	break;
  case err_too_many_symb:
	s = "ERROR: too many arguments";
	break;
  case err_ok:
  case err_exit:
	s = "ERROR: should not be an error, !!!";
	break;
  default:
	s = "ERROR: unknown errror, ???";
	break;
  }

  return s;
} // end of func

void ReportError(my_error_t error)
{
  string errString = s_GetErrorString(error);
  cout << errString << endl;
} // end of func
