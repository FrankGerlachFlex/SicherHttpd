#include <assert.h>
#include <iostream>
#include "zk.h"

/* Unit Test fuer Stringklasse */


using namespace std;


int main(int argc,char** argv)
{
   bool erfolg;
   Zeichenkette zk(10,erfolg);

   assert( erfolg && (zk.laenge()==0) );

   erfolg = zk.dazu("Apfel");

   assert( erfolg && (zk.laenge()==5)  && (zk == "Apfel") );

   Zeichenkette zkb(1,erfolg);
   assert( erfolg && (zkb.laenge()==0) );

   erfolg = zkb.dazu("Birne");
   assert( erfolg && (zkb.laenge()==5)  && (zkb == "Birne") );

   erfolg = zk.dazu(zkb);
   assert( erfolg && (zk.laenge()==10)  && (zk == "ApfelBirne") );

   const char* zkNT = zk.zkNT();
   assert( zkNT && ( strcmp(zkNT,"ApfelBirne")== 0)  );

   uint8_t i;
   for(i=0; i < 10;i++)
   {
      char dazuStr[2];
      dazuStr[0] = 'A'+i;
      dazuStr[1] = 0;
      assert( zkb.dazu(dazuStr) );
   }
   assert( (zkb.laenge() == 15) && (zkb == "BirneABCDEFGHIJ" ) );

   erfolg = zkb.dazu(zk); 
   assert( erfolg && (zkb == "BirneABCDEFGHIJApfelBirne") );
   assert( zkb[9] == 'E' );

   zkb.leere();
   assert( zkb == "" );

   zk.leere(true);
   assert( zk == "" );

   erfolg = zk.dazu("Apfel");
   assert( erfolg && (zk.laenge()==5)  && (zk == "Apfel") );

   for(i=0; i < 10;i++)
   {
      char dazuStr[2];
      dazuStr[0] = 'A'+i;
      dazuStr[1] = 0;
      assert( zkb.dazu(dazuStr) );
   }
   assert( (zkb.laenge() == 10) && (zkb == "ABCDEFGHIJ" ) );
    
   

   cout << "Unit test erfolgreich" << endl;
}
