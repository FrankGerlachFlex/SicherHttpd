/* Effizienter und sicherer URL Parser

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include <iostream>
#include "URLParser.h"

using namespace std;
 
#ifdef URLPARSER_UNITTEST
void URLParser::holeZeichen()
{
   if( m_ausgabeStelle < m_eingabe.laenge() )
   {
       m_aktuellesZeichen = m_eingabe[m_ausgabeStelle++];
       m_hatZeichen = true;
       
   }
   else
   {
      m_hatZeichen = false;
   }
}
#else 

void URLParser::holeZeichen()
{  
    bool erfolg;
    m_aktuellesZeichen = m_lesePuffer->leseZeichen(erfolg);
    m_hatZeichen = erfolg; 
}
#endif

bool URLParser::istGrossBst(char z)
{
   switch(z)
   {
      
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      return true;
      default: return false;
   }
   return false;
}
bool URLParser::istBst(char z)
{
   switch(z)
   {
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      return true;
      default: return false;
   }
   return false;
}


bool URLParser::istWertZeichen(char z)
{
   switch(z)
   {
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': return true;
      default: return false;
   }
   return false;
}




bool URLParser::leseWortGB(Zeichenkette& wort)
{
   while( m_hatZeichen && istGrossBst(m_aktuellesZeichen) )
   {
       wort.dazu(m_aktuellesZeichen);
       holeZeichen();
   } 
   return wort.laenge() > 0;
}

bool URLParser::leseWort(Zeichenkette& wort)
{
   while( m_hatZeichen && istBst(m_aktuellesZeichen) )
   {
       wort.dazu(m_aktuellesZeichen);
       holeZeichen();
   } 
   return wort.laenge() > 0;
}

bool URLParser::leseParamWert(Zeichenkette& wort)
{
   while( m_hatZeichen && istWertZeichen(m_aktuellesZeichen) )
   {
       wort.dazu(m_aktuellesZeichen);
       holeZeichen();
   } 
   return true;
}

//lese zB. "index.html" oder "antwort.txt.alt"
bool URLParser::leseWortMitPunkten(Zeichenkette& wort)
{
   while( m_hatZeichen && istBst(m_aktuellesZeichen) )
   {
       wort.dazu(m_aktuellesZeichen);
       holeZeichen();
       if( m_hatZeichen && (m_aktuellesZeichen == '.') )
       {
          wort.dazu(m_aktuellesZeichen);
          holeZeichen();
          if( !(m_hatZeichen && istBst(m_aktuellesZeichen)) )
          {
              return false;
          }             
       }
   }
   return wort.laenge() > 0;
}

 

bool URLParser::parseProzedurParameter(ParameterListeTyp& parameterListe)
{
   bool erfolg;
   Zeichenkette paramName(20,erfolg);
   if( !erfolg )
   {
      return false;
   }
   Zeichenkette paramWert(20,erfolg);
   if( !erfolg )
   {
      return false;
   }
   while( m_hatZeichen && (m_aktuellesZeichen != ' ') )
   {
       if(!leseWort(paramName))
       {
          return false;
       }
       if( m_hatZeichen && (m_aktuellesZeichen == '=') )
       {
          holeZeichen();
          if(!leseParamWert(paramWert))
          {
             return false;
          }
       }
       //cout << "PARAM " << paramName.zkNT() << " " << paramWert.zkNT() << endl;
       if( !parameterListe.trageEin(paramName,paramWert) )
       {
          return false;
       }
       paramName.leere();
       paramWert.leere();
       if( m_hatZeichen && (m_aktuellesZeichen == '&') )
       {
          holeZeichen();
       }
   }
   return true;
}

/* parse die erste HTTP Zeile. Im Falle einer Dateianforderung ist urlPfad gefuellt. 
                               Im Falle eines Prozeduraufrufs ist prozedurName sowie parameterListe gefuellt.
*/
bool URLParser::parseURL( Zeichenkette& method, 
                          bool& istProzedur,
                          Zeichenkette& urlPfad, 
                          Zeichenkette& prozedurName,
                          ParameterListeTyp& parameterListe)
{
    urlPfad = "";

    holeZeichen();
    
    method.leere();
    leseWortGB(method);

    istProzedur = false;

    if( !(method == "GET") )
    {
       return false;
    }
    method = "GET";
    if( m_hatZeichen &&  (m_aktuellesZeichen == ' ') )
    {
        holeZeichen();
    }
    else return false;

    if( m_hatZeichen &&  (m_aktuellesZeichen == '/') )
    {
        urlPfad.dazu('/');
        holeZeichen();
    }
    else return false;

    bool erfolg;
    Zeichenkette pfadAnteil(20,erfolg);
    if(!erfolg) return false;

    uint anzahlPfadAnteile(0);
    while( m_hatZeichen &&  (m_aktuellesZeichen != ' ') && (m_aktuellesZeichen != '?'))
    { 
       pfadAnteil = "";
       leseWortMitPunkten(pfadAnteil);
       cout << "PA " << pfadAnteil.zkNT() << endl;
       
       urlPfad.dazu(pfadAnteil);
       
       if( m_hatZeichen &&  (m_aktuellesZeichen == '/') )
       {
           urlPfad.dazu('/');
           holeZeichen();
       }
       anzahlPfadAnteile++;
       if( anzahlPfadAnteile > 20 )
       {
          return false;
       }
    }
    parameterListe.loescheFeld();
    if( m_hatZeichen  && (m_aktuellesZeichen == '?') )
    {
       holeZeichen();
       istProzedur = true;
       prozedurName = urlPfad;
       urlPfad = "";
       parseProzedurParameter(parameterListe);
    }
    if( m_hatZeichen &&  (m_aktuellesZeichen == ' ') )
    {
        holeZeichen();
    }
    else return false;
 
    
    return true;
}
    


#ifdef URLPARSER_UNITTEST

#include <assert.h>

int main(int argc, char** argv)
{
   Zeichenkette method;
   bool istProzedur;
   Zeichenkette dateiPfad; 
   Zeichenkette prozedurName;
   bool erfolg;
   ParameterListeTyp parameterListe(5,erfolg);

   URLParser urlparser("GET / HTTP/1.0");
   assert(urlparser.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe));
   dateiPfad = "";
   prozedurName = "";
   parameterListe.loescheFeld();
   

   URLParser urlparser2("GETX / HTTP/1.0");
   assert(!urlparser2.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe));

   URLParser urlparser3("GET/ HTTP/1.0");
   assert(!urlparser3.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe));


   URLParser urlparser4("GET/ HTTP/1.0");
   assert(!urlparser4.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe));
   dateiPfad = "";
   prozedurName = "";
   parameterListe.loescheFeld();

   URLParser urlparser5("GET /index.html HTTP/1.0");
   assert(urlparser5.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe) && (dateiPfad == "/index.html") && !istProzedur );

   dateiPfad = "";
   prozedurName = "";
   parameterListe.loescheFeld();

   URLParser urlparser6("GET /verzeichnisB/index.html HTTP/1.0");
   erfolg = urlparser6.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe);
   assert( erfolg  && (dateiPfad == "/verzeichnisB/index.html") && !istProzedur);

   dateiPfad = "";
   prozedurName = "";
   parameterListe.loescheFeld();

   URLParser urlparserPARAM("GET /rechne?A=15&B=177 HTTP/1.0");
   assert(urlparserPARAM.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe) && istProzedur);
   assert( parameterListe.anzahl() == 2 );
   Zeichenkette wert;
   Zeichenkette schluessel;
   schluessel = "A";
   assert( parameterListe.finde(schluessel,wert) && (wert == "15") );
   schluessel = "B";
   assert( parameterListe.finde(schluessel,wert) && (wert == "177") );

   dateiPfad = "";
   prozedurName = "";
   parameterListe.loescheFeld();

    


   URLParser urlparserPARAM2("GET /register?Name=Heinz HTTP/1.0");
   assert(urlparserPARAM2.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe));
   assert( parameterListe.anzahl() == 1 );
 
   schluessel = "Name";
   assert( parameterListe.finde(schluessel,wert) && (wert == "Heinz") );


   URLParser urlparserPARAM3("GET /rechne?A=15&B=177&C=6&D=1001 HTTP/1.0");
   assert(urlparserPARAM3.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe));

   URLParser urlparserPARAM4("GET /rechne?A=15&B=177&&C=6&D=1001 HTTP/1.0");
   assert( !urlparserPARAM4.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe) );


   URLParser urlparserPARAM5("GET /rechne?16=15&B=177&C=6&D=1001 HTTP/1.0");
   assert( !urlparserPARAM5.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe) );

   cout << "unit Test erfolgreich" << endl;
   return 1;
}

#endif






