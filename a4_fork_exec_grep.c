#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void die(const char *msg) { perror(msg); _exit(1); }

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <word-to-search>\n", argv[0]);
        return 2;
    }
    const char *word = argv[1];
    const char *file = "test.txt";
    pid_t pid = fork();
    if (pid < 0) die("fork");
    if (pid == 0) {
        execl("/bin/grep", "grep", word, file, (char*)NULL);
        die("execl grep");
    }
    if (waitpid(pid, NULL, 0) < 0) die("waitpid");
    printf("Parent process completed\n");
    return 0;
}