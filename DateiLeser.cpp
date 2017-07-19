#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "DateiLeser.h"

bool Dateileser::fuellePuffer()
{
  if( m_dateiHenkel > 0)
  {
      int ergebnis = read(m_dateiHenkel,m_puffer,m_pufferGroesse);
      if( ergebnis > 0)
      {
          m_gueltigImPuffer = ergebnis;
          m_leseZeiger = 0;
          return true;
      }
  }
  return false;
}


Dateileser::Dateileser(Zeichenkette& dateiName, uint32_t pufferGroesse):m_gueltigImPuffer(0),
                                                                        m_leseZeiger(0),
                                                                        m_pufferGroesse(pufferGroesse)
{
    m_dateiName = dateiName;

    m_puffer = new char[m_pufferGroesse];
    if( m_puffer == NULL)
    {
        sicherSturz("kein Speicher");
    }
}

bool Dateileser::oeffne()
{
  m_dateiHenkel = open(m_dateiName.zkNT(),O_RDONLY);
  if( m_dateiHenkel < 1)
  {
     perror(m_dateiName.zkNT());
  }
  return m_dateiHenkel > 0;
}

bool Dateileser::leseZeile(Zeichenkette& zeile)
{
  zeile.leere();
  char zeichen = 0;
  do
  {
      if( m_gueltigImPuffer == m_leseZeiger)
      {
         if( !fuellePuffer() )
         {
             return false;
         }
      }
      zeichen = m_puffer[m_leseZeiger++];
      if( zeichen != '\n')
      {
         zeile.dazu(zeichen);
      }
  }
  while( zeichen != '\n');
  return true;
}


Dateileser::~Dateileser()
{
   m_gueltigImPuffer = 0;
   delete[] m_puffer;
   m_puffer = NULL;
   if( m_dateiHenkel > 0)
   {
      close(m_dateiHenkel);
   }
}


#ifdef DATEILESER_UT

using namespace std;

//Unit test DateiLeser
int main(int argc, char** argv)
{
    Zeichenkette pfad;
    pfad = "./dateiTest.config";
    Dateileser dl(pfad,3);
    assert(dl.oeffne());
    Zeichenkette zeile;
    assert(dl.leseZeile(zeile) && (zeile == "Dachs"));
    assert(dl.leseZeile(zeile) && (zeile == "Spatz"));
    assert(dl.leseZeile(zeile) && (zeile == "Maus"));
    assert(dl.leseZeile(zeile) && (zeile == "Hund"));

    cout << "Unit Test erfolgreich" << endl;
}

#endif






