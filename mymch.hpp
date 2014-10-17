#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

using namespace std;
class BefungeStackMachine {
	stack<char> m_stack;
	int width;
	int length;
	int point[2];
	char** program;
	char cur_dir;
	bool running;
	bool push_on;
	char pop() {
		if (m_stack.empty())
			return -1;
		char top = m_stack.top();
		m_stack.pop();
		return top;
	}

	void push(char c) {
		m_stack.push(c);
	}

	int move(){
		switch(cur_dir) {
			case '>':
				++point[1];
				if (point[1] >= width)
					point[1] = 0;
				break;
			case '<':
				--point[1];
				if (point[1] < 0)
					point[1] = width - point[1];
				break;
			case 'v':
				++point[0];
				if (point[0] >= length)
					point[0] = 0;
				break;
			case '^':
				--point[0];
				if (point[0] < 0)
					point[0] = length - point[0];
				break;
			default:
				return -1;
			}
		return 0;
	}

	int exec(){
		char symb, c = program[point[0]][point[1]];
		switch (c){
			case '>': case '<': case 'v': case '^':
				cur_dir = c;
				return 0;
			case '"':
				push_on = not push_on;
				return 0;
			case ',':
				symb = pop();
				if (symb == -1)
					return -1;
				cout << symb;
				break;
			case '@':
				running = false;
				return -1;
			}
		if (push_on) {
			push(c);
			return 0;
		}
		return 0;
	}
public:
	BefungeStackMachine(const char* const src[], int src_l, int l = 25, int w = 80) : length(l), width(w) {
		program = new char*[l];
		running = false;
		push_on = false;

		for(int i = 0, j = 0; i < l; ++i){
			program[i] = new char[w];
			memset(program[i], 0, sizeof(char) * w);
			if (j < src_l){
				memcpy(program[i], src[j], strlen(src[j]));
				++j;
			}
		}
	}


	~BefungeStackMachine() {
		for(int i = 0; i < length; ++i)
			delete program[i];
		delete program;
	}

	void print_program() {
		for(int i = 0; i < length; ++i)
			cout << program[i] << endl;
	}

	int run(const int* start_point){
		running = true;
		memcpy(point, start_point, sizeof(start_point));
		cur_dir = program[point[0]][point[1]];
		do{
			if (exec() or move())
				running = false;
		} while(running);
	}
};

