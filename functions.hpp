#include <cstdlib>
#include <time.h>

#include "context.hpp"

int _move_r(Context*);
int _move_l(Context*);
int _move_d(Context*);
int _move_u(Context*);
int _void(Context*);
int _symbol_mode(Context*);
int _end(Context* cont);
int _rand_dir(Context*);
int _mult(Context* cont);
int _add(Context* cont);
int _g_if(Context* cont);
int _v_if(Context* cont);
int _skip(Context* cont);
int _logic_not(Context*);
int _sub(Context*);
int _div(Context*);
int _mod(Context*);
int _drop(Context*);
int _swap(Context*);
int _greater(Context*);
int _ask_char(Context*);
int _ask_int(Context*);
int _dup(Context*);
int _print_char(Context*);
int _print_int(Context*);
