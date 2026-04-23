#include "main.h"


void execute_internal_commands(char *input_string) {
    // check the input string is "exit"
    //      use exit() to terminate mini
    if(strcmp("exit", input_string) == 0)
        exit(0);

    // check the input string is "pwd"
    //      use getcwd to get current working directory path
    char cwd[100];
    if(strcmp("pwd", input_string) == 0) {
        getcwd(cwd, 100);
        printf("%s\n",cwd);
    }

    // check the input string is "cd"
    //      use chdir() to change our directory         (input_string + 3)
    if(strncmp("cd", input_string, 2) == 0) {
        if(chdir(input_string + 3) == -1) {
            printf("-bash: cd: %s: No such file or directory\n",input_string + 3);
        }
    }

    if (strcmp(input_string, "jobs") == 0){
        // printf("Jobs list:\n");
        display_jobs();
        return;
    }

    if (strcmp(input_string, "fg") == 0){
        fg_job();
        return;
    }

    if (strcmp(input_string, "bg") == 0){
        bg_job();
        return;
    }

    if (strncmp(input_string, "echo", 4) == 0){
        echo(input_string, status);
        return;
    }
}

void execute_external_commands(char *input_string)
{
    char cmd[100];
    int cmd_ind_arr[50];
    int i, j = 1, cmd_count = 1;
    int prev_fd = -1, pipe_fd[2];

    strcpy(cmd, input_string);

    // Tokenize
    i = 0;
    char *token = strtok(cmd, " ");
    while(token) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    // Find pipes
    cmd_ind_arr[0] = 0;
    for(i = 0; argv[i]; i++) {
        if(strcmp(argv[i], "|") == 0) {
            argv[i] = NULL;
            cmd_ind_arr[j++] = i + 1;
            cmd_count++;
        }
    }

    // No pipe
    if(cmd_count == 1) {
        execvp(argv[0], argv);
        perror("execvp");
        return;
    }

    // n pipes
    for(i = 0; i < cmd_count; i++) {

        if(i < cmd_count - 1)
            pipe(pipe_fd);

        if(fork() == 0) {

            if(prev_fd != -1) {
                dup2(prev_fd, 0);
                close(prev_fd);
            }

            if(i < cmd_count - 1) {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], 1);
                close(pipe_fd[1]);
            }

            execvp(argv[cmd_ind_arr[i]], &argv[cmd_ind_arr[i]]);
            perror("execvp");
            exit(1);
        }

        if(prev_fd != -1)
            close(prev_fd);

        if(i < cmd_count - 1) {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }
    }

    while(wait(NULL) > 0);
}

void echo(char *input_string, int status)
{
    char *token = strtok(input_string, " ");
    token = strtok(NULL, " ");

    while (token != NULL) {
        if (strcmp(token, "$?") == 0)
            printf("%d ", WEXITSTATUS(status));
        else if (strcmp(token, "$$") == 0)
            printf("%d ", getpid());
        else if (token[0] == '$') {
            char *env_var = getenv(token + 1);
            if (env_var != NULL) {
                printf("%s ", env_var);
            }
        }
        else {
            printf("%s ", token);
        }
        token = strtok(NULL, " ");
    }
    printf("\n");
}
