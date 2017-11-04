## Lösung Woche 1
1. Bibliotheken: '/usr/lib', '/lib'; Header-Dateien: '/usr/include'
2. 
	LIBRARY_PATH
	CPATH
	C_INCLUDE_PATH
	CPLUS_INCLUDE_PATH
	OBJC_INCLUDE_PATH
	
3. 
	-I : Include Path für userspezifische Header-Dateien
	-L : Library Path für userspezifische Bibliotheken
	-l : includiert eine userspezifische Bibliothek
	
4. 
	#include <header.h> : Preprocessor sucht nach Header-Dateien in Kombilerabhängigen Pfaden
	#include "header.h" : Sucht nach Header-Dateien im selben Verzeichnis wie die Datei die den Header einbinden will