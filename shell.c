#include "shell.h"
/**
 *main - Simple creation of Shell
 *@ac: args
 *@argv: argv
 *Return: 0 if worked, error if not.
 */
int main(int ac, char **argv)
{
	char *prompt = "$ ";
	char *line = NULL; char **command = NULL;
	size_t n = 0;
	char *args[] = {line, NULL};
	ssize_t nread;
	/**bucle para shells prompt*/
	while (1)
	{
		printf("%s", prompt);
		nread = getline(&line, &n, stdin);
		if (nread == -1)
		/**ver si fallo la getline o se entro el comando Crtl+D o EOF*/
		{
			printf("Shell Out!\n");
			exit(EXIT_FAILURE);
		}
		/** Enter como nueva linea y poder utilizarlo como un ejecutor del programa*/
		line[strcspn(line, "\n")] = '\0';
		/** Realizamos fork para que un proceso hijo realice el comando deseado*/
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork Failed");
			exit(EXIT_FAILURE);
		}
		/**Comnzamos proceso hijo y ejecuta comando*/
		else if (pid == 0)
		{
			if (execve(line, args, NULL) == -1)
			{
				perror("Error executing command");
				exit(EXIT_FAILURE);
			}
		}
		waitpid(pid, NULL, 0);
		free(line);
	}
	return (0);
}
