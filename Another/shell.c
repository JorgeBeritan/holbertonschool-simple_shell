#include "main.h"

int main(int ac, char **av)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t nread = 0;
	int status = 0;
	int exitst = 0;

	//bucle de shell 	
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)//determinamos si el flujo de archivo es en una terminal interactica
			printf("BEKA$ ");//si se cumple mostramos en pantalla BEKA$
		nread = getline(&line, &n, stdin);
		if(nread == -1)
		{
			if(isatty(STDIN_FILENO) == 1)
				printf("\n");
			break;
		}
		//Asociamos la entrada de salto de linea como si fuera el caracter nulo 
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		//Si es caracter Nulo que continue en ejecucion
		if (*line == '\0')
			continue;
		//llammada a la funcion para ver si es un comando
		if (command_read(line, nread) == 2)
			break;
	}

	free(line);
	line = NULL;

	exitst = WEXITSTATUS(status);

	return (exitst);
}
