#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char **argv){
	struct msgbuf{
		long mtype;
		char message[50]; // message
	};
	msgbuf buffer;
	string strBuffer;
	int argBuffer;
	int size = sizeof(buffer) - sizeof(long);

	cout << "\nSender PID " << getpid() << " begins execution" <<  endl;
	cout << "Sender recieved message queue id " << argv[0] << " through commandline parameter\n";

	cout << "Sender: Please input your message\n";

	cin.getline(buffer.message,50); // user input
	buffer.mtype = 120; // has to be a positive integer for type to be read
	cout << buffer.message << endl;
	sscanf(argv[0], "%d", &argBuffer); // turning qid into an int type

	cout << "Sender Buffer: " << argBuffer << " " <<  argBuffer + 3 << endl;
	msgsnd(argBuffer, (struct msgbuf *) &buffer, size, 121); // sends message
	exit(0);
}
