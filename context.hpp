#include <iostream>
#include <stack>

//#define DEBUG

class Context {
	std::stack<long int> m_stack;
public:
	unsigned int width;
	unsigned int length;
	unsigned int point[2];
	long int cur_dir;
	bool symb_mode;
	bool running;
	bool skip;
	long int pop(void);
	void push(long int);
};


