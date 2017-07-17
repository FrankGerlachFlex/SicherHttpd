#ifndef KOPFZEILENPARSER
#define KOPFZEILENPARSER
#include "LesePuffer.h"
#include "Nuetzlich.h"

class KopfzeilenParser
{
   char m_aktuellesZeichen;
   bool m_hatZeichen;
   Lesepuffer* m_lesePuffer;

   bool istKopfzeilenNameZeichen(char z)
   {
      switch(z)
      {
         case '0':
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':
         case '6':
         case '7':
         case '8':
         case '9':
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
         case '-':
         return true;
         default: return false;
      }
      return false;
   }

public:


   

#ifndef KOPFZEILENPARSER_UT
   KopfzeilenParser():m_hatZeichen(false),m_lesePuffer(lesePuffer)
   {}
   void holeZeichen(Lesepuffer* lesePuffer)
   {  
       bool erfolg;
       m_aktuellesZeichen = m_lesePuffer->leseZeichen(erfolg);
       m_hatZeichen = erfolg; 
   }

   bool leseWert(Zeichenkette& wert)
   {
      while( m_hatZeichen && istKopfzeilenWertZeichen(m_aktuellesZeichen) )
      {
          wert.dazu(m_aktuellesZeichen);
          holeZeichen();
      }
   }
#else
   Zeichenkette m_eingabe;
   uint32_t m_eingabeZeiger;


   KopfzeilenParser(const char* eingabe):m_hatZeichen(false),m_lesePuffer(NULL),m_eingabeZeiger(0)
   {
       m_eingabe.dazu(eingabe);
   }
   void holeZeichen()
   {  
       if( m_eingabe.laenge() == m_eingabeZeiger )
       {
          m_hatZeichen = false;
       }
       else
       {
          m_hatZeichen = true;           
          m_aktuellesZeichen = m_eingabe[m_eingabeZeiger++];
       }  
   }

   
#endif
   

   bool leseZeile(Zeichenkette& name, Zeichenkette& wert)
   {
      holeZeichen();
      while( m_hatZeichen && istKopfzeilenNameZeichen(m_aktuellesZeichen) )
      {
          name.dazu(m_aktuellesZeichen);
          holeZeichen();
      }
      if( name.laenge() > 0 )
      {
         if( m_hatZeichen && (m_aktuellesZeichen == ':') )
         {
             holeZeichen();
             
             while( m_hatZeichen && (m_aktuellesZeichen == ' ') )
             {
                holeZeichen();
             }
             while( m_hatZeichen && istKopfzeilenWertZeichen(m_aktuellesZeichen) )
             {
                wert.dazu(m_aktuellesZeichen);
                holeZeichen();
             }
             if( wert.laenge() > 0 )
             {
                if( m_hatZeichen && (m_aktuellesZeichen == '\r') )
                {
                   holeZeichen();
                   if( m_hatZeichen && (m_aktuellesZeichen == '\n') )
                   {
                      holeZeichen();
                      return true;
                   }
                }
             }            
         }          
      }
      return false;
   }


};




#endif
