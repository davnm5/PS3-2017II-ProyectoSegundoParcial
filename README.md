PROYECTO SEGUNDO PARCIAL
======================

Escuela Superior Politécnica del Litoral
Version 1.0 3/02/2018

1 - Descripción
---------------
Programa cliente-servidor, que soporta múltiples conexiones,trabaja con una librería estática generada a partir de la implementación de una Tabla_Hash. El cliente envía comandos al servidor, este se encarga de procesarlos y responder a sus solicitudes, permitiendole hacer modificaciones en la tabla, dicha estructura estará respaldada por un archivo XML.


2 - Instalación
----------------
Para el funcionamiento de este programa es necesario contar con las siguientes librerias:

* Libreria Mini-XML

Descargamos la libreria desde un repositorio de github
```
git clone https://github.com/michaelrsweet/mxml
cd mxml
./configure
make install
sudo ldconfig
```
Esto agregara la libreria en los directorios lib e include, se podria usar el prefijo -lmxml para invocarla.
Para crear los ejecutables se dispone de una archivo Makefile que facilitará el trabajo.
Se encargará de crear el ejecutable del cliente y el servidor.

```
make servidor cliente
Para limpiar:
make clean
```

3 - Modo de uso general
------------------------

* Iniciar el programa servidor.

El servidor se encargará de aceptar múltiples conexiones simultaneas, de clientes, aceptará y procesará los siguientes comandos:

* GET <clave>: Devuelve al cliente un mensaje indicando si la clave existe o no
* INSERT <clave>: Inserta en la tabla hash, la clave especificada
* REMOVE <clave>: Elimina de la tabla hash, la clave especificada

Se proporcionan dos formas de ejecutar:
```
./servidor
./bin/servidor -c /ruta/archivo/configuracion.cfg
```

Además el servidor puede ser ejecutado y finalizado de las siguientes formas:

* Modo Foreground:
```
./servidor -->ejecutar
presionando CTRL+C --> finalizar
```
* Modo Background:
```
./servidor & -->ejecutar
aparecerá un id del proceso eje:
[1] 2943
Luego ejecutando kill -KILL 2943 --> finalizar
```

* Iniciar el programa cliente.

El cliente debe recibir como argumentos la dirección IP y el puerto del servidor al que se conectará.
Durante su ejecución el programa cliente aceptará por teclado lineas de comando del tipo:

* GET <clave>
* INSERT <clave>
* REMOVE <clave>

El programa cliente validará si se trata de una cadena alfanumérica de 6 caracteres, enviará al servidor el mensaje para que se ejecute el comando respectivo y esperará por la respuesta del servidor.

Forma correcta de ejecutar:

```
./bin/cliente -s 127.0.0.1 -p 1212
```
Ejemplo del envio de comandos al servidor:
--------------------------------------------
```
INSERT aaccee
GET aaccee
REMOVE aaccee

NOTA: Sólo se aceptan aquellos comandos que contengan las palabras claves <GET,INSERT,REMOVE>,acompañadas de cadenas válidas de 6 carácteres,caso contrario no sucederá nada y se seguirá esperando por un comando correcto.  
```
El programa cliente finaliza cuando se presiona CTRL+C, se pueden tener varios clientes conectados en simultáneo, esto no afectará el funcionamiento.

```
NOTA: Se creó una librería estática llamada libayuda.a que permite manejar ciertas funciones de mejor manera.
```

4 - Autores
-----------

* José David Neira Martrus
* Carlos Peñafiel
