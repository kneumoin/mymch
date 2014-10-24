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

void resize_line(long int*& old_one, int new_size, long int z) {
	long int* new_one = new long int[new_size + 1];
	old_one = &old_one[-1];
	int i, old_size = static_cast<int>(old_one[0]);
	new_one[0] = new_size;
	// TO_DO VVV
	for (i = 1; i <= old_size; ++i){
		new_one[i] = old_one[i];
	}
	for (; i < new_size; ++i){
		new_one[i] = z;
	}
	delete[] old_one;
	old_one = new_one;
}

int get_line_size(long int* line) {
	line = &line[-1];
	return line[0];
}

class BefungeStackMachine {
	stack<long int> m_stack;
	unsigned int width;
	unsigned int length;
	unsigned int point[2];
	vector<long int*> program;
	char cur_dir;
	bool running;
	bool symb_mode;
	long int pop() {
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

	void push(long int c) {
		m_stack.push(c);
#ifdef DEBUG
		cout << point[0] << 'x' << point[1] << " push: " << c << endl;
#endif
	}

	int move(){
		switch(cur_dir) {
			case '>':
				++point[1];
				if (width and point[1] >= width)
					point[1] = point[1] - width;
				break;
			case '<':
				--point[1];
				if (width and point[1] < 0)
					point[1] = width - point[1];
				break;
			case 'v':
				++point[0];
				if (length and point[0] >= length)
					point[0] = point[0] - length;
				break;
			case '^':
				--point[0];
				if (length and point[0] < 0)
					point[0] = length - point[0];
				break;
			default:
				return -1;
			}
#ifdef DEBUG
		usleep(150000);
#endif
		return 0;
	}

	long int getsymbol() {
		int new_size;
		if (point[0] >= program.size()){
			if (length)
				new_size = length;
			else
				new_size = point[0] * 1.5;
			program.resize(new_size);
		}
		if (point[1] >= get_line_size(program[point[0]])) {
			if (length)
				new_size = length;
			else
				new_size = point[1] * 1.5;
			resize_line(program[point[0]], new_size, static_cast<long int>(' '));
		}
#ifdef DEBUG
		cout << "c: " << program[point[0]][point[1]] << "(" << static_cast<char>(program[point[0]][point[1]]) << ")" << endl;
#endif
		return program[point[0]][point[1]];
	}

	int exec(){
		long int a, b, c = getsymbol();
		char x[2] = {0};

		if (symb_mode && c != '"') {
			push(c);
			return 0;
		}

		if (c == '>' or c == '<' or c == 'v' or c == '^') {
			cur_dir = c;
			return 0;
		}

		if (c == ',') {
			a = pop();
#ifdef DEBUG
			cout << "print: '";
#endif
			cout << static_cast<char>(a);
#ifdef DEBUG
			cout << "'" << endl;
#endif
			return 0;
		}

		if (c == '.') {
			a = pop();
			cout << a;
			return 0;
		}

		switch (c){
			case ' ':
				return 0;
			case '"':
				symb_mode = not symb_mode;
				return 0;
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
				return 0;
			case 'g':
				push(program[pop()][pop()]);
				return 0;
			case '_':
				if (pop())
					cur_dir = '<';
				else
					cur_dir = '>';
				return 0;
			case '|':
				if (pop())
					cur_dir = '^';
				else
					cur_dir = 'v';
				return 0;
			case '#':
				move();
				return 0;
			case '!':
				push(static_cast<long int>(not static_cast<bool>(pop())));
				return 0;
			case '-':
				a = pop();
				b = pop();
				push(b - a);
				return 0;
			case '/':
				a = pop();
				if (!a){
					cout << "divide by zero" << endl;
					return -1;
				}
				b = pop();
				push(b / a);
			case '%':
				cout << static_cast<char>(c) << " not empl" << endl;
				return -1;
			case '$':
				cout << static_cast<char>(c) << " not empl" << endl;
				return -1;
			case '\\':
				a = pop();
				b = pop();
				push(a);
				push(b);
				return 0;
			case '`':
				a = pop();
				b = pop();
				push(static_cast<int>(b > a));
				return 0;
			case '~':
				a = static_cast<long int>(cin.get());
				push(a);
				return 0;
			case '&':
				a = static_cast<long int>(cin.get()) - static_cast<long int>(' ');
				push(a);
				return 0;
			case ':':
				a = pop();
				push(a);
				push(a);
				return 0;
			}
		push(c - '0');
		return 0;
	}
public:
	BefungeStackMachine(ifstream& fin, int l = 0, int w = 0) : length(l), width(w) {
		if (length or width) {
			//TO_DO 25x80
			throw;
		}
		running = false;
		symb_mode = false;
		srand(time(NULL));
		long int *converted_line;

		string line;
		while(getline(fin, line)) {
			converted_line = new long int[line.length() + 1];
			converted_line[0] = line.length();
			converted_line = &converted_line[1];
			for(int i = 0; i < line.length(); ++i)
				converted_line[i] = line[i];
			program.push_back(converted_line);
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
#ifdef DEBUG
			cout << endl;
#endif
		} while(running);
	}
};

