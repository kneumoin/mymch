#include "context.hpp"

long int Context::pop() {
#ifdef DEBUG
	cout << point[0] << 'x' << point[1] << " pop: ";
#endif
	if (m_stack.empty()){
#ifdef DEBUG
	cout << "empty"<< endl;
#endif
		return 0; // befunge-93 says popping off an empty stack returns 0
	}
	long int top = m_stack.top();
	m_stack.pop();
#ifdef DEBUG
	if (symb_mode)
		cout << static_cast<char>(top) << endl;
	else
		cout << top << endl;
#endif
	return top;
}

void Context::push(long int c) {
	m_stack.push(c);
#ifdef DEBUG
	cout << point[0] << 'x' << point[1] << " push: " << c << endl;
#endif
}
