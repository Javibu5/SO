/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "holamundo.h"

void holamundo_1(char *host, char *nombre)
{
	CLIENT *clnt;
	char * *result_1;
	char * hola_1_arg;

	clnt = clnt_create (host, HOLAMUNDO, HOLAMUNDO_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	
	result_1 = hola_1(&nombre, clnt);
	if (result_1 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else printf("Mensaje recibido del servidor: %s\n", *result_1);

	clnt_destroy (clnt);

}


int main (int argc, char *argv[])
{
	char *host, *nombre;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	nombre = argv[2];
	holamundo_1 (host, nombre);
exit (0);
}