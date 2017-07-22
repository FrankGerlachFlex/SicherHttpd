#include <iostream>
#include "ProzedurVerwalter.h"

using namespace std;

void ProzedurVerwalter::meldeProzedurAn(const Zeichenkette& host, const Zeichenkette& prozedurName,AbstrakteProzedur* prozedur)
{
   Zeichenkette kanonischerName;

   kanonischerName.dazu(host);
   kanonischerName.dazu("__");
   kanonischerName.dazu(prozedurName);

   AbstrakteProzedur* gefundenProz(NULL);
   if( m_prozeduren.finde(kanonischerName,gefundenProz) )
   {
      sicherSturz("Prozedur mit diesem Namen schon registriert");
   }
   if( !m_prozeduren.trageEin(kanonischerName,prozedur) )
   {
      sicherSturz("kann Prozedur nicht registrieren");
   }
}


bool ProzedurVerwalter::fuehreAus(const Zeichenkette& host,
                                  const Zeichenkette& prozedurName,
                                  const ParameterListeTyp& parameterListe,
                                  int ausgabeSocket)
{
   Zeichenkette kanonischerName;

   kanonischerName.dazu(host);
   kanonischerName.dazu("__");
   kanonischerName.dazu(prozedurName);

   AbstrakteProzedur* gefundenProz(NULL);
   if( !m_prozeduren.finde(kanonischerName,gefundenProz) )
   {
      Zeichenkette pn,h;
      pn = prozedurName;
      h = host;
      cout << "Prozedur " << pn.zkNT() << " host:" << h.zkNT() << " existiert nicht" << endl;
      return false;
   }
   return gefundenProz->verarbeite(parameterListe,ausgabeSocket);
}
