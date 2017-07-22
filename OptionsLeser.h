#ifndef OPTIONSLEDER
#define OPTIONSLEDER

#include <iostream>
#include "OptionsLeser.h"
#include "DateiLeser.h"
#include "HashAdapterZK.h"

using namespace std;

/* Klasse zum Einlesen von Server-Optionen aus einer einfachen Konfigurationsdatei
   der Struktur
   KONFDATEI ::= (SCHLUESSEL ':' WERT \n) +
   SCHLUESSEL ::= [A-Z]+
   WERT ::= [A-Z0-9\_\-]+

*/
class OptionsLeser
{
   Dateileser   m_dateiLeser;
   SFzkzk       m_optionen;
   bool         m_erfolg;
public:
   OptionsLeser(const Zeichenkette& pfad):m_dateiLeser(pfad),m_optionen(5,m_erfolg)
   {}

   bool parseZeile(const Zeichenkette& zeile, Zeichenkette& name, Zeichenkette& wert)
   {
       if( zeile.laenge() > 1000)
       {
          return false;
       }
       name = "";
       wert = "";
       uint16_t stelle(0);
       char zeichen = 0;
       while( stelle < zeile.laenge() )
       {
           zeichen = zeile[stelle++];
           if(istBst(zeichen))
           {
               name.dazu(zeichen);
           }
           else break;
       }
       //cout << "name: " << name.zkNT() << endl;
       if( !(name.laenge() > 0 ) && (zeichen == ':') )
       {
          return false;
       }
       while( stelle < zeile.laenge() )
       {
           zeichen = zeile[stelle++];
           if(istKopfzeilenWertZeichen(zeichen))
           {
               wert.dazu(zeichen);
           }
           else break;
       }
       //cout << "wert: " << wert.zkNT() << endl;
       return wert.laenge() > 0 ;
   }

   bool leseDateiEin()
   {
       if( !m_dateiLeser.oeffne() )
       {
          return false;
       }
       Zeichenkette zeile;
       Zeichenkette name;
       Zeichenkette wert;
       while(m_dateiLeser.leseZeile(zeile))
       {
          if( parseZeile(zeile,name, wert) )
          {
              m_optionen.trageEin(name,wert);
          }
       }
       return true;
   }

   bool leseOption(const Zeichenkette& name,Zeichenkette& wert)
   {
      return m_optionen.finde(name,wert);
   }
};


#endif
