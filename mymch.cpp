#include "mymch.hpp"

int main(){
	ifstream fin( "hello.bf" );
	BefungeStackMachine* A = new BefungeStackMachine(fin);
	int a[] = {0,0};
	A->print_program();
	A->run(a);
	delete(A);
	fin.close();
	return 0;
}
