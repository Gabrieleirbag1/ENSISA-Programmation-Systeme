#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

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

        // Parser les redirections
        char *input_file = NULL;
        char *output_file = NULL;
        char *args[101];
        int arg_index = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(sentence[i], "<") == 0) {
                if (i + 1 < word_count) {
                    input_file = sentence[i + 1];
                    i++;  // Sauter le nom du fichier
                }
            } else if (strcmp(sentence[i], ">") == 0) {
                if (i + 1 < word_count) {
                    output_file = sentence[i + 1];
                    i++;  // Sauter le nom du fichier
                }
            } else {
                args[arg_index++] = sentence[i];
            }
        }
        args[arg_index] = NULL;

        // Vérifier si la commande se termine par &
        int background = 0;
        if (arg_index > 0 && strcmp(args[arg_index - 1], "&") == 0) {
            background = 1;
            arg_index--;  // Retirer & de args
            args[arg_index] = NULL;
        }

        if (arg_index == 0) {
            fprintf(stderr, "Aucune commande saisie\n");
            free(buff);
            continue;
        }

        char *first_word = args[0];

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
            // Appliquer les redirections
            if (input_file) {
                int fd = open(input_file, O_RDONLY);
                if (fd == -1) {
                    perror("open input file");
                    free(full_path);
                    exit(1);
                }
                dup2(fd, 0);
                close(fd);
            }
            if (output_file) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("open output file");
                    free(full_path);
                    exit(1);
                }
                dup2(fd, 1);
                close(fd);
            }
            execv(full_path, args);
            perror("execv failed");
            free(full_path);
            exit(EXIT_FAILURE);
        } else {
            if (!background) {
                wait(NULL);
            } else {
                printf("Processus en arrière-plan lancé avec PID: %d\n", p);
            }
            free(full_path);
        }
    }
    return 0;
}