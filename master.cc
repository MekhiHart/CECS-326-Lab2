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

	cout << "Master, PID " << getpid() << ",begins execution" << endl;
	int qid = msgget(IPC_PRIVATE, IPC_EXCL|IPC_CREAT|0666); // new message queue is located as the queue identifier

	cout << "Master acquired a message queue, id " << qid << endl;
	pid_t cpid = fork(); // creates sender process
	

	char messageID_buffer[10];
	sprintf(messageID_buffer,"%d", qid); // turning queue identifier into an int type

	if (cpid == 0){ // Sender process
	cout << "Master created a child process with PID: " << getpid() << " to execute sender" << endl;
	execlp("./sender",messageID_buffer,NULL); // loads sender binary file into memory and replacing current process image

	exit(0); // terminated process
	}

	cpid = fork(); // creates new child process for receiver process

	if (cpid == 0){  // receiver
	cout << "Master created a child process with PID: " << getpid() << " to execute receiver" << endl;
	execlp("./receiver",messageID_buffer,NULL); // loads receiver binary file into memory and replacing current process image
	exit(0); // terminates process
	}

	cout << "Master waits for both child process to terminate" << endl;
	while(wait(NULL) != -1); // blocks code after it when all child processes has terminated
	msgctl(qid, IPC_RMID,NULL); // removes message queue with the IPC_RMID argument
	cout << "Master received termination signals from both child processes, removed message queue, and terminates\n";

	exit(0); // terminated master process
}
