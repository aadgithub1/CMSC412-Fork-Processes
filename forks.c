//Aaron Webb
//Jan 14, 2025
//CMSC412
//Professor Alin Suciu

/*
This program demonstrates the ability to fork
processes in the C programming language
using the below header files.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    int child_1_pid, status;
    child_1_pid = fork();

    if(child_1_pid == -1)
    {
        printf("Fork failed\n");
    } else if(child_1_pid == 0)
    {
        //Currently Child1 process block
        int grandchild_1_pid = fork();
        if(grandchild_1_pid == -1)
        {
            printf("Grandchild1 fork failed.\n");
        } else if(grandchild_1_pid == 0)
        {
            //Grandchild1 process block
            printf("I am the process Grandchild1 and my pid is %d. "
            "My parent pid is %d.\n", getpid() , getppid());
        } else
        {
            //New Child1 process block after GC fork
            wait(&status); //wait for child process (Grandchild1) to finish
            printf("I am the process Child1 and my pid is %d. "
            "My parent pid is %d.\n", getpid(), getppid());
        }
        
    } else
    {
        //Current Parent process block
        wait(&status); //wait for Child1 so it can't erroneously signal Parent
        int child_2_pid = fork();
        if(child_2_pid == -1)
        {
            printf("Child2 fork failure.\n");
        } else if(child_2_pid == 0)
        {
            //Current Child2 process block
            int grandchild_2_pid = fork();
            if(grandchild_2_pid == -1)
            {
                printf("Grandchild2 fork failure.\n");
            } else if (grandchild_2_pid == 0)
            {
                printf("I am the process Grandchild2 and my pid is %d. "
                "My parent pid is %d.\n", getpid(), getppid());
            } else {
                wait(&status); //wait for child (Grandchild2) to finish
                printf("I am the process Child2 and my pid is %d. "
                "My parent pid is %d.\n", getpid(), getppid());
            }
        } else
        {
            //New parent block (Child2 fork)
            wait(&status); //wait on Child2 to finish
            printf("I am the Parent process and my pid is %d. "
            "Both my children finished their execution.\n", getpid());
        }
    }
    return 0;
}