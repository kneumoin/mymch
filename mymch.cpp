#include "mymch.hpp"

const char* const PROGRAM[] = {">                          v", "@,,,,,,,,,,,,\"Hello World!\"<", "                            "};

int main(){
	BefungeStackMachine* A = new BefungeStackMachine(PROGRAM, sizeof(PROGRAM)/sizeof(*PROGRAM));
	int a[] = {0,0};
	//A->print_program();
	A->run(a);
	delete(A);
	return 0;
}
