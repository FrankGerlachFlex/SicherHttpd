/* Effizienter und sicherer URL Parser

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include <iostream>
#include "URLParser.h"

using namespace std;
 

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

URLParser::URLParser(const char* url):m_ausgabeStelle(0),
                                       m_aktuellesZeichen(0),
                                       m_hatZeichen(false)
{
    m_eingabe = url;
}

bool URLParser::parseProzedurParameter()
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
       cout << "PARAM " << paramName.zkNT() << " " << paramWert.zkNT() << endl;
       if( m_hatZeichen && (m_aktuellesZeichen == '&') )
       {
          holeZeichen();
       }
   }
   return true;
}

bool URLParser::parseURL()
{
    holeZeichen();
    Zeichenkette httpMethode;
    leseWortGB(httpMethode);

    if( !(httpMethode == "GET") )
    {
       return false;
    }
    if( m_hatZeichen &&  (m_aktuellesZeichen == ' ') )
    {
        holeZeichen();
    }
    else return false;

    if( m_hatZeichen &&  (m_aktuellesZeichen == '/') )
    {
        holeZeichen();
    }
    else return false;

    bool erfolg;
    Zeichenkette pfadAnteil(20,erfolg);
    if(!erfolg) return false;
    while( m_hatZeichen &&  (m_aktuellesZeichen != ' ') && (m_aktuellesZeichen != '?'))
    {
       
       leseWortMitPunkten(pfadAnteil);
       cout << "PA " << pfadAnteil.zkNT() << endl;
       pfadAnteil.leere();
       if( m_hatZeichen &&  (m_aktuellesZeichen == '/') )
       {
           holeZeichen();
       }
    }
    if( m_hatZeichen  && (m_aktuellesZeichen == '?') )
    {
       holeZeichen();
       parseProzedurParameter();
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
   URLParser urlparser("GET / HTTP/1.0");
   assert(urlparser.parseURL());

   URLParser urlparser2("GETX / HTTP/1.0");
   assert(!urlparser2.parseURL());

   URLParser urlparser3("GET/ HTTP/1.0");
   assert(!urlparser3.parseURL());


   URLParser urlparser4("GET/ HTTP/1.0");
   assert(!urlparser4.parseURL());

   URLParser urlparser5("GET /index.html HTTP/1.0");
   assert(urlparser5.parseURL());

   URLParser urlparser6("GET /verzeichnisB/index.html HTTP/1.0");
   assert(urlparser6.parseURL());

   URLParser urlparserPARAM("GET /rechne?A=15&B=177 HTTP/1.0");
   assert(urlparserPARAM.parseURL());

   URLParser urlparserPARAM2("GET /register?Name=Heinz HTTP/1.0");
   assert(urlparserPARAM2.parseURL());



   cout << "unit Test erfolgreich" << endl;
   return 1;
}

#endif






