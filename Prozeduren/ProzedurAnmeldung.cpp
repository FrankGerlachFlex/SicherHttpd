#include "ProzedurVerwalter.h"
#include "Zusammenzaehler.h"
#include "Primzahlen.h"
#include "Abschalter.h"

extern ProzedurVerwalter g_prozedurVerwalter;

void meldeProzedurenAn()
{
   Zeichenkette prozName;

   Zeichenkette host;
   host = "localhost:8000";

   Zusammenzaehler* zZaehler  = new Zusammenzaehler;
   prozName = "/rechne";
   g_prozedurVerwalter.meldeProzedurAn(host,prozName,zZaehler);

   Primzahlen* primZahlen  = new Primzahlen;
   prozName = "/primZahlen";
   g_prozedurVerwalter.meldeProzedurAn(host,prozName,primZahlen);


   Abschalter* abschalter = new Abschalter;
   prozName = "/abschalten";
   g_prozedurVerwalter.meldeProzedurAn(host,prozName,abschalter);
}
