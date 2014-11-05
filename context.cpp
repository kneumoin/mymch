#include "context.hpp"

long int Context::pop() {
	if (m_stack.empty()){
		return 0; // befunge-93 says popping off an empty stack returns 0
	}
	long int top = m_stack.top();
	m_stack.pop();
	return top;
}

void Context::push(long int c) {
	m_stack.push(c);
}

Context::Context() {
	length = 0;
	width = 0;
	running = false;
	symb_mode = false;
	cur_dir = '>';
}
