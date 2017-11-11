#include "sicherSturz.h"
#include "stdio.h"


/* Führe einen sicher debuggbaren Zustand des Prozesses herbei.
   Sollte gerufen werden wenn

   + kein Speicher mehr vorhanden
   + essentielle Dateien nicht geoeffnet werden koennen
   + keine Handles mehr verfuegbar sind
   + vergleichbare Ausnahemzustaende

 */
void sicherSturz(const char* meldung)
{
   printf("Sicherer Sturz, Anhalten: %s\n",meldung);
   char* ptrNULL = NULL;
   ptrNULL[2] = 1;//Absturz so machen, dass GDB den Stacktrace anzeigen kann
}


/* Stelle Bedingung sicher und beende das Programm in FALSCH-Fall 
  
   stelle soll die versuchte Operation/Bedingung menschenlesbar ausdrücken
*/
void wahrOderSturz(bool bedingung,const char* stelle)
{
   if( !bedingung )
   {
     sicherSturz(stelle);
   }  
}
