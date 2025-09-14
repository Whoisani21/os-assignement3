#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void die(const char *msg) { perror(msg); _exit(1); }

int main(void) {
    setbuf(stdout, NULL);
    pid_t c1 = fork();
    if (c1 < 0) die("fork c1");
    if (c1 == 0) {
        execl("/bin/ls", "ls", "-la", (char*)NULL);
        die("execl ls");
    }
    pid_t c2 = fork();
    if (c2 < 0) die("fork c2");
    if (c2 == 0) {
        execl("/bin/date", "date", (char*)NULL);
        die("execl date");
    }
    if (waitpid(c1, NULL, 0) < 0) die("wait c1");
    if (waitpid(c2, NULL, 0) < 0) die("wait c2");
    printf("Parent process done\n");
    return 0;
}