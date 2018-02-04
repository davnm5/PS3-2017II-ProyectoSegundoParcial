all: servidor cliente

servidor: src/servidor.c
	gcc -static -c src/hash.c -o obj/hash.o
	gcc -static -c src/csapp.c -o obj/csapp.o
	ar -rcs lib/libhash_ps3.a obj/hash.o
	ar -rcs lib/libayuda.a obj/csapp.o
	gcc -Wall $^ -o bin/$@ -Llib -lhash_ps3 -layuda -lpthread

cliente: src/cliente.c
	gcc -Wall $^ -o bin/$@ -Llib -layuda -lpthread

clean:
	rm -rf obj/* bin/* lib/*
