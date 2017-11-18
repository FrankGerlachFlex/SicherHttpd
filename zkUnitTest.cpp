#include <assert.h>
#include <iostream>
#include "zk.h"
#include "feld.h"

/* Unit Test fuer Zeichenketten-Klasse */


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

   zk = "12345";
   assert( (zk.laenge() == 5) && (zk == "12345") );

   zk = "GET /index.html HTTP/1.0";
   erfolg = zk.linksBisLeerzeichen(zkb);
   assert( erfolg && (zkb.laenge() == 3) && (zkb == "GET" ) );

   assert( zk.letztesZeichenIst('0') );

   zkb.leere(true);
   for(i=0; i < 10;i++)
   {       
      assert( zkb.dazu('A'+i) );
   }
   assert( (zkb.laenge() == 10) && (zkb == "ABCDEFGHIJ" ) );

   Feld<Zeichenkette> feld;
   feld.resize(3);

   zk = "GET /broschuere.html HTTP/1.0 nix mehr";

   zk.spalteAuf(' ',feld);

   assert( feld[0] == "GET" );
   assert( feld[1] == "/broschuere.html" );
   assert( feld[2] == "HTTP/1.0" );

   zk = "index.html";
   Zeichenkette zEnde("html");
   assert( zk.endetMit(zEnde) );

   zk = "index.htm";
   assert( !zk.endetMit(zEnde) );

   zk = "gemiSCHT";

   zk.makeLowerCase();
   assert( zk == "gemischt" ); 

   
   zk.makeUpperCase();
   assert( zk == "GEMISCHT" ); 

   zk = "123klein";
   zk.makeLowerCase();
   assert( zk == "123klein" ); 
   zk.makeUpperCase();
   assert( zk == "123KLEIN" ); 

   zk = "test.123";

   Zeichenkette rechts;
   zk.rechtsBisZeichen('.',rechts);
   assert( rechts == "123" );

   zk = "unix";
   zk.rechtsBisZeichen('.',rechts);
   assert( rechts == "unix" );
  
   zk = "unix.";
   zk.rechtsBisZeichen('.',rechts);
   assert( rechts == "" );

   cout << "Unit test erfolgreich" << endl;
}
