#ifndef URLPARSER
#define URLPARSER

/* Effizienter und sicherer URL Parser

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include "zk.h"

/* sicherer URL Parser */
class URLParser
{
   Zeichenkette m_eingabe;
   uint32_t m_ausgabeStelle;

   char m_aktuellesZeichen; 
   bool m_hatZeichen;

   void holeZeichen();

   bool istGrossBst(char z);


   bool istBst(char z);
   bool istWertZeichen(char z);


   bool leseWortGB(Zeichenkette& wort);

   bool leseWort(Zeichenkette& wort);

   //lese zB. "index.html" oder "antwort.txt.alt"
   bool leseWortMitPunkten(Zeichenkette& wort);

   bool leseParamWert(Zeichenkette& wort);

   bool parseProzedurParameter();


 
public:
    URLParser(const char* testURL);

    bool parseURL();

    
};
    

#endif
