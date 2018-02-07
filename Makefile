all: servidor cliente

servidor: src/servidor.c
	gcc -static -c src/hash.c -o obj/hash.o -lmxml
	gcc -static -c src/csapp.c -o obj/csapp.o
	ar -rcs lib/libhash_ps3.a obj/hash.o
	ar -rcs lib/libayuda.a obj/csapp.o
	gcc src/servidor.c -o bin/servidor -Llib -lhash_ps3 -layuda -lpthread -lmxml

cliente: src/cliente.c
	gcc src/cliente.c -o bin/cliente -Llib -layuda -lpthread
	gcc src/daemon.c -o bin/daemon



clean:
	rm -rf obj/* bin/* lib/*
