# Sistema de matriculas
Un sistema de matriculas en c++.

## Instalación

Para poder compilar este proyecto deberias tener instalado 3 dependencias que son: 

1. ncurses
2. sqlite
3. boost

Si se desea comprobar que todas librerias estan instaladas:

	ls /usr/include/ncurses.h
	ls /usr/include/menu.h
	ls /usr/include/sqlite3.h
	ls /usr/include/boost/format.hpp

## Compilación

g++ *.cc -o binary -lcurses -lmenu -lsqlite3

## Ejecución


