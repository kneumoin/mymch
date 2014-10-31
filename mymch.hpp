#include <vector>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <map>
#include <unistd.h>

#define VERSION 0.11

//#define DEBUG

using namespace std;

// TO_DO----------------------------------------------------
void resize_line(long int*& old_one, int new_size, long int z) {
	long int* new_one = new long int[new_size + 1];
	old_one = &old_one[-1];
	int i, old_size = static_cast<int>(old_one[0]);
	new_one[0] = new_size;
	for (i = 1; i < new_size; ++i)
		new_one[i] = (i <= old_size) ? old_one[i] : z;
	delete[] old_one;
	old_one = &new_one[1];
}

unsigned int get_line_size(long int* line) {
	line = &line[-1];
	return line[0];
}
//----------------------------------------------------------

typedef int (*Function)(Context*);
typedef map<long int, Function> function_table;

class BefungeStackMachine {
	vector<long int*> program;
	Context cont;
	function_table ft;

	int move(void);
	int exec(void);
	long int getsymbol(void);
public:

	~BefungeStackMachine();
	BefungeStackMachine(ifstream&, long int, long int);

	void print_program(void);
	void run(PP&&);
};
