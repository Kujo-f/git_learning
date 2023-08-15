#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/* prompt_func prints the prompt used in the shell */
void prompt_func()
{
	write(STDOUT_FILENO, "cisfun$ ", 9);
}

/*
 * main - Entry point of the program
 */
int main()
{
	/* @command - buffer to contain user input
	 * @command_length - number of characters in user input
	 * @pid - stores value returned after forking
	 */ 
	 
	char *command = NULL;
	size_t command_length = 0;
	pid_t pid;
	int status;
	int exit_status;
	ssize_t input_chars;

	while (1)
	{
		/* calling function to display prompt */
		prompt_func();

		/* getting user input for stdin stream using getline function 
		 * getline dynamically allocates memory
		 */

		input_chars = getline(&command, &command_length, stdin);
		if (input_chars == -1) /* checking for any error which is (-1) */
		{
			if (feof(stdin)) /* checks for eof erroe in stdin  and breaks if so */
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
			else
			{
				perror("Error reading input"); /* if its any other it also breaks and frees the buffer*/
				exit(EXIT_FAILURE);
			}
		}

		/* replacing the newline character */
		command[strcspn(command, "\n")] = '\0';

		/* checks for exit command */
		if (strcmp(command, "exit") == 0)
		{
			
			break;
		}

		/* forking a process to execute the command */
		pid = fork();

		/* checks if forking returned an error */
		if (pid < 0) 
		{
			
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) /* meaning forking was successful */
		{
			/* Now running the child process */
			char **args = (char **)malloc(2 * sizeof(char *)); /* command and argument list */
			args[0] = command;
			args[1] = NULL;


			if (execvp(command, args) == -1)
			{
				perror("command not found");
				
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* the parent process */
			waitpid(pid, &status, 0); /* wait for child process to complete */

			/* checking if child process executed successfully */
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (exit_status != 0)
				{
					write(STDOUT_FILENO, "./shell: NO such file or directory\n",  35);
				}
			}
		}
	}

	free(command);

	return (0);
}
