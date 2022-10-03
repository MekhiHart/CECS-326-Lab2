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

	struct msgbuf{
		long mtype;
		char message[50];
	};
	msgbuf buffer;

	int size = sizeof(buffer) - sizeof(long);
	cout << "Receiver, PID " << getpid() << ", begins execution" << endl;
	cout << "Receiver message queue id " << argv[0] << " through commandline parameter\n";

	int qidBuffer;
	sscanf(argv[0],"%d", &qidBuffer); // turns message id from type int to type char[]
	

	msgrcv(qidBuffer,(struct msgbuf*) &buffer, size, 0, 0); // Pops a message from the message queue
	cout << "Receiver acnknowledged receipt of message\n";
	cout << "Retrieved the following message from message queue\n";
	cout << buffer.message << endl;
	exit(0); // terminated child process


	
}
