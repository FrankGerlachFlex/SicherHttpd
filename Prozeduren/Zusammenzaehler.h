#ifndef ZUSAMMENZAEHLER
#define ZUSAMMENZAEHLER 1
#include "URLParser.h"
#include "ProzedurVerwalter.h"
#include "Nuetzlich.h"
#include "socketNuetzlich.h"

class Zusammenzaehler: public AbstrakteProzedur
{
   
public:
   virtual bool verarbeite(const ParameterListeTyp& parameterListe,int ausgabeSocket)
   {
       bool erfolg;
       Zeichenkette name(5,erfolg);
       Zeichenkette wert(10,erfolg);
       name = "A";
       uint64_t paramA(0);
       if( !parameterListe.finde(name,wert) || !leseZahl(wert,paramA) )
       {
           return false;
       }
       name = "B";
       if( parameterListe.finde(name,wert) )
       {
           
           uint64_t paramB(0);
           if( !leseZahl(wert,paramB) )
           {
               return false;
           }
           uint64_t ergebnis = paramA+paramB; 

           bool erfolg;
           Zeichenkette antwort(100,erfolg);
           antwort.dazu("<html>\n"
                        "  <body>\n "
                        "    Das Ergebis ist: ");
           antwort.dazuZahl(ergebnis);
           antwort.dazu("</body></html>"); 
           sendeHTTPantwort(ausgabeSocket,antwort);
           return true;
       }
       return false;
   }

   virtual ~Zusammenzaehler()
   {
   }
};

#endif
