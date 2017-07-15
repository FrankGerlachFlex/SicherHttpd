#ifndef PROZEDUR_VERWALTER
#define PROZEDUR_VERWALTER

/* Modul zur Registrierung und zum Aufruf von "Prozeduren" (GET und POST Requests) innerhalb von SicherHttpd.

   (C) Frank Gerlach 2017

   Nichtkommerzielle Nutzung ist lizenz- und kostenfrei.

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.
 
   Einzelheiten bitte erfragen bei frankgerlach.tai@gmx.de

*/

#include "zk.h"
#include "Streufeld.h"
#include "HashAdapterZK.h"
#include "URLParser.h" 

 

class AbstrakteProzedur
{
   
public:
   virtual bool verarbeite(const ParameterListeTyp& parameter,int ausgabeSocket) = 0;

   virtual ~AbstrakteProzedur()
   {}
};

template<class TypZeiger>
class WertAdapterAbstr
{
public:
    
   static void loesche(TypZeiger*& schluessel )
   {
      schluessel = NULL;
   }

  static void loescheEndgueltig(TypZeiger*& schluessel)
  {
      delete schluessel;
      schluessel = NULL;
  }
};


class ProzedurVerwalter
{
   bool m_erfolg;
   Streufeld<Zeichenkette,AbstrakteProzedur*,SchlAdapterZK,WertAdapterAbstr<AbstrakteProzedur> > m_prozeduren;

public:
   ProzedurVerwalter():m_erfolg(false),m_prozeduren(3,m_erfolg)
   {
      if(!m_erfolg)
      {
         sicherSturz("kein Speicher in ProzedurVerwalter::ProzedurVerwalter()");
      }
   }

   void meldeProzedurAn(const Zeichenkette& name,AbstrakteProzedur* prozedur);

   bool fuehreAus(const Zeichenkette& prozedurName,const SFzkzk& parameter,int ausgabeSocket);
};

#endif
