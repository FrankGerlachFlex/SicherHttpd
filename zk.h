#ifndef ZEICHENKETTE_HDR
#define ZEICHENKETTE_HDR

/* Sichere, hocheffiziente und komfortable C++ Stringklasse.

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

using namespace std;
 
class Zeichenkette
{
   char* m_puffer;
   uint64_t m_kapazitaet;//groesse des Puffers
   uint64_t m_gueltig;//anzahl Zeichen gueltig
public:
   Zeichenkette(uint64_t kapazitaet,bool& erfolg):m_kapazitaet(0),m_gueltig(0)
   {
      m_puffer = new char[kapazitaet];
      erfolg = (m_puffer != NULL);
   }

   char operator[](uint64_t stelle) const
   {
      if( stelle < m_gueltig )
      {
         return m_puffer[stelle];
      }
      else
      {
         return 0;//Fehler
      }
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
 
   ~Zeichenkette()
   {
      delete[] m_puffer;
      m_puffer = NULL;
   }
};



#endif
