#include "main.h"
char *external_commands[153];
char *argv[50];
pid_t pid;
int status;
int main()
{
    // Clear the terminal.
    system("clear");                                       
    char prompt_str[20] = "Minishell$";          // declare prompt string
    char input_str[50];                         // declare input string
    scan_input(prompt_str, input_str);          // fun ction call for getting and validating input string
    return 0;
}
