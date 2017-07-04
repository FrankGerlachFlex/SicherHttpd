#include <assert.h>
#include "zk.h"



int main(int argc,char** argv)
{
   bool erfolg;
   Zeichenkette zk(10,erfolg);

   assert( erfolg && (zk.laenge()==0) );
}
