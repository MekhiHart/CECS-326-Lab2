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
	cout << "This is the receiver, PID " << getpid() << ", begins execution" << endl;
	cout << "Receiver message queue id " << argv[0] << " through commandline parameter\n";

	int argBuffer;
	cout << "\nCheck 1" << endl;
	sscanf(argv[0],"%d", &argBuffer);
	cout << "Check 2" << endl;
	
	msgrcv(argBuffer,(struct msgbuf*) &buffer, size, 113, 0);
	cout << "Check 3" << endl;
	cout << "Receiver acnknowledged receipt of message\n";
	cout << "Retrieved the following message from message queue\n";
	cout << buffer.message;



	
}
