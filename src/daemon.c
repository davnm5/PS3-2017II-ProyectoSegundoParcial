#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <mntent.h>
#include<string.h>
int i=0;
int tiempo;
FILE *archivo;
pid_t id_servidor;
void contador(){

    kill(id_servidor,SIGUSR2);

}

int main(int argc, char **argv) {

	pid_t id, sesion;
  id_servidor=atoi(argv[1]);
  tiempo=atoi(argv[2]);
	id = fork();
	if (id < 0) {
		return -1;
	}
	if (id > 0) {
		return -1;
	}

	umask(0);
  signal(SIGALRM,contador);

	sesion= setsid();

	if (sesion < 0) {
		perror("ERROR");

	}


	while (1) {
    alarm(tiempo);
    pause();
	}
	return -1;
}
