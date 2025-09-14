#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void die(const char *msg) { perror(msg); _exit(1); }

int main(void) {
    setbuf(stdout, NULL);
    pid_t pid = fork();
    if (pid < 0) die("fork");
    if (pid == 0) {
        execl("/bin/ls", "ls", "-la", (char*)NULL);
        die("execl ls");
    }
    if (waitpid(pid, NULL, 0) < 0) die("waitpid");
    printf("Parent process done\n");
    return 0;
}