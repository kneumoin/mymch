#include <iostream>
#include <stack>

//#define DEBUG

typedef unsigned int PP[2];

class Context {
	std::stack<long int> m_stack;
public:
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


