#include "main.h"


char *get_command(char *input_string) {
    // Declare a cmd string and allocate memory dynamically
    // check the input string character by character till '/0' or ' '
    //          store the inp[] to cmd[]
    // store '\0' to the cmd[]
    // return the cmd
    char *cmd = (char *) calloc(50, sizeof(char));
    int i = 0;
    while(input_string[i] != ' ' && input_string[i] != '\0')
        cmd[i++] = input_string[i];
    cmd[i] = '\0';
    return cmd;
}
int check_command_type(char *command) {
    // declare 2d array for builtin commands
    /*List of builtin commands */
	char *builtin_cmd[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "jobs", "fg", "bg", NULL};
    
    // check the cmd is builtin command (untill NULL add)
    //      return builtin
    int i = 0;
    for(i=0;builtin_cmd[i]!=NULL;i++) {
        if(strcmp(command, builtin_cmd[i]) == 0)
            return BUILTIN;
    }
    // check the cmd is external command (untill NULL add)
    //      return External
    for(i=0;external_commands[i]!=NULL;i++) {
        if(strncmp(command, external_commands[i], strlen(command)) == 0)
            return EXTERNAL;
    }

    // return no command
    return NO_COMMAND;
}
void extract_external_commands(char **external_commands) {
    // open the file in read mode
    // loop for 152 times 
        // read the string still new line
        // external_cmd = malloc(length of string)
        // copy the cmd from buffer to cmd array
    // store the null address at last index
    int fd = open("external_commands.txt", O_RDONLY);
    int ind = 0, i = 0;
    char file_cmd[50], ch;
    while(read(fd, &ch, 1)) {
        if(ch != '\n')
            file_cmd[i++] = ch;
        else {
            file_cmd[i] = '\0';
            external_commands[ind] = (char *) calloc(strlen(file_cmd) + 1, sizeof(char));
            strcpy(external_commands[ind], file_cmd);
            ind++;
            i = 0;
            memset(file_cmd, 0, 50);
        }
    }
    external_commands[ind] = NULL;
}