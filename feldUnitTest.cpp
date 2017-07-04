#include <string>
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include "feld.h"

using namespace std;

struct Adresse
{
   string m_vorname;
   string m_nachname;
   string m_strasse;
   uint32_t m_plz;
   string m_ort;
};

int main(int argc, char** argv)
{
  Feld<Adresse> feld;

  Adresse a;
  a.m_vorname  = "Frank";  
  a.m_nachname = "Gerlach";
  a.m_strasse  = "Kirchgasse";
  a.m_plz      = 71126;
  a.m_ort      = "Gaeufelden-Tailfingen";

  feld.push_back(a);
  feld.push_back(a);
  feld.push_back(a);

  assert(feld[2].m_nachname == "Gerlach"); 

  feld[1].m_vorname = "Dieter";

  assert(feld[1].m_vorname == "Dieter"); 

  //crash
  assert(feld[3].m_vorname == "Dieter"); 

  cout << "Unit Test erfolgreich" << endl;
}
