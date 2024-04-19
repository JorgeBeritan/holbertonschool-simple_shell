#include "main.h"

char *command_path(char *cmd)
{
	int i = 0;
	char *path, *token;
	char *path_array[100];
	char *new_path = NULL;
	struct stat st;

	//obtenemos el PATH de las variables de entorno
	path = strdup(getenv("PATH"));
	//tokenizamos path para separar todos los pathing indicando el delimitador ":"
	token = strtok(path, ":");
	//Asociamos memoria dinamica para un nuevo path
	new_path = malloc(sizeof(char) * 100);
	if (getenv("PATH")[0] == ':')
		if (stat(cmd, &st) == 0)//checkeamos si existe
			return (strdup(cmd));
	while (token != NULL)//Tokenizacion
	{
		path_array[i] = token;
		i++;
		token = strtok(NULL, ":");
	}
	path_array[i] = NULL;
	//Procesamos new_path para que sea una string conn el comando en si 
	for (i = 0; path_array[i]; i++)
	{
		strcpy(new_path, path_array[i]);
		strcat(new_path, "/");
		strcat(new_path, cmd);
		strcat(new_path, "\0");
		if (stat(new_path, &st) == 0)
		{
			free(path);
			return (new_path);
		}
		else
			new_path[0] = 0;
	}
	free(path);
	free(new_path);

	if (stat(cmd, &st) == 0)
		return (strdup(cmd));
	return (NULL);
}

int command_read(char *line, size_t nread)
{
	char *token = NULL;
	char *cmd_arr[100];
	int i = 0;

	//Analizamos el caso de exit y su solucion
	if (strcmp(line, "exit") == 0)
	{
		printf("Shell OUT\n");
		return (2);
	}
	//analizamos el caso de env y su solucion
	if (strcmp(line, "env") == 0)
		return (_printenv());
	//Arreglar tema de los espacios
	if (line[0] == 32)
	{
		line = NULL;
		return (1);
	}
	//tokenizamos el comando que se nos pasa con el delimitador " "
	token = strtok(line, " ");

	while (token)
	{
		cmd_arr[i++] = token;
		token = strtok(NULL, " ");
	}
	cmd_arr[i] = NULL;
	return (execute(cmd_arr));
}

int execute(char *cmd_arr[])
{
	char *exe_path = NULL;
	char *cmd = NULL;
	pid_t pid;
	int status;
	int exit1 = 0;
	char name;

	cmd = cmd_arr[0];
	exe_path = command_path(cmd);
	//en el caso de no encontrar el comando se manipula el error
	if (exe_path == NULL)
	{
		printf("%s %s: not found", name, cmd);
		exit1 = WEXITSTATUS(status);

		return (exit1);
	}
	//Creacion y ejecucion de proceso hijo y padre
	pid = fork();
	if (pid < 0)
	{
		perror("Error:");
		return (-1);
	}
	else if (pid == 0)
	{
		if (environ)
		{
			(execve(exe_path, cmd_arr, environ));
			perror("Error:");
			exit (1);
		}
		else
		{
			execve(exe_path, cmd_arr, NULL);
		}
	}
	else
	{
		wait(&status);
	}
	free(exe_path);
	return (0);
}

int _printenv(void) {
    char **env_ptr = environ;
    int i = 0;

    while (env_ptr[i] != NULL) {
        printf("%s\n", env_ptr[i]);
        i++;
    }

    return (0);
}
