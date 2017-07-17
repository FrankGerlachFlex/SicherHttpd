#ifndef PRIMZAHLEN
#define PRIMZAHLEN 1
#include <math.h>
#include "URLParser.h"
#include "ProzedurVerwalter.h"
#include "Nuetzlich.h"
#include "socketNuetzlich.h"
#include "feld.h"


/* Beispiel einer sicherHttpd Prozedur (Zerlegen einer Zahl in die Primfaktoren) */





class Primzahlen: public AbstrakteProzedur
{
   
public:

   static void zerlegeZahl(uint64_t zahl, Feld<uint64_t>& primFaktoren)
   {
       uint64_t wurzel = sqrt(zahl);
       uint64_t probeZahl = 2;
       while( wurzel >= probeZahl )
       {
           while( (zahl % probeZahl) == 0 )
           {
               primFaktoren.push_back(probeZahl);
               zahl /= probeZahl;
               wurzel = sqrt(zahl);
           } 
           probeZahl++;
       }   
       if( zahl > 1 )
       {
         primFaktoren.push_back(zahl);
       }
   }

   virtual bool verarbeite(const ParameterListeTyp& parameterListe,int ausgabeSocket)
   {
       Feld<uint64_t> primZahlen;
        
       bool erfolg;
       Zeichenkette name(5,erfolg);
       Zeichenkette wert(10,erfolg);
       name = "A";
       uint64_t paramA(0);
       if( !parameterListe.finde(name,wert) || !leseZahl(wert,paramA) )
       {
           return false;
       }

       Feld<uint64_t> primFaktoren;
       zerlegeZahl(paramA,primFaktoren);
       
       Zeichenkette antwort(100,erfolg);
       antwort.dazu("<html>\n"
                     "  <body>\n "
                     "    Die Primfaktoren von ");
       antwort.dazuZahl(paramA);
       antwort.dazu(" sind:"); 
       for(uint64_t i=0; i < primFaktoren.size(); i++)
       {
           antwort.dazuZahl(primFaktoren[i]);
           antwort.dazu(" "); 
       }
       antwort.dazu("</body></html>"); 
       sendeHTTPantwort(ausgabeSocket,antwort);
       return true;
       
   }

   virtual ~Primzahlen()
   {
   }
};

#endif
