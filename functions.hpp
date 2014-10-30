#include <cstdlib>
#include <time.h>

#include "context.hpp"

int _move_r(Context*, long int);
int _move_l(Context*, long int);
int _move_d(Context*, long int);
int _move_u(Context*, long int);
int _void(Context*, long int);
int _symbol_mode(Context*, long int);
int _end(Context* cont, long int c);
int _rand_dir(Context*, long int);
int _mult(Context* cont, long int c);
int _add(Context* cont, long int c);
int _g_if(Context* cont, long int c);
int _v_if(Context* cont, long int c);
int _skip(Context* cont, long int c);
int _logic_not(Context*, long int);
int _sub(Context*, long int);
int _div(Context*, long int);
int _mod(Context*, long int);
int _drop(Context*, long int);
int _swap(Context*, long int);
int _greater(Context*, long int);
int _ask_char(Context*, long int);
int _ask_int(Context*, long int);
int _dup(Context*, long int);
int _print_char(Context*, long int);
int _print_int(Context* cont, long int c);
