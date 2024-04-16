#include "shell.h"

int main(int ac, char **argv)
{
	char *prompt = "$ ";
	char *line = NULL, *line_cpy = NULL;
	size_t n = 0;
	ssize_t nread;
	const char *s = " \n";
	int num_tokens = 0;
	char *token;
	int i;

	//bucle para shells prompt
	while (1)
	{
		printf("%s", prompt);
		nread = getline(&line, &n, stdin);
		//ver si fallo la getline o se entro el comando Crtl+D o EOF
		if(nread == -1)
		{
			printf("Shell out\n");
			return (-1);
		}

		//Almacenando espacio para una copia de line
		line_cpy = malloc(sizeof(char) * nread);
		if (line_cpy == NULL)
		{
			perror("ERROR memory Allocation error");
			return (-1);
		}
		//copiando el contenido de la linea original en la linea nueva
		strcpy(line_cpy, line);

		//Dividiendo la linea origianl para calcular la cantidad de tokens
		token = strtok(line, s);
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, s);
		}
		num_tokens++;

		//Almacenando espacio para la cadena de caracteres
		argv = malloc(sizeof(char *) * num_tokens);

		//Almacenando cada token en el arrya argv
		token = strtok(line_cpy, s);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, s);
		}
		argv[i] = NULL;
		printf("%s\n", line);
	
		//liberando memoria 
		free(line);
	}
	return (0);
}
