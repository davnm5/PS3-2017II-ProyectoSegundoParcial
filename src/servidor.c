
#include "../include/csapp.h"
#include "../include/hash.h"
#include <signal.h>
#include <mxml.h>

static Hasht *ht;
int port,time_table,size_table;
char* ruta;
char file_table[20];
char buf[MAXLINE];
void *thread(void *vargp);
void leer_configuracion(char* ruta);
char* existe(char *cadena);
void  leer_clave();
void foreground();
void background();
void guardar();

void guardar(){
printf("HASH_TABLE GUARDADA\n");  //método que se activa cada cierto tiempo o cada vez que se le envie una señal correcta
guardarHash(ht,file_table);

}


void foreground(){
guardar(); //guardamos la tabla
system("killall daemon"); //matamos al daemon cuando ya se presiona CTRL+C
system("killall servidor");//matamos al servidor
}

void background(){
char r[20]="kill -9 ";
char f[3];
sprintf(f,"%d",getpid());
guardar();//guardamos la tabla
strcat(r,f);
system("killall daemon"); //matamos al daemon
system(r); //enviamos la señal KILL al propio servidor
}



void echo(int connfd)
{
  char* cadenas;
  char* msg;
    size_t n;

    rio_t rio;

    Rio_readinitb(&rio, connfd);
while((n=Rio_readlineb(&rio,buf, MAXLINE)) != 0) {
  /*Leemos información constantemente y comprobamos que se trate de algun comando válido*/
  if(strlen(buf)==10){
  cadenas= strtok(buf,"***");
  if(strcmp(existe(cadenas),"EXISTE")==0){
  strcpy(buf,"EXISTE");    //retornamos al cliente el mensaje que existe la clave
  Rio_writen(connfd,buf,n);

}
else{
  strcpy(buf,"NO");     //retornamos NO, es decir, no existe la clave
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

    signal(SIGUSR2,guardar);// esta señal nos permite guardar la tabla cada cierto tiempo
    signal(SIGINT,foreground);// señal SIGINT en modo foreground
    signal(SIGKILL,background);//señal KILL en modo background

    int listenfd, *connfdp;
    socklen_t clientlen=sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    unsigned short client_port;
    pthread_t tid;
    if(argc==1){
    ruta="configuracion.cfg";   //si se ejecuta como ./servidor se lee un archivo ya existente de configuracion
    }

    if (argc>1 && argc<3 || argc>3) {
	fprintf(stderr, "Uso: %s -c <ruta_archivo>\n", argv[0]);
	exit(0);
    }
  if(argc==3){
    ruta=argv[2]; //se lee la ruta proporcionada
  }

    leer_configuracion(ruta); //método para leer el archivo de configuración
    printf("**INFORMACION DEL ARCHIVO DE CONFIGURACION**\n");
    printf("port: %d\n",port);
    printf("file_table: %s\n",file_table);
    printf("size_table: %d\n",size_table);
    printf("time_table: %d\n",time_table);
    printf("--------------------------------------------\n");
    FILE* xml;
    char *archivo;
    xml=fopen(strtok(file_table,"$ \r"),"r");
    /*leemos el archivo definido en la configuracion,
    si no existe se crea una nueva tabla, caso contrario se usa la existente
*/
    if(xml==NULL){
    printf("tabla_nueva\n");
    ht = new_ht(size_table);
    }

    if(xml!=NULL){
    printf("tabla_existente\n");
    ht=crear_hash_xml(file_table);// se crea una tabla hash a partir del archivo existente
   }

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
    /*
    Ejecutamos mediante el uso de system el daemon, que se encargará de llevar el conteo de segundos
    y de enviar una señal al servidor, daemon recibe: el tiempo y el id del proceso.
    */
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
/*se lee el archivo de configuración linea a linea y se asignan los valores a las variables globales definidas al inicio*/
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

/*funcion que devuelve si existe la clave en la tabla hash*/
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
