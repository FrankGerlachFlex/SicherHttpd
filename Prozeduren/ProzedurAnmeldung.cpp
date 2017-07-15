#include "ProzedurVerwalter.h"
#include "Zusammenzaehler.h"

extern ProzedurVerwalter g_prozedurVerwalter;

void meldeProzedurenAn()
{
   Zusammenzaehler* zZaehler  = new Zusammenzaehler;
   Zeichenkette prozName;
   prozName = "/rechne";
   g_prozedurVerwalter.meldeProzedurAn(prozName,zZaehler);
}
