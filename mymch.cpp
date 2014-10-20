#include "mymch.hpp"

int main(int args, char* argv[]){
	if (args != 2) {
		cout << "invalid param" << endl;
		exit(0);
	}
	ifstream fin( argv[1] );
	BefungeStackMachine* A = new BefungeStackMachine(fin);
	int a[] = {0,0};
	A->run(a);
	delete(A);
	fin.close();
	return 0;
}
