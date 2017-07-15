#include "ProzedurVerwalter.h"
#include "Zusammenzaehler.h"
#include "Primzahlen.h"

extern ProzedurVerwalter g_prozedurVerwalter;

void meldeProzedurenAn()
{
   Zeichenkette prozName;

   Zusammenzaehler* zZaehler  = new Zusammenzaehler;
   prozName = "/rechne";
   g_prozedurVerwalter.meldeProzedurAn(prozName,zZaehler);

   Primzahlen* primZahlen  = new Primzahlen;
   prozName = "/primZahlen";
   g_prozedurVerwalter.meldeProzedurAn(prozName,primZahlen);
}
