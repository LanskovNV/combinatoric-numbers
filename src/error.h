#pragma once
#ifndef _ERROR_H
#define _ERROR_H

// leins, 05.04.2018

typedef unsigned int uint;

typedef enum {
  err_ok,
  err_exit,
  err_help,
  err_no_memory, //
  err_bad_command, //
  err_too_many_symb,
  err_less_param, //
  err_bad_param // 
}my_error_t;

void ReportError(my_error_t error);

#endif
