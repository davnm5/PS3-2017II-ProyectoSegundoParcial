
#include "../include/csapp.h"
#include "../include/hash.h"


int port,time_table,size_table;
char* ruta;
char* file_table;


void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n=Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
  printf("%s",buf);
	Rio_writen(connfd,buf,n);
    }
}

void *thread(void *vargp);
void leer_configuracion(char* ruta);

int main(int argc, char **argv)
{
    int listenfd, *connfdp;
    socklen_t clientlen=sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    unsigned short client_port;
    pthread_t tid;
    if (argc != 3) {
	fprintf(stderr, "Uso: %s -c <ruta_archivo>\n", argv[0]);
	exit(0);
    }

    ruta=argv[2];

    leer_configuracion(ruta);
    printf("**INFORMACION DEL ARCHIVO DE CONFIGURACION**\n");
    printf("port: %d\n",port);
    printf("file_table: %s\n",file_table);
    printf("size_table: %d\n",size_table);
    printf("time_table: %d\n",time_table);
    printf("--------------------------------------------\n");
    listenfd = Open_listenfd(port);

    while (1) {
	connfdp = Malloc(sizeof(int));
	*connfdp = Accept(listenfd, (SA *) &clientaddr, &clientlen);

	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
			   sizeof(clientaddr.sin_addr.s_addr), AF_INET);

	haddrp = inet_ntoa(clientaddr.sin_addr);
	printf("Conectado con %s (%s)\n",haddrp,hp->h_name);
	Pthread_create(&tid, NULL, thread, connfdp);
    }
}


void leer_configuracion(char* ruta){
FILE *archivo;
char buffer[100];
char *cadenas;

archivo=Fopen(ruta,"r");
while (Fgets(buffer,100,archivo)!=NULL){
cadenas= strtok(buffer,"=\n");
    while(cadenas != NULL ) {
       if(strcmp(cadenas,"port")==0){
       cadenas = strtok(NULL,"=\n");
       port=atoi(cadenas);
    }

    if(strcmp(cadenas,"file_table")==0){
    cadenas = strtok(NULL,"=\n");
    file_table=(char*)malloc(strlen(cadenas));
    strcpy(file_table,cadenas);
    }

    if(strcmp(cadenas,"time_table")==0){
    cadenas = strtok(NULL,"=\n");
    time_table=atoi(cadenas);
 }

 if(strcmp(cadenas,"size_table")==0){
 cadenas = strtok(NULL,"=\n");
 size_table=atoi(cadenas);
}


    cadenas = strtok(NULL,"=\n");

}
}
}




void *thread(void *vargp)
{
    int connfd = *((int *)vargp);
    Pthread_detach(pthread_self());
    Free(vargp);
    echo(connfd);
    Close(connfd);
    return NULL;
}