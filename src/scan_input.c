#include "main.h"

void scan_input(char *prompt, char *input_string) {
    // register the SIGINT and SIGTSTP to my_handler
    signal(SIGINT, my_handler);
    signal(SIGTSTP, my_handler);
    // call extract_external_cmd();
    extract_external_commands(external_commands);
    while(1) {
        printf(ANSI_COLOR_BLUE "%s " ANSI_COLOR_RESET,prompt);    
        fflush(stdout);
        scanf(" %[^\n]",input_string);                       // getting input string from user
        // __fpurge(stdin);
        if(strncmp("PS1=", input_string, 4) == 0) {           // check command is present or not
            // custmize the prompt
            if(input_string[4] != ' ' && input_string[4] != '\0') {
                strcpy(prompt, input_string + 4);
                continue;
            }
            else {
                printf("PS1= command not found\n");
                continue;
            }
        }
        // to get command
        char *cmd = get_command(input_string);
        
        // to check the type of command
        int cmd_type = check_command_type(cmd);
        // printf("Command type = %d\n",cmd_type);
        if(cmd_type == BUILTIN) {
            // builtin command
            execute_internal_commands(input_string);
        }
        else if(cmd_type == EXTERNAL) {
            //  external command
            
            // create a process
            // child process
                // call execute_external_cmd()
            // parent process
                // wait until the child state change
                // waitpid(pid, &status, W_UNTRACED),           pid = 0;
            int pid = fork();
            if(pid == 0) {
                // child process
                signal(SIGINT, SIG_DFL);
                signal(SIGTSTP, SIG_DFL);

                char buffer[100];
                strcpy(buffer, input_string);
                execute_external_commands(buffer);
            }
            else if(pid > 0) {
                // Parent process
                waitpid(pid, &status, WUNTRACED);

                if (WIFSTOPPED(status))
                {
                   insert_job(pid, input_string);  
                }
                // ctrl c handling
                // else if (WIFSIGNALED(status))
                // {
                //     printf("\n");
                // }
                else
                    printf("\n");

                pid = 0;
            }
        }
        else {
            // no command
            printf("Command not found: %s\n", cmd);
        }
        getchar();
        memset(input_string, 0, 50);
    }
}

void my_handler(int signum) {
    // check the signal is SIGINT
        // if pid is zero print prompt string
        if (signum == SIGINT)
        if (pid > 0)
        {
            kill(pid, signum);
            // printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, prompt);
            // fflush(stdout);
        }
}