#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char CHILD[] = "Child";
const char PARENT[] = "Parent";
const int N_FORKS = 10;

int main(int argc, char **argv)
{
    int i;
    pid_t child_pid = 0;
    for (i = 0; i < 10; i++)
    {
        child_pid = fork();
        if (child_pid == 0)
        {
            break;
        }
        else if (child_pid < 0)
        {
            printf("error on fork()\n");
            break;
        }
    }
    if (child_pid == 0)
    {
        sleep(1);
    }
    else
    {
        printf("I'm the Parent and I'm waiting my children...\n");
        pid_t completed_child_pid;
        while ((completed_child_pid = wait(NULL)) > 0) {
            printf("I'm the parent and acknowledged that the Child %d has finished!\n", completed_child_pid);
            fflush(stdout);
        }
        printf("My children finished their work!\n");
    }
    printf("%s %d: My work here is done!\n", child_pid == 0 ? CHILD : PARENT, getpid());
    fflush(stdout);
    return 0;
}