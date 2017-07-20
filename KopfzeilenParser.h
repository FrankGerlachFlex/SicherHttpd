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
   KopfzeilenParser(Lesepuffer* lesePuffer):m_hatZeichen(false),m_lesePuffer(lesePuffer)
   {
       holeZeichen();
   }
private:
   void holeZeichen()
   {
       bool erfolg;
       m_aktuellesZeichen = m_lesePuffer->leseZeichen(erfolg);
       m_hatZeichen = erfolg;
   }

   bool leseWert(Zeichenkette& wert)
   {
      wert = "";
      while( m_hatZeichen && istKopfzeilenWertZeichen(m_aktuellesZeichen) )
      {
          wert.dazu(m_aktuellesZeichen);
          holeZeichen();
      }
      return wert.laenge() > 0;
   }
public:
#else
   Zeichenkette m_eingabe;
   uint32_t m_eingabeZeiger;


   KopfzeilenParser(const char* eingabe):m_hatZeichen(false),m_lesePuffer(NULL),m_eingabeZeiger(0)
   {
       m_eingabe.dazu(eingabe);
       holeZeichen();
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
      name.leere();
      wert.leere();

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

             if( m_hatZeichen && (m_aktuellesZeichen == ' ') )
             {
                holeZeichen();
             }
             else return false;

             while( m_hatZeichen && (m_aktuellesZeichen != '\r') )
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


class HostWertPruefer
{
    const Zeichenkette* m_zk;
    uint32_t m_stelle;
    char     m_aktuellesZeichen;
    bool     m_hatZeichen;

    void leseZeichen()
    {
       if( (m_stelle < 1000) && (m_stelle < m_zk->laenge()) )
       {
           m_aktuellesZeichen = (*m_zk)[m_stelle++];
           m_hatZeichen = true;
       }
       else
       {
          m_hatZeichen = false;
       }
    }

    bool leseHostWort()
    {
       uint32_t laenge(0);
       while( (laenge < 30) && m_hatZeichen && istHostBst(m_aktuellesZeichen))
       {
          laenge++;
          leseZeichen();
       }
       return laenge > 0;
    }

    bool leseHostPort()
    {
       uint32_t laenge(0);
       while( (laenge < 6) && m_hatZeichen && istZiffer(m_aktuellesZeichen))
       {
          laenge++;
          leseZeichen();
       }
       return laenge > 0;
    }

public:
    HostWertPruefer(const Zeichenkette* zk):m_zk(zk),
                                            m_stelle(0),
                                            m_aktuellesZeichen(0),
                                            m_hatZeichen(false)
    {
       leseZeichen();
    }

    bool pruefe()
    {
        bool wortFolgt(false);
        while( leseHostWort() )
        {
            wortFolgt = false;
            if( m_hatZeichen && (m_aktuellesZeichen == '.') )
            {
                wortFolgt = true;
                leseZeichen();
            }
        }
        if( wortFolgt )
        {
           return false;
        }
        if( m_hatZeichen && (m_aktuellesZeichen == ':') )
        {
            leseZeichen();
            if( !leseHostPort() )
            {
               return false;
            }
        }
        return !m_hatZeichen;
    }


};




#endif
