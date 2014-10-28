#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <stack>
#include <time.h>
#include <map>

#define VERSION 0.1

//#define DEBUG

using namespace std;

void resize_line(long int*& old_one, int new_size, long int z) {
	long int* new_one = new long int[new_size + 1];
	old_one = &old_one[-1];
	int i, old_size = static_cast<int>(old_one[0]);
	new_one[0] = new_size;
	for (i = 1; i < new_size; ++i){
		new_one[i] = (i <= old_size) ? old_one[i] : z;
	}
	delete[] old_one;
	old_one = new_one;
}

int get_line_size(long int* line) {
	line = &line[-1];
	return line[0];
}

class Context {
	stack<long int> m_stack;
public:
	unsigned int width;
	unsigned int length;
	unsigned int point[2];
	long int cur_dir;
	bool symb_mode;
	bool running;
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
};

typedef int (*Function)(Context*);
typedef map<long int, Function> function_table;

int move_r(Context* cont){
	++cont->point[1];
	if (cont->width and cont->point[1] >= cont->width)
		cont->point[1] = cont->point[1] - cont->width;
	return 0;
}

int move_l(Context* cont){
	--cont->point[1];
	if (cont->width and cont->point[1] < 0)
		cont->point[1] = cont->width - cont->point[1];
	return 0;
}

int move_d(Context* cont){
	++cont->point[0];
	if (cont->length and cont->point[0] >= cont->length)
		cont->point[0] = cont->point[0] - cont->length;
	return 0;
}

int move_u(Context* cont){
	--cont->point[0];
	if (cont->length and cont->point[0] < 0)
		cont->point[0] = cont->length - cont->point[0];
	return 0;
}

class BefungeStackMachine {
	vector<long int*> program;
	Context cont;
	function_table ft;

	int move(){
#ifdef DEBUG
		usleep(150000);
#endif
		try {
			return ft[cont.cur_dir](&cont);
		}
		catch(...) {
			return -1;
		}
	}

	long int getsymbol() {
		int new_size;
		if (cont.point[0] >= program.size()){
			if (cont.length)
				new_size = cont.length;
			else
				new_size = cont.point[0] * 1.5;
			program.resize(new_size);
		}
		if (cont.point[1] >= get_line_size(program[cont.point[0]])) {
			if (cont.length)
				new_size = cont.length;
			else
				new_size = cont.point[1] * 1.5;
			resize_line(program[cont.point[0]], new_size, static_cast<long int>(' '));
		}
#ifdef DEBUG
		cout << "c: " << program[cont.point[0]][cont.point[1]] << \
			"(" << static_cast<char>(program[cont.point[0]][cont.point[1]]) << ")" << endl;
#endif
		return program[cont.point[0]][cont.point[1]];
	}

	int exec(){
		long int a, b, c = getsymbol();
		char x[2] = {0};

		if (cont.symb_mode && c != '"') {
			cont.push(c);
			return 0;
		}

		if (c == '>' or c == '<' or c == 'v' or c == '^') {
			cont.cur_dir = c;
			return 0;
		}

		if (c == ',') {
			a = cont.pop();
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
			a = cont.pop();
#ifdef DEBUG
			cout << "print: '";
#endif
			cout << a;
#ifdef DEBUG
			cout << "'" << endl;
#endif
			return 0;
		}

		switch (c){
			case ' ':
				return 0;
			case '"':
				cont.symb_mode = not cont.symb_mode;
				return 0;
			case '@':
				cont.running = false;
				return -1;
			case '?':
				cont.cur_dir = "v^<>"[rand() % 4];
				return 0;
			case '*':
				cont.push(cont.pop() * cont.pop());
				return 0;
			case '+':
				cont.push(cont.pop() + cont.pop());
				return 0;
			case 'p':
				program[cont.pop()][cont.pop()] = cont.pop();
				return 0;
			case 'g':
				cont.push(program[cont.pop()][cont.pop()]);
				return 0;
			case '_':
				if (cont.pop())
					cont.cur_dir = '<';
				else
					cont.cur_dir = '>';
				return 0;
			case '|':
				if (cont.pop())
					cont.cur_dir = '^';
				else
					cont.cur_dir = 'v';
				return 0;
			case '#':
				move();
				return 0;
			case '!':
				cont.push(static_cast<long int>(not static_cast<bool>(cont.pop())));
				return 0;
			case '-':
				a = cont.pop();
				b = cont.pop();
				cont.push(b - a);
				return 0;
			case '/':
				a = cont.pop();
				if (!a){
					cout << "divide by zero" << endl;
					return -1;
				}
				b = cont.pop();
				cont.push(b / a);
			case '%':
				a = cont.pop();
				if (!a){
					cout << "divide by zero" << endl;
					return -1;
				}
				b = cont.pop();
				cont.push(b % a);
				return 0;
			case '$':
				cont.pop();
				return 0;
			case '\\':
				a = cont.pop();
				b = cont.pop();
				cont.push(a);
				cont.push(b);
				return 0;
			case '`':
				a = cont.pop();
				b = cont.pop();
				cont.push(static_cast<long int>(b > a));
				return 0;
			case '~':
				char x;
				cin >> x;
				cont.push(static_cast<long int>(x));
				return 0;
			case '&':
				cin >> a;
				cont.push(a);
				return 0;
			case ':':
				a = cont.pop();
				cont.push(a);
				cont.push(a);
				return 0;
			}
		cont.push(c - '0');
		return 0;
	}
public:
	BefungeStackMachine(ifstream& fin, long int l = 0, long int w = 0) {
		cont.length = l;
		cont.width = w;
		if (cont.length or cont.width) {
			//TO_DO 25x80
			throw;
		}
		cont.running = false;
		cont.symb_mode = false;
		ft.insert(make_pair((long int)'>', &move_r));
		ft.insert(make_pair((long int)'<', &move_l));
		ft.insert(make_pair((long int)'^', &move_u));
		ft.insert(make_pair((long int)'v', &move_d));

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
		cont.running = true;
		memcpy(cont.point, start_point, sizeof(start_point));
		cont.cur_dir = '>';
		do{
			if (exec() or move())
				cont.running = false;
#ifdef DEBUG
			cout << endl;
#endif
		} while(cont.running);
	}
};

