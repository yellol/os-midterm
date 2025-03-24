#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    char filename[] = "test.txt";
    pid_t c_pid = fork();

    if (c_pid < 0) {
        perror("fork");
        return 1;
    }

    int file = open(filename, O_WRONLY);

    if (file < 0) {
        perror("open");
        return 1;
    }

    if (c_pid == 0) {
        // child process
        const char *msg = "This is the child..\n";
        write(file, msg, 25);
    } else {
        // parent process
        const char *msg = "This is the parent...\n";
        write(file, msg, 26);
    }

    return 0;
}

