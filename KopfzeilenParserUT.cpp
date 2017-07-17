#include <assert.h>
#include <iostream>
#include "zk.h"
#include "KopfzeilenParser.h" 

using namespace std;

int main(int argc, char** argv)
{
    {
       KopfzeilenParser kop("User-Agent: Mozilla/17.0\r\n");
       Zeichenkette name, wert;
       assert( kop.leseZeile(name, wert) && (name == "User-Agent") && (wert == "Mozilla/17.0" ) );
    }

    {
       KopfzeilenParser kop("Header2: value2\r\n");
       Zeichenkette name, wert;
       assert( kop.leseZeile(name, wert) && (name == "Header2") && (wert == "value2" ) );
    }

    {
       KopfzeilenParser kop("Content-Length: 1354\r\n");
       Zeichenkette name, wert;
       assert( kop.leseZeile(name, wert) && (name == "Content-Length") && (wert == "1354" ) );
    }

    {
       KopfzeilenParser kop("Content-Type: text/html\r\n");
       Zeichenkette name, wert;
       assert( kop.leseZeile(name, wert) && (name == "Content-Type") && (wert == "text/html" ) );
    }
    {
       KopfzeilenParser kop("Content-Type:: text/html\r\n");
       Zeichenkette name, wert;
       assert( !kop.leseZeile(name, wert)  );
    }

    {
       KopfzeilenParser kop("Content-Type text/html\r\n");
       Zeichenkette name, wert;
       assert( !kop.leseZeile(name, wert)  );
    }
    {
       KopfzeilenParser kop("Content-Type: text:html\r\n");
       Zeichenkette name, wert;
       assert( !kop.leseZeile(name, wert)  );
    }


    cout << "Unit Test erfolgreich " << endl;
    return 0;
}
 
