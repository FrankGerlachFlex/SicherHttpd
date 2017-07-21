#ifndef ABSCHALTER 
#define ABSCHALTER 1
#include <math.h>
#include "URLParser.h"
#include "ProzedurVerwalter.h"
#include "Nuetzlich.h"
#include "socketNuetzlich.h"
#include "feld.h"


/* Prozedur zum Abschalten des Servers */



extern bool g_signalisiereHerunterfahren;

class Abschalter: public AbstrakteProzedur
{
   
public:


   virtual bool verarbeite(const ParameterListeTyp& parameterListe,int ausgabeSocket)
   {    
       bool erfolg;
       Zeichenkette name(5,erfolg);
       Zeichenkette wert(10,erfolg);
       name = "Passwort";
       if( !parameterListe.finde(name,wert)  )
       {
           return false;
       }

       if( wert == "geheim1234")
       {
           g_signalisiereHerunterfahren = true;
       }

       return true;
       
   }

   virtual ~Abschalter()
   {
   }
};

#endif
