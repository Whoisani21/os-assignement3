#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void die(const char *msg) {
    perror(msg);
    _exit(1);
}

int main(void) {
    setbuf(stdout, NULL);
    pid_t pid;
    printf("[start] PID=%d, PPID=%d\n", getpid(), getppid());

    pid = fork();
    if (pid < 0) die("fork 1");
    printf("[after fork1] PID=%d, PPID=%d, fork1 returned %d\n", getpid(), getppid(), (int)pid);

    pid = fork();
    if (pid < 0) die("fork 2");
    printf("[after fork2] PID=%d, PPID=%d, fork2 returned %d\n", getpid(), getppid(), (int)pid);

    pid = fork();
    if (pid < 0) die("fork 3");
    printf("[after fork3] PID=%d, PPID=%d, fork3 returned %d\n", getpid(), getppid(), (int)pid);

    sleep(1);
    while (waitpid(-1, NULL, 0) > 0) {}
    return 0;
}