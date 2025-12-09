#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

char *find_path(char *cmd) {
    char *path_env = getenv("PATH");
    if (!path_env) return NULL;

    char *path_copy = strdup(path_env);
    if (!path_copy) return NULL;

    char *dir = strtok(path_copy, ":");
    while (dir) {
        char full_path[1024];
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

int main()
{
    while (1) {
        char *buff = NULL;
        size_t sizeAllocated = 0;
        printf("> ");
        size_t characters = getline(&buff, &sizeAllocated, stdin);
        if (characters == -1) {
            perror("getline failed");
            free(buff);
            exit(1);
        }
        buff[characters - 1] = '\0';

        char sentence[100][100];
        char *mot;
        int word_count = 0;

        mot = strtok(buff, " ");
        while (mot != NULL && word_count < 100) {
            strcpy(sentence[word_count], mot);
            word_count++;
            mot = strtok(NULL, " ");
        }

        if (word_count == 0) {
            free(buff);
            continue;
        }

        char *first_word = sentence[0];

        char *args[101];
        for (int i = 0; i < word_count; i++) {
            args[i] = sentence[i];
        }
        args[word_count] = NULL;

        char *full_path = find_path(first_word);
        if (!full_path) {
            fprintf(stderr, "Command not found: %s\n", first_word);
            free(buff);
            continue;
        }

        free(buff);

        pid_t p = fork();
        
        if (p < 0){
            perror("fork failed");
            free(full_path);
            exit(EXIT_FAILURE);
        }

        if (p == 0) {
            execv(full_path, args);
            perror("execv failed");
            free(full_path);
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
            free(full_path);
        }
    }
    return 0;
}