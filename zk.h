#ifndef ZEICHENKETTE_HDR
#define ZEICHENKETTE_HDR

/* Sichere, hocheffiziente und komfortable C++ Stringklasse.

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "feld.h"
#include "sicherSturz.h"

using namespace std;
 
class Zeichenkette
{
   char* m_puffer;
   uint64_t m_kapazitaet;//groesse des Puffers
   uint64_t m_gueltig;//anzahl Zeichen gueltig

   void richteEin()
   {
      m_puffer = NULL;
      m_kapazitaet = 0;
      m_gueltig = 0;
   }
public:
   Zeichenkette(const Zeichenkette& andere) 
   {
       richteEin();
       dazu(andere);
   }

   Zeichenkette(Zeichenkette& andere)
   {
      richteEin();
      dazu(andere);
   }

   Zeichenkette(uint64_t kapazitaet, bool& erfolg)
   {
      richteEin();
      erfolg = sichereKapazitaet(kapazitaet);
   }

   Zeichenkette() 
   {
       richteEin();
   }



   char operator[](uint64_t stelle) const
   {
      if( stelle < m_gueltig )
      {
         return m_puffer[stelle];
      }
      else
      {
         //perror("Indexfehler in Zeichenkette::operator[]");
         //exit(-1);        
         sicherSturz("Indexfehler in Zeichenkette::operator[]");
      }
      return 0xFF;//dummy
   }
 
   bool sichereKapazitaet(uint64_t mindestKapazitaet)
   {
       if( mindestKapazitaet > m_kapazitaet )
       {
          uint64_t neuKapazitaet = (m_kapazitaet+1)*2;
          if( neuKapazitaet < mindestKapazitaet )
          {
              neuKapazitaet = mindestKapazitaet;
          }
          char* neuPuffer = new char[neuKapazitaet];
          if( neuPuffer == NULL )
          {
             return false;
          }
          for(uint64_t i=0; i < m_gueltig; i++)
          {
             neuPuffer[i] =  m_puffer[i];
          }
          delete[] m_puffer;
          m_puffer = neuPuffer;
          m_kapazitaet = neuKapazitaet;
       }
       return true;
   }

   bool dazu(const char* zeichenketteNT)
   {
      uint64_t laengeDazu = strlen(zeichenketteNT);
      return dazu(zeichenketteNT,laengeDazu);
   }

   bool dazu(const char* zeichenkette, uint64_t laengeZK)
   {   
       uint64_t neuLaenge = m_gueltig+laengeZK;
       if( !sichereKapazitaet(neuLaenge) )
       {
         return false;
       }

       uint64_t i,j;
       for(j=0,i=m_gueltig; i < neuLaenge; i++,j++)
       {
          m_puffer[i] = zeichenkette[j];
       }
       m_gueltig = neuLaenge;
       return true;
   }

   bool dazu(const Zeichenkette& zeichenkette)
   {
      return dazu(zeichenkette.m_puffer,zeichenkette.m_gueltig);
   }

   bool dazu(char zeichen)
   {
      if( m_gueltig == m_kapazitaet )
      {
          if( !sichereKapazitaet(m_gueltig+1) )
          {
            return false;
          }
      }
      m_puffer[m_gueltig++] = zeichen;
      return true;
   }

   bool weiseZu(const char* dazuNT)
   {
       leere();
       return dazu(dazuNT);
   }

   bool weiseZu(const Zeichenkette& zkDazu)
   {
       leere();
       return dazu(zkDazu);
   }

   void operator=(const char* dazuNT)
   {
         if(!weiseZu(dazuNT) )
         {
            sicherSturz("Speichermangel");
         }
   }
   void operator=(const Zeichenkette& dazu)
   {
         if(!weiseZu(dazu) )
         {
            sicherSturz("Speichermangel");
         }
   }

   uint64_t laenge() const
   {
      return m_gueltig;
   }

   bool operator==(const char* vergleichZK) const
   {
       return gleich(vergleichZK);
   }

   bool operator==(const Zeichenkette& vergleichZK) const
   {
       return (vergleichZK.m_gueltig == m_gueltig) && gleich(vergleichZK.m_puffer);
   }

   bool gleich(const char* vergleichZK) const
   {
       uint64_t i=0;
       while( (i < m_gueltig) && vergleichZK[i] && (vergleichZK[i] == m_puffer[i]) )
       {
          i++;
       } 
       return i == m_gueltig;
   }

   /* gebe einen Nullterminierten "C String" zurueck */
   const char* zkNT()
   {
      if( !sichereKapazitaet(m_gueltig+1) )
      {
         return NULL;
      }
      m_puffer[m_gueltig] = 0;
      return m_puffer;
   }

   void leere(bool gebeSpeicherFrei=false)
   {
       m_gueltig = 0;
       if( gebeSpeicherFrei )
       {
          delete[] m_puffer;
          m_puffer = NULL;
          m_kapazitaet = 0;
       }
   }
 
   static bool istLeerzeichen(char zeichen)
   {
      switch( zeichen )
      {
         case ' ':
         case '\t':return true;
      }
      return false;
   }

   /* suche die "linke" Zeichenkette bis zu einem Leerzeichen.
      Gebe false zurück, wenn Speicher nicht angefordert werden kann */
   bool linksBisLeerzeichen(Zeichenkette& links) const
   {
        uint64_t i=0;
        char zeichen = 1;
        char puffer[2];
        puffer[1] = 0;
        links.leere();
        while( i < m_gueltig )
        {
           zeichen = (*this)[i++];
           if( istLeerzeichen(zeichen) )
           {
              break;
           }
           else
           {
              puffer[0] = zeichen;
              if( !links.dazu(puffer) )
              {
                 return false;
              }              
           }
        }
        return true;
   }

   bool letztesZeichenIst(char zeichen) const
   {
      if( m_gueltig > 0 )
      {
         return m_puffer[m_gueltig-1] == zeichen;
      }
      return false;
   }

   /* spalte die ZK nach einem Trennzeichen auf. Maximalzahl Spalten gegeben durch
      die Groesse des Feldes spalten.
   */
   void spalteAuf(char trenner, Feld<Zeichenkette>& spalten)
   {
      uint64_t spaltenZeiger = 0;
      uint64_t zeichenZeiger = 0;
      while( (zeichenZeiger < m_gueltig) && (spaltenZeiger < spalten.size()) )
      {
         char zeichen = m_puffer[zeichenZeiger++];
         if( zeichen == trenner )
         {
            spaltenZeiger++;
         }
         else
         {
            spalten[spaltenZeiger].dazu(zeichen);  
         }
      }
   }
 
   ~Zeichenkette()
   {
      delete[] m_puffer;
      m_puffer = NULL;
   }
};



#endif
