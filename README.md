# Sistema de matriculas
Un sistema de matriculas en c++.

## Instalación

Para poder compilar este proyecto deberias tener instalado 3 dependencias que son: 

1. ncurses
2. sqlite
3. boost

Si se desea comprobar que todas librerias estan instaladas, ejecute todos los comandos:

	ls /usr/include/ncurses.h
	ls /usr/include/menu.h
	ls /usr/include/sqlite3.h
	ls /usr/include/boost/format.hpp

Si todos los comandos le devolvieron datos la instalacion de las dependencias estan
completas, si no es el caso, deberia consultar en "google" como instalar las 3 
dependencias correctamente en su distribución.

## Compilación

g++ *.cc -o binary -lcurses -lmenu -lsqlite3

## Ejecución

touch data.db
sqlite3 data.db < sqlite3.sql
./binary

Todo esto deberia de hacerse en la misma carpeta del proyecto, si desea mover el binario
deberia de hacerlo junto con "data.db"

