#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <stack>
#include <time.h>

#define DEBUG

using namespace std;
class BefungeStackMachine {
	stack<char> m_stack;
	int width;
	int length;
	int point[2];
	vector<string> program;
	char cur_dir;
	bool running;
	bool symb_mode;
	char pop() {
#ifdef DEBUG
		cout << point[0] << 'x' << point[1] << " pop: ";
#endif
		if (m_stack.empty()){
#ifdef DEBUG
		cout << "empty"<< endl;
#endif
			return 0; // befunge-93 says popping off an empty stack returns 0
		}
		char top = m_stack.top();
		m_stack.pop();
#ifdef DEBUG
		if (symb_mode)
			cout << (char)top << endl;
		else
			cout << (int)top << endl;
#endif
		return top;
	}

	void push(char c) {
		m_stack.push(c);
#ifdef DEBUG
		cout << point[0] << 'x' << point[1] << " push: " << (int)c << endl;
#endif
	}

	int move(){
		switch(cur_dir) {
			case '>':
				++point[1];
				if (width and point[1] >= width)
					point[1] = 0;
				break;
			case '<':
				--point[1];
				if (width and point[1] < 0)
					point[1] = width - point[1];
				break;
			case 'v':
				++point[0];
				if (length and point[0] >= length)
					point[0] = 0;
				break;
			case '^':
				--point[0];
				if (length and point[0] < 0)
					point[0] = length - point[0];
				break;
			default:
				exit(-1);
				//return -1;
			}
#ifdef DEBUG
		usleep(300000);
#endif
		return 0;
	}

	char getsymbol() {
		if (point[0] >= program.size()){
			int new_size;
			if (length)
				new_size = length;
			else
				new_size = point[0] * 1.5;
			program.resize(new_size);
		}
		if (point[1] >= program[point[0]].size()) {
			int new_size;
			if (length)
				new_size = length;
			else
				new_size = point[1] * 1.5;
			program[point[0]].resize(new_size, ' ');
		}
#ifdef DEBUG
		cout << "c: " << program[point[0]][point[1]] << ' ' << endl;
#endif
		return program[point[0]][point[1]];
	}

	int exec(){
		char a, b, res, symb, c = getsymbol();

		if (c == '"'){
			symb_mode = not symb_mode;
			return 0;
		}

		if (symb_mode) {
			push(c);
			return 0;
		}

		if (c == '>' or c == '<' or c == 'v' or c == '^') {
			cur_dir = c;
			return 0;
		}

		if (c == ',' or c == '.') {
			symb = pop();
			cout << symb;
			return 0;
		}

		switch (c){
			case '@':
				running = false;
				return -1;
			case '?':
				cur_dir = "v^<>"[rand() % 4];
				return 0;
			case '*':
				push(pop() * pop());
				return 0;
			case '+':
				push(pop() + pop());
				return 0;
			case 'p':
				program[pop()][pop()] = pop();
				print_program();
				return 0;
			case ':':
				push(m_stack.top());
				return 0;
			}
		push(c);
		return 0;
	}
public:
	BefungeStackMachine(ifstream& fin, int l = 0, int w = 0) : length(l), width(w) {
		running = false;
		symb_mode = false;
		srand(time(NULL));

		string line;
		while(getline(fin, line)) {
			if (!length and !width)
				program.push_back(line);
			//TO_DO 25x80
		}
	}


	~BefungeStackMachine() {
	}

	void print_program() {
		for (auto line: program)
			cout << line << endl;
	}

	int run(const int* start_point){
		running = true;
		memcpy(point, start_point, sizeof(start_point));
		cur_dir = '>';
		do{
			if (exec() or move())
				running = false;
		} while(running);
	}
};

