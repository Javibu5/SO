/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "arrays.h"


void
arrays_1(char *host)  
{
	CLIENT *clnt;
	respuesta_notas  *result_1;
	indices_notas  obtener_notas_1_arg;
	int i;

#ifndef	DEBUG
	clnt = clnt_create (host, ARRAYS, ARRAYS_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	
	obtener_notas_1_arg.indices.indices_len = MAXIMO;
	obtener_notas_1_arg.indices.indices_val =  malloc(sizeof(float)*MAXIMO);

	for(i=0;i<MAXIMO;i++)
	{
		obtener_notas_1_arg.indices.indices_val[i] = i;
	}
	result_1 = obtener_notas_1(&obtener_notas_1_arg, clnt);
	if (result_1 == (respuesta_notas *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else {
	  fprintf(stderr, "------ Desde el Cliente -------\n");
      for(i=0;i<MAXIMO;i++)
		printf("vector[%d] = %f\n", i, result_1->notas.notas_val[i]);
    }

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	arrays_1 (host);
exit (0);
}