#include "../include/csapp.h"

int main(int argc, char **argv)
{
    int c=0;
    int clientfd,puerto;
    char *host, buf[MAXLINE];
    rio_t rio;

    if (argc != 5) {
	fprintf(stderr, "Uso: %s -s <direccion_ip> -p <puerto>\n", argv[0]);
	exit(0);
    }
    host = argv[2];
    puerto= atoi(argv[4]);
    clientfd = Open_clientfd(host,puerto);
    Rio_readinitb(&rio, clientfd);
    printf("Conectado con %s en el puerto %d\n",host,puerto);
    printf("Ingrese palabras de 6 caracteres para enviar:\n");
    fflush(stdout);
  while (Fgets(buf, MAXLINE, stdin) != NULL) {
  if(strlen(buf)-1==6){
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	printf("echo:");
	Fputs(buf, stdout);
	printf("Palabra a enviar:"); fflush(stdout);
    }
    else{
      printf("La palabra no contiene 6 carácteres, ingrese nuevamente: ");
    }
  }
    Close(clientfd);
    exit(0);
}
