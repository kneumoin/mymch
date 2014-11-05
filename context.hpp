#include <iostream>
#include <stack>

typedef unsigned int PP[2];

class Context {
	std::stack<long int> m_stack;
public:
	Context();
	unsigned int width;
	unsigned int length;
	PP point;
	long int cur_dir;
	bool symb_mode;
	bool running;
	bool skip;
	long int pop(void);
	void push(long int);
};


