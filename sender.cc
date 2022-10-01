#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char **argv){
	cout << "\nThis is the sender process" << endl;
	cout << argv[0] << endl;
	exit(0);
}
