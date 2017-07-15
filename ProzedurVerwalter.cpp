#include <iostream>
#include "ProzedurVerwalter.h"

using namespace std;

void ProzedurVerwalter::meldeProzedurAn(const Zeichenkette& name,AbstrakteProzedur* prozedur)
{
   AbstrakteProzedur* gefundenProz(NULL);
   if( m_prozeduren.finde(name,gefundenProz) )
   {
      sicherSturz("Prozedur mit diesem Namen schon registriert");
   }
   if( !m_prozeduren.trageEin(name,prozedur) )
   {
      sicherSturz("kann Prozedur nicht registrieren");
   }
}


bool ProzedurVerwalter::fuehreAus(const Zeichenkette& prozedurName,
                                  const ParameterListeTyp& parameterListe,
                                  int ausgabeSocket)
{
   AbstrakteProzedur* gefundenProz(NULL);
   if( !m_prozeduren.finde(prozedurName,gefundenProz) )
   {
      cout << "Prozedur mit diesem Namen existiert nicht" << endl;
      return false;
   }
   return gefundenProz->verarbeite(parameterListe,ausgabeSocket);
}
