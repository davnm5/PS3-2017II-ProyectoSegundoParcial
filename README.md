PROYECTO SEGUNDO PARCIAL
======================

Escuela Superior Politécnica del Litoral
Version 1.0 3/02/2018

1 - Descripción
---------------




2 - Instalación
----------------
Para el funcionamiento de este programa es necesario contar con las siguientes librerias:

* Libreria Mini-XML

DESCARGAMOS EL REPOSITORIO desde github
git clone https://github.com/michaelrsweet/mxml
...

cd mxml
...

./configure
...

make
...
make install //Esto agregara la libreria en los directorios lib e include, se podria usar el prefijo -lmxml para invocarla.

...
sudo apt-get install
```

Para crear los ejecutables se dispone de una archivo Makefile que facilitará el trabajo.
Se encargará de crear el ejecutable del cliente y el servidor.

```
make servidor cliente
```

3 - Modo de uso general
------------------------

* Iniciar el programa servidor.

El servidor se encargará de aceptar múltiples conexiones simultaneas de clientes, aceptará y procesará los siguientes comandos:

* GET <clave>: Devuelve al cliente un mensaje indicando si la clave existe o no
* INSERT <clave>: Inserta en la tabla hash, la clave especificada
* REMOVE <clave>: Elimina de la tabla hash, la clave especificada

```
./servidor
./bin/servidor -c /ruta/archivo/configuracion.cfg
```

* Iniciar el programa cliente.

El cliente debe recibir como argumentos la dirección IP y el puerto del servidor al que se conectará.
Durante su ejecución el programa cliente aceptará por teclado lineas de comando del tipo:

* GET <clave>
* INSERT <clave>
* REMOVE <clave>

El programa cliente validará si se trata de una cadena alfanumérica de 6 caracteres, enviará al servidor el mensaje para que se ejecute el comando respectivo y esperará por la respuesta del servidor.

```
./bin/cliente -s 192.168.1.1 -p 1212
```


4 - Autores
-----------

* José David Neira Martrus
* Carlos Peñafiel
