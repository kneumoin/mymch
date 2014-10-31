#include "context.hpp"

long int Context::pop() {
#ifdef DEBUG
	std::cout << point[0] << 'x' << point[1] << " pop: ";
#endif
	if (m_stack.empty()){
#ifdef DEBUG
	std::cout << "empty"<< std::endl;
#endif
		return 0; // befunge-93 says popping off an empty stack returns 0
	}
	long int top = m_stack.top();
	m_stack.pop();
#ifdef DEBUG
	if (symb_mode)
		std::cout << static_cast<char>(top) << std::endl;
	else
		std::cout << top << std::endl;
#endif
	return top;
}

void Context::push(long int c) {
	m_stack.push(c);
#ifdef DEBUG
	std::cout << point[0] << 'x' << point[1] << " push: " << c << std::endl;
#endif
}
