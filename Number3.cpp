// Concerns question number 6. 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    pid_t c_pid = fork();

    if (c_pid < 0) {
        perror("fork");
        return 1;
    }

    if (c_pid != 0) {
        // child process
        cout << "Hello!" << endl;

    } else {
        // parent process
        usleep(100);
        cout << "Goodbye!" << endl;
    }

    return 0;
}

