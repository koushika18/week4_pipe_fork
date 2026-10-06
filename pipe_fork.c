#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello from the parent process!";
    char buffer[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(fd[0]);

        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);

        wait(NULL);

        printf("Parent: Message sent to child through pipe.\n");
    }
    else {
        // Child process
        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));
        close(fd[0]);

        printf("Child: Received message: %s\n", buffer);
    }

    return 0;
}
