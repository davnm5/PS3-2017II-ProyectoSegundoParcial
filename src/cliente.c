#include "../include/csapp.h"

void upper_case(char *s);
void enviar_mensaje();
void  comparar();
void validar();
int clientfd;
char buf[MAXLINE];
char* cadenas;
rio_t rio;
int main(int argc, char **argv)
{
    int c=0;
    int puerto;
    char *host, buf[MAXLINE],comandos[15];

    if (argc != 5) {
	fprintf(stderr, "Uso: %s -s <direccion_ip> -p <puerto>\n", argv[0]);
	exit(0);
    }
    host = argv[2];
    puerto= atoi(argv[4]);
    clientfd = Open_clientfd(host,puerto);
    Rio_readinitb(&rio, clientfd);
    printf("Conectado con %s en el puerto %d\n",host,puerto);
    printf("Ingrese un comando válido junto a su clave:  \n |GET <clave>,INSERT <clave>,REMOVE <clave>|\n\n");
    enviar_mensaje();
    Close(clientfd);
    exit(0);
}


void enviar_mensaje(){
    while (Fgets(buf, MAXLINE, stdin) != NULL) {
    upper_case(buf);
    comparar();
    }

}

void comparar(){

  cadenas= strtok(buf," ");
    while(cadenas != NULL ) {

         if(strcmp(cadenas,"GET")==0){
        printf("SOLICITUD : %s\n",buf);
         strcpy(cadenas,"***");
         validar();
       }
       if(strcmp(cadenas,"INSERT")==0){
      printf("SOLICITUD : %s\n",buf);
       strcpy(cadenas,"####");
       validar();
     }
     if(strcmp(cadenas,"REMOVE")==0){
     printf("SOLICITUD : %s\n",buf);
     strcpy(cadenas,"$$$$$");
     validar();
   }
cadenas = strtok(NULL," ");
}

return 0;
}


void validar(){
  cadenas = strtok(NULL," ");
  int size=strlen(cadenas)-1;
  if(size==6){
   strcat(buf,cadenas);
   Rio_writen(clientfd,buf,strlen(buf));
   if(strlen(buf)==10){
   Rio_readlineb(&rio,buf,MAXLINE);
   Fputs(buf,stdout);
   printf("\n");
      }
    }
else{
  printf("La palabra no contiene 6 carácteres, ingrese nuevamente: \n");
}
}



void upper_case(char *s)
{
  while (*s) {
    *s = toupper(*s);
    s++;
  }
}
