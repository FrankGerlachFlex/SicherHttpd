#include <assert.h>
#include "OptionsLeser.h"


int main(int argc, char** argv)
{
   Zeichenkette dateiname;
   dateiname = "./beispielEinstellungen.txt";
   OptionsLeser ol(dateiname);
   Zeichenkette name,wert;
   name = "ListenPort";
   assert(ol.leseDateiEin() && ol.leseOption(name,wert));
   assert( wert == "800" );
   name = "htdocsWurzelVerzeichnis";
   assert(ol.leseOption(name,wert) && wert == "/home/buero/htdocs");

   cout << "Unit Test erfolgreich" << endl;
}
