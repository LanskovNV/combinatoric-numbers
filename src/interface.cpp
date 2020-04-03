 // leins, 05.04.2018

#include <iostream>
#include <cctype>
#include <climits>
#include <map>
#include <cstring>
#include "numbers.h"
#include "interface.h"

using namespace std;

// ***************
// local functions

static void s_SkipSpaces(string &str)
{
  while (!str.empty() && isspace(str.front()))
	str.erase(0, 1);
} // end of function

// check space after correct param
static void s_CheckParam(string s, my_error_t &error)
{
  if (!s.empty() && !isspace(s.front()))
	error = err_bad_param;
} // end of function

static int s_GetDigit(string &str, my_error_t &error)
{
  s_SkipSpaces(str);

  if (str.empty())
  {
	error = err_less_param;
	return 0;
  }
  else
  {
	uint denum = 10;
	uint res = 0;

	if (!isdigit(str.front()))
	  error = err_bad_param;
	else
	{
	  while (!str.empty() && isdigit(str.front()))
	  {
		uint digit = ((uint)str.front() - '0');

    if (res > UINT_MAX / 10 || ((res == UINT_MAX / 10) && (digit > UINT_MAX % 10))) // int capacity check
		{
		  error = err_no_memory;
		  break;
		}
		res = res * denum + digit;
		str.erase(0, 1);
	  }
	}

	return res;
  }
} // end of function

// detecting extra parameters error 
static void s_FinalCheck(string &command, my_error_t &error)
{
  // end of command check
  if (error == err_exit || error == err_help)
	command.erase(0, 1);
  s_SkipSpaces(command);

  if (!command.empty())
	error = err_too_many_symb;
} // end of func

static void s_PrintHelp()
{
  cout << "supporting commands" << endl;
  cout << "Q - exit" << endl;
  cout << "U - number of partial permutations (two parameters)" << endl;
  cout << "A - number of partial permutations without repetitions (two parameters)" << endl;
  cout << "P - number of permutations (one parameter)" << endl;
  cout << "C - number of combinations (two parameters)" << endl;
  cout << "S - number of Stirling of second kind (two parameters)" << endl;
  cout << "B - number of Bell (one parameter)" << endl;
} // end of function

static uint s_ProcessLine(bool &run, string command, my_error_t &error)
{
  uint result = 0;

  s_SkipSpaces(command);

  if (!command.empty())
  {
	char commandId;
	uint m = 0, n = 0;
	get_numb_double_t doubleFunc[4] = { GetU, GetA, GetC, GetS };
	get_numb_uno_t unoFunc[2] = { GetP, GetB };
	map<char, uint> i = { {'U', 0}, { 'A', 1 }, { 'C', 2 }, { 'S', 3 } };
	map<char, uint> j = { { 'P', 0 },{ 'B', 1 } };

	commandId = command.front();

	switch (commandId)
	{
	case 'Q':
	  run = false;
	  error = err_exit;
	  break;
	case 'H':
	  error = err_help;
	  break;
	case 'U':
	case 'A':
	case 'C':
	case 'S':
	  command.erase(0, 1);
	  if (!isspace(command.front()))
	  {
	  	  error = err_bad_command;
		  break;
	  }
	  m = s_GetDigit(command, error);
	  s_CheckParam(command, error); // after int is space?
	  if (error == err_ok)
	  {
		n = s_GetDigit(command, error);
		s_CheckParam(command, error);
	  }
	  if (error == err_ok)
		result = doubleFunc[i.find(commandId)->second](m, n, error);
	  break;
	case 'P':
	case 'B':
	  command.erase(0, 1);
	  if (!isspace(command.front()))
	  {
	  	error = err_bad_command;
		break;
	  }
	  n = s_GetDigit(command, error);
	  s_CheckParam(command, error); // after int is space?
	  if (error == err_ok)
		result = unoFunc[j.find(commandId)->second](n, error);
	  break;
	default:
	  error = err_bad_command;
	  break;
	}

	if (error <= err_help)
	  s_FinalCheck(command, error);
  }
  else
	error = err_exit;

  return result;
} // end of func

static uint s_ProcessCmd(int argc, char *argv[], my_error_t &error)
{
  uint result = 0;

  switch (argc)
  {
  case 2:
	if (!strcmp(argv[1], "Q"))
	  error = err_exit;
	else if (!strcmp(argv[1], "H"))
	  error = err_help;
	else
	  error = err_bad_command;
	break;
  case 3:
	if (strlen(argv[1]) > 1)
	  error = err_bad_command;
	else
	{
	  uint m;
	  map<char, uint> j = { { 'P', 0 },{ 'B', 1 }};
	  get_numb_uno_t unoFunc[2] = { GetP, GetB };
	  string s = argv[2];

	  switch (*argv[1])
	  {
	  case 'P':
	  case 'B':
		m = s_GetDigit(s, error);
		s_CheckParam(s, error); // after int is space?
		if (error == err_ok)
		  result = unoFunc[j.find(*argv[1])->second](m, error);
		break;
	  default:
		error = err_bad_command;
	  }
	}
	break;
  case 4:
	if (strlen(argv[1]) > 1)
	  error = err_bad_command;
	else
	{
	  uint m = 0, n = 0;
	  map<char, uint> i = { { 'U', 0 },{ 'A', 1 },{ 'C', 2 },{ 'S', 3 } };
	  get_numb_double_t doubleFunc[4] = { GetU, GetA, GetC, GetS };
	  string s = argv[2];

	  switch (*argv[1])
	  {
	  case 'U':
	  case 'A':
	  case 'C':
	  case 'S':
		m = s_GetDigit(s, error);
		s_CheckParam(s, error); // after uint is space?
		if (error == err_ok)
		{
		  s = argv[3];
		  n = s_GetDigit(s, error);
		  s_CheckParam(s, error);
		}
		if (error == err_ok)
		  result = doubleFunc[i.find(*argv[1])->second](m, n, error);
		break;
	  default:
		error = err_bad_command;
	  }
	}
	break;
  default:
	error = err_too_many_symb;
  }

  return result;
} // end of func

static void s_PrintAnswer(uint ans, my_error_t error)
{
  if (error == err_ok)
	cout << ans << endl;
  else if (error == err_help)
	s_PrintHelp();
  else if (error != err_exit)
	ReportError(error);
} // end of func

// *****************
// in main functions

// interactive mode
void ProcessorMode()
{
  uint ans;
  my_error_t error = err_ok;
  bool run = true;
  string command;

  while (run)
  {
	cout << "input your command (press H for help):" << endl;
	getline(cin, command);

	ans = s_ProcessLine(run, command, error);
	s_PrintAnswer(ans, error);

	// cannot out if errors exists
	if (error > err_help) // error detected
	  run = true;

	error = err_ok;
  }
}

// work with command line arguments
void ConsoleMode(int argc, char *argv[])
{
  uint ans;
  my_error_t error = err_ok;

  ans = s_ProcessCmd(argc, argv, error);
  s_PrintAnswer(ans, error);
}
