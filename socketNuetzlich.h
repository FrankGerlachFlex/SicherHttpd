#ifndef SOCKETNUETZLICH
#define SOCKETNUETZLICH

#include "zk.h"

void sendAlles(int socket, const char* puffer, uint16_t anzahl);

/* sende eine Null-Terminierte Zeichenkette an die Gegenstelle */
void sendAllesZK(int socket, const char* pufferNT);


void sendeHTTPantwort(int socket, const Zeichenkette& antwort);

void bestimmePartnerIP(int socket, Zeichenkette& partnerIP);

#endif
