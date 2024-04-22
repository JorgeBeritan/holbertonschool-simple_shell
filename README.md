# Shell Interactiva en C

Este repositorio contiene una implementación básica de una shell interactiva en el lenguaje C. La shell proporcionuna interfaz de línea de comandos simple donde puedes ejecutar comandos del sistema operativo.

## Contenido del Repositorio

El repositorio está orgnizado de la siguiente manera:

- `shell.c`: Contiene el códgo fuente principal de la shell.
- `functions.c`: Contiene las funciones auxiliares utilizadas por la shell.
- `main.h`: Encabezado que declara las funciones utilizadas en los archivos fuente.
- `README.md`: Este archivo que proporciona información sobre el repositorio.

## Funcionalidades Principales

La shell implementa las siguientes funcionalidades:

- Interfaz de línea de comandos interactiva.
- Ejecución de comandos del sistema operativo.
- Soporte para los comandos `exit` y `env`.
- Búsqueda y ejecucióde comandos en la ruta del sistema (`PATH`).

## Funciones Utilizadas

Las principales funciones utilizadas en los archivos fuente son:

- `get_envidia`: Obtiene el valor de una variable de entorno especifica.
- `command_path`: Obtiene la ruta completa de un comando ejecutable en el sistema.
- `command_read`: Tokeniza la entrada del usuario y ejecuta comandos específicos.
- `execute`: Ejecuta un comando dado en un proceso hijo.
- `_printenv`: Imprime las variables de entorno actuales.

## Uso

Para compilar la shell, puedes utilizar un compilador de C compatible, por ejemplo:

gcc shell.c functions.c main.h -o ./shell

Una vez compilada, puedes ejecutar la shell simplemente escribiendo:
./shell

De esta manera accederemos a nuestra shell lista para usar.

