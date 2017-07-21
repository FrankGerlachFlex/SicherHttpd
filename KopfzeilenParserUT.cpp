#include <assert.h>
#include <iostream>
#include "zk.h"
#include "KopfzeilenParser.h"

using namespace std;


bool pruefHost(const char* zk)
{
        Zeichenkette hostPruef;
        hostPruef = zk;
        HostWertPruefer hwp(&hostPruef);
        return hwp.pruefe();
}

int main(int argc, char** argv)
{
    {
       KopfzeilenParser kop("User-Agent: Mozilla/17.0\r\nHeader2: value2\r\nHeader3: value321\r\n");
       Zeichenkette name, wert;
       assert( kop.leseZeile(name, wert) && (name == "User-Agent") && (wert == "Mozilla/17.0" ) );
       assert( kop.leseZeile(name, wert) && (name == "Header2") && (wert == "value2" ) );
       assert( kop.leseZeile(name, wert) && (name == "Header3") && (wert == "value321" ) );
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
       assert( kop.leseZeile(name, wert)  );
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "www.meineseiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "www.meine/seiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "www..meineseiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "www/x.meineseiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "www/x.meineseiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "www_x.meineseiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "www.meine-seiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "x.meine-seiten.de";
        HostWertPruefer hwp(&hostPruef);
        assert(hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "x.meine-seiten.de:888";
        HostWertPruefer hwp(&hostPruef);
        assert(hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = "x.meine-seiten.de:";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }
    {
        Zeichenkette hostPruef;
        hostPruef = ".x.";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = ".";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }

    {
        Zeichenkette hostPruef;
        hostPruef = ".x";
        HostWertPruefer hwp(&hostPruef);
        assert(!hwp.pruefe());
    }
    assert(!pruefHost("x."));
    assert(!pruefHost(".x"));
    assert(!pruefHost(".."));
    assert(!pruefHost("."));

    assert(pruefHost("x.x"));
    assert(pruefHost("x:7122"));


    assert(!pruefHost("x/"));
    assert(!pruefHost("x:"));



    cout << "Unit Test erfolgreich " << endl;
    return 0;
}

