#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    //we have an initial parent proecess P
    //P should create 2 child processes, Child1 and Child2
    //Process P will create process Child1

    int child_1_pid, child_2_pid, status;
    child_1_pid = fork();

    if(child_1_pid == -1)
    {
        printf("fork failed\n");
    } else if(child_1_pid == 0)
    {
        //this is the first child process block
        printf("i am the first child! parent id: %d\n", getppid());
    } else
    {
        //currently parent block (before second fork)
        wait(&status);
        child_2_pid = fork();
        if(child_2_pid == -1)
        {
            printf("second fork failure\n");
        } else if(child_2_pid == 0)
        {
            //second child process block
            printf("i am the second child! parent pid: %d\n", getppid());
        } else
        {
            //new parent block (after second fork)
            wait(&status);
            printf("i am the parent with ID %d\n", getpid());
        }
    }



    
    // then will immediately create
    // process Child2 and then will wait for 
    // both child processes to finish their execution;
    // in the end it will display the message “I am the Parent 
    // process and my pid is ... . Both my children
    // finished their execution.” (the ellipsis stand for the actual pid 
    // value which should be an integer number)









    //Child1 creates its own process, GrandChild1
    //Child2 creates it own process, GrandChild2
    return 0;
}