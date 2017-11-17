#include <stdio.h>
#include <time.h>
#include "zk.h"

void getCurrentTime(Zeichenkette& output)
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  output.dazuZahl(timeinfo->tm_year + 1900);
  output.dazu(".");
  output.dazuZahl(timeinfo->tm_mon + 1);
  output.dazu(".");
  output.dazuZahl(timeinfo->tm_mday);
  output.dazu(" ");
  output.dazuZahl(timeinfo->tm_hour);
  output.dazu(":");
  output.dazuZahl(timeinfo->tm_min);
  output.dazu(":");
  output.dazuZahl(timeinfo->tm_sec);
}
