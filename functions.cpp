#include "functions.hpp"
using namespace std;
int _move_r(Context* cont, long int c){
	cont->cur_dir = c;
	++cont->point[1];
	if (cont->width and cont->point[1] >= cont->width)
		cont->point[1] = cont->point[1] - cont->width;
	return 0;
}

int _move_l(Context* cont, long int c){
	cont->cur_dir = c;
	--cont->point[1];
	if (cont->width and cont->point[1] < 0)
		cont->point[1] = cont->width - cont->point[1];
	return 0;
}

int _move_d(Context* cont, long int c){
	cont->cur_dir = c;
	++cont->point[0];
	if (cont->length and cont->point[0] >= cont->length)
		cont->point[0] = cont->point[0] - cont->length;
	return 0;
}

int _move_u(Context* cont, long int c){
	cont->cur_dir = c;
	--cont->point[0];
	if (cont->length and cont->point[0] < 0)
		cont->point[0] = cont->length - cont->point[0];
	return 0;
}

int _void(Context* cont, long int c){
	return 0;
}

int _symbol_mode(Context* cont, long int c){
	cont->symb_mode = not cont->symb_mode;
	return 0;
}

int _end(Context* cont, long int c){
	cont->running = false;
	return -1;
}

int _rand_dir(Context* cont, long int c) {
	cont->cur_dir = "v^<>"[rand() % 4];
	return 0;
}

int _mult(Context* cont, long int c) {
	cont->push(cont->pop() * cont->pop());
	return 0;
}

int _add(Context* cont, long int c) {
	cont->push(cont->pop() + cont->pop());
	return 0;
}

int _g_if(Context* cont, long int c) {
	if (cont->pop())
		cont->cur_dir = '<';
	else
		cont->cur_dir = '>';
	return 0;
}

int _v_if(Context* cont, long int c) {
	if (cont->pop())
		cont->cur_dir = '^';
	else
		cont->cur_dir = 'v';
	return 0;
}

int _skip(Context* cont, long int c) {
	cont->skip = true;
	return 0;
}

int _logic_not(Context* cont, long int c) {
	cont->push((long int)(not (bool)(cont->pop())));
	return 0;
}

int _sub(Context* cont, long int c) {
	// TO_DO move
	auto a = cont->pop();
	auto b = cont->pop();
	cont->push(b - a);
	return 0;
}

int _div(Context* cont, long int c) {
	auto a = cont->pop();
	if (!a){
		cout << "divide by zero" << endl;
		return -1;
	}
	auto b = cont->pop();
	cont->push(b / a);
	return 0;
}

int _mod(Context* cont, long int c) {
	auto a = cont->pop();
	if (!a){
		cout << "divide by zero" << endl;
		return -1;
	}
	auto b = cont->pop();
	cont->push(b % a);
	return 0;
}

int _drop(Context* cont, long int c) {
	cont->pop();
	return 0;
}

int _swap(Context* cont, long int c) {
	auto a = cont->pop();
	auto b = cont->pop();
	cont->push(a);
	cont->push(b);
	return 0;
}

int _greater(Context* cont, long int c) {
	auto a = cont->pop();
	auto b = cont->pop();
	cont->push((long int)(b > a));
	return 0;
}

int _ask_char(Context* cont, long int c) {
	char x;
	cin >> x;
	cont->push(static_cast<long int>(x));
	return 0;
}

int _ask_int(Context* cont, long int c) {
	long int a;
	cin >> a;
	cont->push(a);
	return 0;
}

int _dup(Context* cont, long int c) {
	auto a = cont->pop();
	cont->push(a);
	cont->push(a);
	return 0;
}

int _print_char(Context* cont, long int c) {
	auto a = cont->pop();
#ifdef DEBUG
	cout << "print: '";
#endif
	// TO_DO
	cout << static_cast<char>(a);
#ifdef DEBUG
	cout << "'" << endl;
#endif
	return 0;
}

int _print_int(Context* cont, long int c) {
	auto a = cont->pop();
#ifdef DEBUG
	cout << "print: '";
#endif
	cout << a;
#ifdef DEBUG
	cout << "'" << endl;
#endif
	return 0;
}
