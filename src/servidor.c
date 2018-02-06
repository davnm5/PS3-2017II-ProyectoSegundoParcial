
#include "../include/csapp.h"
#include "../include/hash.h"
#include <signal.h>

static Hasht *ht;
int port,time_table,size_table;
char* ruta;
char file_table[20];
char buf[MAXLINE];
int c=0;
void *thread(void *vargp);
void leer_configuracion(char* ruta);
char* existe(char *cadena);
void  leer_clave();
void manejador();
void guardar();

void manejador(){

printf("HASH_TABLE GUARDADA\n");
guardarHash(ht,file_table);

}

void echo(int connfd)
{
  char* cadenas;
  char* msg;
    size_t n;

    rio_t rio;

    Rio_readinitb(&rio, connfd);
while((n=Rio_readlineb(&rio,buf, MAXLINE)) != 0) {
  if(strlen(buf)==10){
  cadenas= strtok(buf,"***");
  if(strcmp(existe(cadenas),"EXISTE")==0){
  strcpy(buf,"EXISTE");
  Rio_writen(connfd,buf,n);

}
else{
  strcpy(buf,"NO");
  Rio_writen(connfd,buf,n);
}
}

if(strlen(buf)==11){
cadenas= strtok(buf,"####");
  printf("INSERT\n");
  add_ht(ht,cadenas);
}

if(strlen(buf)==12){
cadenas= strtok(buf,"$$$$$");
  printf("REMOVE\n");
  remove_ht(ht,cadenas);
}
}
}

int main(int argc, char **argv)
{
    signal(SIGUSR2,manejador);
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
    ht = new_ht(size_table);

    char s[20]="./bin/daemon ";
    char d[4];
    char f[4];
    char r[2]=" ";
    sprintf(f,"%d",getpid());
    sprintf(d,"%d",time_table);
    strcat(s,f);
    strcat(s,r);
    strcat(s,d);
    system(s);
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


char* existe(char *cadena){
void* aux= get_ht(ht,cadena);
if(aux!=NULL){
return "EXISTE";
}
return "NO";
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
