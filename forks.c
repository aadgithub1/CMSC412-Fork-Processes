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
        int child_2_pid = fork(); //immediate fork to Child2
        if(child_2_pid == -1)
        {
            printf("Child2 fork failure.\n");
        } else if(child_2_pid == 0)
        {
            //Current Child2 process block
            int grandchild_2_pid = fork(); //immediate fork to Grandchild2
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
            //New parent block (after Child2 fork)
            wait(&status); //wait on both children to signal
            wait(&status);
            printf("I am the Parent process and my pid is %d. "
            "Both my children finished their execution.\n", getpid());
        }
    }
    return 0;
}