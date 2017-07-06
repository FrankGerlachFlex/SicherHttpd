#ifndef FG_FELD
#define FG_FELD


/* Parameterisierte Feldklasse. 

   Vorteil gegenüber std::vector ist die Absicherung
   des Indexzugriffs gegen falsche Indizes.

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/

#include <vector>



template<class Nutzlast>
class Feld: public std::vector<Nutzlast> 
{
public:
   Nutzlast& operator[](int stelle)
   {
      return this->at(stelle);
   }
};

#endif
