#include <iostream.h>
#include <fstream.h>

#include "OptionsLeser.h"

/* Klasse zum Einlesen von Server-Optionen aus einer einfachen Konfigurationsdatei
   der Struktur
   KONFDATEI ::= (SCHLUESSEL ':' WERT \n) +
   SCHLUESSEL ::= [A-Z]+
   WERT ::= [A-Z0-9\_\-]+

*/
class OptionsLeser
{
   Zeichenkette m_pfad;
public:
   OptionsLeser(const Zeichenkette& pfad)
   {
      m_pfad = pfad;
   }

ifstream infile("mydata.txt",ios::in);

};
