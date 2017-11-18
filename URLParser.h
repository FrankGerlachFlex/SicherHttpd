#ifndef URLPARSER
#define URLPARSER

#include "Streufeld.h"
#include "HashAdapterZK.h"
#include "LesePuffer.h"

/* Effizienter und sicherer URL Parser

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include "zk.h"


typedef Streufeld<Zeichenkette,Zeichenkette,SchlAdapterZK,WertAdapterZK> ParameterListeTyp;

/* sicherer URL Parser */
class URLParser
{
#ifdef URLPARSER_UNITTEST
   Zeichenkette m_eingabe;
   uint32_t m_ausgabeStelle;
#else
   Lesepuffer* m_lesePuffer;
   uint32_t m_groessteURL_Laenge;
   uint32_t m_zeichenGelesen;
#endif

   char m_aktuellesZeichen; 
   bool m_hatZeichen;
   

   void holeZeichen();

   bool istGrossBst(char z);




   bool leseWortGB(Zeichenkette& wort);

   bool leseWort(Zeichenkette& wort);

   //lese zB. "index.html" oder "antwort.txt.alt"
   //bool leseWortMitPunkten(Zeichenkette& wort);
   bool leseURLPfadanteil(Zeichenkette& wort);

   bool leseParamWert(Zeichenkette& wort);

   bool parseProzedurParameter(ParameterListeTyp& parameterListe);

   bool istWertZeichen(char z);


  void richteEin()
  {
     m_aktuellesZeichen = 0;
     m_hatZeichen = false;
  }

 
public:
#ifdef URLPARSER_UNITTEST
   URLParser(const char* testURL):m_ausgabeStelle(0)
   {
      richteEin();
      m_eingabe = testURL;
   }
#else
   URLParser(Lesepuffer* lesepuffer,uint32_t groessteURL_Laenge):m_lesePuffer(lesepuffer),
                                                                 m_groessteURL_Laenge(groessteURL_Laenge),
                                                                 m_zeichenGelesen(0)
   {
      richteEin();
   }
#endif
    

    bool parseURL(Zeichenkette& method, 
                  bool& istProzedur,
                  Zeichenkette& urlPfad, 
                  Zeichenkette& prozedurName,
                  ParameterListeTyp& parameterListe);

    
};
    

#endif
