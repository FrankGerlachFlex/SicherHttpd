#ifndef DATEILESER_H
#define DATEILESER_H


/* Sichere, effiziente und komfortable Klasse zum Einlesen von Textdateien

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/


#include "zk.h"

class Dateileser
{
   Zeichenkette m_dateiName;
   char* m_puffer;
   uint32_t m_gueltigImPuffer;
   uint32_t m_leseZeiger;
   uint32_t m_pufferGroesse;
   int m_dateiHenkel;

   bool fuellePuffer();

public:
   Dateileser(const Zeichenkette& dateiName, uint32_t pufferGroesse = 10000);

   bool oeffne();
   bool leseZeile(Zeichenkette& zeile);


   ~Dateileser();
};

#endif
