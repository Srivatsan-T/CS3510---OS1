#include <stdio.h>
//The header files required for fork() function
#include <unistd.h>
//Header files required for wait() function
#include <sys/wait.h>
#include<stdlib.h>
//Function which begins a child process and prints the collatz numbers while the parent process waits for the child to complete
void print_collatz(int n)
{
    //Declaring process_id as pid
    pid_t pid;
    pid = fork();

    //pid == 0 signifies that its the child process that's executing
    if (pid == 0)
    {
        printf("Beginning to print collatz numbers from child process\n");
        printf("%d :", n);
        while (n > 1)
        {
            if (n % 2 == 0)
            {
                n = n / 2;
            }
            else
            {
                n = 3 * n + 1;
            }
            printf("%d :", n);
        }
        printf("\n");
    }
    //pid > 0 signifies that its the parent process that's executing
    //The parent process prints that its waiting for child completion
    else if(pid>0)
    {
        printf("The control in parent block and is now waiting for child process to complete\n");
        wait(NULL);
    }
    //This block execution means that creation of child has failed and stops the process
    else
    {
        printf("Error in creating a child process and process stops\n");
    }
}

int main(int argc,char* argv[])
{
    int n;
    if(argc != 2)
    {
        printf("Wrong number of arguments given\n");
    }
    n = atoi(argv[1]);
    //If n<=0 means that the process has to terminate so we stop
    if (n <= 0)
    {
        printf("The number entered is not positive!\n");
    }
    //Else we execute the process
    else
    {
        print_collatz(n);
        printf("Back in main\n");
    }
    return 0;
}