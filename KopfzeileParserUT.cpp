#include "KopfzeilenParser.h" 

int main(int argc, char** argv)
{
    KopfzeilenParser kop("User-Agent: Mozilla/17.0\r\n");
    Zeichenkette name, wert;
    assert(kop.leseZeile(name, wert) && (name == "User-Agent") && (wert == "Mozilla/17.0" ) );
}
 
