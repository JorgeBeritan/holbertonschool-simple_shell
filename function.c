#include "main.h"
/**
 *get_envidia - get the environment especified with name
 *@name: name of the env we want
 *Return: env after the = sign if found, else NULL
 */
char *get_envidia(const char *name)
{
	int namelen = strlen(name);
	char **env;
	int same_name;
	char same_sign;

	for (env = environ; *env != NULL; env++)
	{
/**Comparamos los caracteres de 'name' con los primeros caracteres de '*env'*/
		same_name = strncmp(name, *env, namelen) == 0;
/**Verificamos si el carácter justo despes es un signo de igua "="*/
		same_sign = (*env)[namelen] == '=';
/**Verificamos si ambas condiciones son verdaderas*/
		if (same_name && same_sign)
		{
			return (*env + namelen + 1); /** Devuelve el valor después del"" */
		}
	}

	return (NULL); /**Si no se encuentra la variable, devuelve NULL*/
}
/**
 *command_path - obtiene la ruta completa de un comando ejecutable en el sistem
 *@cmd: El nombre del comando que se desea buscar en el PATH
 *Return: ruta completa del comando, NUll si no encuentra PATH o no ejecutable
 */
char *command_path(char *cmd)
{
	int i = 0;
	char *path, *token;
	char *path_array[100];
	char *new_path = NULL;
	struct stat st;

	/**obtenemos el PATH de las variables de entorno*/
	path = strdup(get_envidia("PATH"));
/**tokenizamos path para separar todos los pathing*/
	token = strtok(path, ":");
	/**Asociamos memoria dinamica para un nuevo path*/
	new_path = malloc(sizeof(char) * 100);
	if (get_envidia("PATH")[0] == ':')
		if (stat(cmd, &st) == 0)/**checkeamos si existe*/
			return (strdup(cmd));
	while (token != NULL)/**Tokenizacion*/
	{
		path_array[i] = token;
		i++;
		token = strtok(NULL, ":");
	}
	path_array[i] = NULL;
	/**Procesamos new_path para que sea una string con el comando en si*/
	for (i = 0; path_array[i]; i++)
	{
		sprintf(new_path, "%s/%s", path_array[i], cmd);
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
/**
 *command_read - tokenize line, get solution for exit and env, execute comm
 *@line: user input
 *@nread: n of bytes
 *Return: The executable of the function given
 */
int command_read(char *line, size_t nread)
{
	char *token = NULL;
	char *cmd_arr[100];
	int i = 0;
	(void)nread;

	/**Analizamos el caso de exit y su solucion*/
	if (strcmp(line, "exit") == 0)
	{
		printf("OK");
		return (1);
	}
	/**analizamos el caso de env y su solucion*/
	if (strcmp(line, "env") == 0)
		return (_printenv());
	/**Arreglar tema de los espacios*/
	while (*line && *line == ' ')
	line++;
	/**tokenizamos el comando que se nos pasa con el delimitador " "*/
	token = strtok(line, " ");
	while (token)
	{
		cmd_arr[i++] = token;
		token = strtok(NULL, " ");
	}
	cmd_arr[i] = NULL;
	return (execute(cmd_arr));
}
/**
 *execute - execute the command given on a child process with the path
 *@cmd_arr: chain of tokens that will be executed
 *Return: handlle errors wit -1 and 1, runs command and exit
 */
int execute(char *cmd_arr[])
{
	char *exe_path = NULL, *cmd = NULL;
	pid_t pid;
	int status, exit1 = 0;
	char *name = NULL;

	cmd = cmd_arr[0];
	exe_path = command_path(cmd);
	/**en el caso de no encontrar el comando se manipula el error*/
	if (exe_path == NULL)
	{
		printf("\033[5;1;35m%s %s: not found\n\033[0m", name, cmd);
		exit1 = WEXITSTATUS(status);
		return (exit1);
	}
	/**Creacion y ejecucion de proceso hijo y padre*/
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
			exit(1);
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
/**
 *_printenv - prints environment
 * Return: 0 if succes
 */
int _printenv(void)
{
	char **env_ptr = environ;
	int i = 0;

	while (env_ptr[i] != NULL)
	{
		printf("%s\n", env_ptr[i]);
		i++;
	}
	return (0);
}
