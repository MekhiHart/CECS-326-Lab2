#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <cstdio>
#include <sys/wait.h>
using namespace std;

int main(int argc, char **argv){
	struct msgbuf{
		long mtype;
		char greeting[50];
	};
	int qid = msgget(IPC_PRIVATE, IPC_EXCL|IPC_CREAT|0600);
	cout << "Master, PID " << getpid() << ",begins execution" << endl;

	pid_t cpid = fork(); // sender process

	if (cpid == 0){
	cout << "Master created a child process with PID " << getpid() << " to execute sender\n";
	execlp("./sender","cool",NULL);
	exit(0);
	}

	cpid = fork();

	if (cpid == 0){ 
	cout << "Master created a child process with PID " << getpid() << " to execute receiver\n";
	exit(0);
	}
	wait(NULL);
	msgctl(qid, IPC_RMID,NULL);
	exit(0);
}
