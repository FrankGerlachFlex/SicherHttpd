#include "sicherSturz.h"


void sicherSturz(const char* meldung)
{
   printf("Sicherer Sturz, Anhalten: %s\n",meldung);
   char* ptrNULL = NULL;
   ptrNULL[2] = 1;//Absturz so machen, dass GDB den Stacktrace anzeigen kann
}
