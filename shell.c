#include "main.h"
/**
 *main - actua como una shell interactiva
 *@ac: num de argumentos
 *@av: cadena caracteres que contiene los argumentos de la línea de comando
 *Return: estado de salida de la shell
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t nread = 0;
	int status = 0;
	int exitst = 0;
	(void)ac;
	(void)av;

	/**bucle de shell*/
	while (1)
	{
/**determinamos si el flujo de archivo es en una terminal interactica*/
		if (isatty(STDIN_FILENO) == 1)
/**si se cumple mostramos en pantalla BEKA$*/
			printf("\033[5;1;35mBEKA$\033[0m ");
		nread = getline(&line, &n, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}
/**Asociamos la entrada de salto de linea como si fuera el caracter nulo*/
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
/**Si es caracter Nulo que continue en ejecucion*/
		if (*line == '\0')
			continue;
/**Llammada a la funcion para ver si es un comando*/
		if (command_read(line, nread) == 2)
			break;
	}

	free(line);
	line = NULL;

	exitst = WEXITSTATUS(status);

	return (exitst);
}
