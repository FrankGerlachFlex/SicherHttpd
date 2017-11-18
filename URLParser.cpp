/* Effizienter und sicherer URL Parser

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include <iostream>
#include "URLParser.h"
#include "Nuetzlich.h"

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
    if( m_zeichenGelesen < m_groessteURL_Laenge )
    {
       bool erfolg;
       m_aktuellesZeichen = m_lesePuffer->leseZeichen(erfolg);
       if( erfolg )
       {
           m_zeichenGelesen++;
       }
       m_hatZeichen = erfolg;
    }
    else
    {
       m_hatZeichen = false;
       m_aktuellesZeichen = 0;
    }
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

enum ZeichenTyp{ZTBuchst,ZTZiffer,ZTUnterStrich,ZTStrich,ZTPunkt,ZTLeerzeichen,ZTSonstiges,ZTSchraegStrich,ZTFrageZeichen};

ZeichenTyp bestimmeTyp(char zeichen)
{
   switch(zeichen)
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
      case 'Z': return ZTBuchst;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': return ZTBuchst;
      case '.': return ZTPunkt;
      case '_': return ZTUnterStrich;
      case '-': return ZTStrich;
      case ' ': return ZTLeerzeichen;
      case '/': return ZTSchraegStrich;
      case '?': return ZTFrageZeichen;
      default:  return ZTSonstiges;
   }
}



/* lese Wort mit Grossbuchstaben */
bool URLParser::leseWortGB(Zeichenkette& wort)
{
   while( m_hatZeichen && istGrossBst(m_aktuellesZeichen) )
   {
       wort.dazu(m_aktuellesZeichen);
       holeZeichen();
   }
   return wort.laenge() > 0;
}

/* lese ein Wort mit Buchstaben */
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

//-----------//lese zB. "index.html" oder "antwort.txt.alt"
/*
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
*/

enum PfadAnteilParserZustand {ZAnfang,ZBuchstabe,ZZiffer,ZStrich,ZUnterStrich,ZPunkt};

bool URLParser::leseURLPfadanteil(Zeichenkette& wort)
{
   enum PfadAnteilParserZustand zustand = ZAnfang;

   while(m_hatZeichen)
   {
       switch(zustand)
       {
           case ZAnfang:
              if( istBst(m_aktuellesZeichen) )
              {
                   wort.dazu(m_aktuellesZeichen);
                   holeZeichen();
                   zustand = ZBuchstabe;
              }
              else return false;
           break;
           case ZBuchstabe:
              switch(bestimmeTyp(m_aktuellesZeichen) )
              {
                  case ZTBuchst:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZBuchstabe;
                  break;
                  case ZTPunkt:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZPunkt;
                  break;
                  case ZTZiffer:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZZiffer;
                  break;
                  case ZTStrich:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZStrich;
                  break;
                  case ZTUnterStrich:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZUnterStrich;
                  break;
                  case ZTLeerzeichen:
                  case ZTSchraegStrich:
                  case ZTFrageZeichen: return true;

                  default: return false; 
              }
           break;
           case ZZiffer:
              switch(bestimmeTyp(m_aktuellesZeichen) )
              {
                  case ZTBuchst:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZBuchstabe;
                  break;
                  case ZTPunkt:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZPunkt;
                  break;
                  case ZTZiffer:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZZiffer;
                  break;
                  case ZTStrich:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZStrich;
                  break;
                  case ZTUnterStrich:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZUnterStrich;
                  break;
                  case ZTLeerzeichen:
                      return true;
                  break;
                  case ZTSchraegStrich:
                      return true;
                  break;
                  default: return false; 
              }
           break;
           case ZUnterStrich:
              switch(bestimmeTyp(m_aktuellesZeichen) )
              {
                  case ZTBuchst:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZBuchstabe;
                  break;
                  case ZTZiffer:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZZiffer;
                  break;
                  default: return false; 
              }
           break;
           case ZStrich:
              switch(bestimmeTyp(m_aktuellesZeichen) )
              {
                  case ZTBuchst:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZBuchstabe;
                  break;
                  case ZTZiffer:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZZiffer;
                  break;
                  default: return false; 
              }
           break;
           case ZPunkt:
              switch(bestimmeTyp(m_aktuellesZeichen) )
              {
                  case ZTBuchst:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZBuchstabe;
                  break;
                  case ZTZiffer:
                      wort.dazu(m_aktuellesZeichen);
                      holeZeichen();
                      zustand = ZZiffer;
                  break;
                  default: return false; 
              }
           break;
           default: return false;
       }
   }
   return false;//es muss hinter einer URL immer noch ein " HTTP/1.x" kommen
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
          if( m_hatZeichen )
          {
             if(!leseParamWert(paramWert))
             {
                return false;
             }
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

    if( m_hatZeichen == false )
    {
      return false;
    }

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
       if( !leseURLPfadanteil(pfadAnteil) )
       {
         return false;
       } 
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

        while(m_hatZeichen && (m_aktuellesZeichen != '\n') ) // HTTPx/x\r\n weglesen
        {
           holeZeichen();
        }
    }
    else return false;


    return true;
}



#ifdef URLPARSER_UNITTEST

#include <assert.h>


void akzeptanzTest(const char* url)
{
      Zeichenkette method;
      bool istProzedur;
      Zeichenkette dateiPfad;
      Zeichenkette prozedurName;
      bool erfolg;
      ParameterListeTyp parameterListe(5,erfolg);
      URLParser urlparserB(url);
      if( urlparserB.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe) == false )
      {
         cout << "URLParser Unit test(akzeptanz) fehlgeschlagen: " << url << endl;
         exit(-1);
      }
}


void fehlerTest(const char* url)
{
      Zeichenkette method;
      bool istProzedur;
      Zeichenkette dateiPfad;
      Zeichenkette prozedurName;
      bool erfolg;
      ParameterListeTyp parameterListe(5,erfolg);
      URLParser urlparserB(url);
      if( urlparserB.parseURL(method,istProzedur,dateiPfad,prozedurName,parameterListe) == true )
      {
         cout << "URLParser Unit test(fehler) fehlgeschlagen: " << url << endl;
         exit(-1);
      }
}


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

   akzeptanzTest("GET /name.pdf HTTP/1.0");
   akzeptanzTest("GET /name3.pdf HTTP/1.0"); 

   akzeptanzTest("GET /name3441.pdf HTTP/1.0");   
   fehlerTest("GET /../x.pdf HTTP/1.0");   
   fehlerTest("GET /.../x.pdf HTTP/1.0");   
   fehlerTest("GET /.zzz/x.pdf HTTP/1.0");   
   fehlerTest("GET /aa/bb/ccccc/../x.pdf HTTP/1.0");
   fehlerTest("GET /aa/bb/............../../x.pdf HTTP/1.0");
   fehlerTest("GET jhdskfjhskdfh HTTP/1.0");
   fehlerTest("GET _____ HTTP/1.0");

   akzeptanzTest("GET /name3441/e333/a767267236762_33/x.pdf HTTP/1.0");   
   akzeptanzTest("GET /name3441/e3_33/a76_7267236762_33/x.pdf HTTP/1.0");

   fehlerTest("GET /_name3441/e3_33/a76_7267236762_33/x.pdf HTTP/1.0");

   fehlerTest("GET /apfel!/x.pdf HTTP/1.0");
   fehlerTest("GET /@pfel/x.pdf HTTP/1.0");
   fehlerTest("GET {apfel/x.pdf HTTP/1.0");

   cout << "unit Test efolgreich" << endl;
   return 1;
}

#endif






