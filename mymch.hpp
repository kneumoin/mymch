#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <stack>
#include <time.h>

//#define DEBUG

using namespace std;
class BefungeStackMachine {
	stack<char> m_stack;
	int width;
	int length;
	int point[2];
	vector<string> program;
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
				return -1;
			}
#ifdef DEBUG
		usleep(300000);
		cout << point[0] << ':' << point[1] << endl;
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
		cout << "c: " << program[point[0]][point[1]] << ' ';
#endif
		return program[point[0]][point[1]];
	}

	int exec(){
		char c = getsymbol();

		if (c == '>' or c == '<' or c == 'v' or c == '^') {
				cur_dir = c;
				return 0;
		}

		if (c == ',' or c == '.') {
			char symb = pop();
			if (symb == -1)
				return -1;
			cout << symb;
			return 0;
		}

		switch (c){
			case ' ':
				return 0;
			case '"':
				push_on = not push_on;
				return 0;
			case '@':
				running = false;
				return -1;
			case '?':
				cur_dir = "v^<>"[rand() % 4];
				return 0;
			}

		if (push_on or (c >= '0' and c <= '9')) {
			int i = c - (int)'0';
			push(c);
			return 0;
		}
		cout << endl << "Stop, new symbol: '" << c << '\''<< endl;
		return -1;
	}
public:
	BefungeStackMachine(ifstream& fin, int l = 0, int w = 0) : length(l), width(w) {
		running = false;
		push_on = false;
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

