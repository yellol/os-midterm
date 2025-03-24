// Concerns question number 6. 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h> 

using namespace std;

int main()
{
    while (true)
    {
        string programName;
        int instanceAmount = 1;
        char mode = 'p';

        cout << "closh> ";
        cin >> programName;

        cout << "count> ";
        cin >> instanceAmount;

        cout << "[p]arallel or [s]equential or e[x]it> ";
        cin >> mode;

        programName = "./" + programName;

        if (mode == 'p')
        {
            cout << endl << "Initializing parallel processes..." << endl;
            for (int i = 0; i < instanceAmount; i++) 
            {
                pid_t pid = fork();

                if (pid == 0) 
                {
                    char* args[] = { (char*)programName.c_str(), NULL };
                    execvp(programName.c_str(), args);
                    perror("execlp failed");
                    exit(1);
                }
                else if (pid < 0)
                {
                    perror("fork failed");
                }
            }
        } 
        else if (mode == 's')
        {
            cout << endl << "Initializing sequential processes..." << endl;
            for (int i = 0; i < instanceAmount; i++) 
            {
                pid_t pid = fork();

                if (pid == 0) 
                {
                    char* args[] = { (char*)programName.c_str(), NULL };
                    execvp(programName.c_str(), args);
                    perror("execlp failed");
                    exit(1);
                }
                else if (pid > 0) 
                { 
                    waitpid(pid, NULL, 0);
                } 
                else if (pid < 0) 
                {
                    perror("fork failed");
                    exit(1);
                }
            }
        }
        else
        {
            break;
        }
    }
    return 0;
}

