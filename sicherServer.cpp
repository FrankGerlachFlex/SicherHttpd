/* Einfacher und sicherer Webserver, in C++.

   Erweiterbar durch benutzerdefinierten C++ Code.

   (C) Frank Gerlach 2017, frankgerlach.tai@gmx.de

   Kommerzielle Nutzung erfordert eine kostenpflichtige Lizenz.

*/




#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern "C" {
#include <pthread.h>
}

#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


#define SNAME "Server: SicherServer\r\n"


/* Klasse zum effizienten, sicheren und komfortablen Einlesen von einem Socket */
class Lesepuffer
{
   char*    m_rohPuffer;
   uint16_t m_kapazitaet;
   uint16_t m_gueltig;
   uint16_t m_leseZeiger;
   int      m_socket;
public:
   Lesepuffer(int socket, bool& erfolg):m_kapazitaet(2000),
                                        m_gueltig(0),
                                        m_leseZeiger(0),
                                        m_socket(socket)
   {
      m_rohPuffer = new char[m_kapazitaet];
      erfolg = m_rohPuffer != NULL;        
   }

   char leseZeichen(bool& erfolg)
   {
      if( m_leseZeiger == m_gueltig )
      {
         int antwort = recv(m_socket,m_rohPuffer, m_kapazitaet, 0);
         if( antwort < 1 )
         {
             erfolg = false;
             return 0;
         } 
         else
         {
            cout << antwort << " oktets gelesen " << endl;
            m_gueltig = antwort;
            m_leseZeiger = 0;
         }
      }
      erfolg = true;
      //cout  << m_rohPuffer[m_leseZeiger];
      return m_rohPuffer[m_leseZeiger++];
   }

   ~Lesepuffer()
   {
      delete[] m_rohPuffer;
      m_rohPuffer = NULL;
   }

};

void* arbeite(void* param);
void fehlermeldung(int);
void sendeDatei(int, FILE *);
void fatalerFehler(const char *);
int leseZeile(Lesepuffer& lesepuffer, char *, int);
void kopfZeilen(int, const char *);
void not_found(int);
void serve_file(Lesepuffer&,int, const char *);
int fahreHoch(u_short *);
void nichtRealisiert(int);

#define leerzeichen(x) isspace((int)(x))

bool istNormalZeichen(char z)
{
   switch(z)
   {
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '/':return true;
      default: return false;
   }
   return false;
}


/* stelle sicher, dass in der URL keine illegalen Zeichen oder
   Konstrukte, insbesondere ".." vorhanden sind.
*/
bool pruefeURL(char* zk)
{
   uint16_t zeiger = 0;
   char zeichen = zk[zeiger++]; 
  
   while( (zeiger < 1000) && zeichen )
   {
       if( !istNormalZeichen(zeichen) )
       {
          if( zeichen == '.' )
          {
             zeichen = zk[zeiger++];
             if( zeichen && !istNormalZeichen(zeichen) )
             {
               return false;
             } 
          }
          else return false;
       }
       else
       {
         zeichen = zk[zeiger++];
       }
   }
   return true; 
}

/* sende die gesamte Anzhal Oktets, blockiere bis
   vollstaendig gesendet
*/
void sendAlles(int socket, char* puffer, uint16_t anzahl)
{
   uint16_t anzGesendet = 0;
   do
   {
      int ergebnis = send(socket,puffer,anzahl,0);
      if( ergebnis < 1 )
      {
        return; // fehler, Verbindung abgebrochen ?
      }
      else
      {
         anzGesendet += ergebnis;
      }
   }
   while(anzGesendet < anzahl);

}

/* sende eine Null-Terminierte Zeichenkette an die Gegenstelle */
void sendAllesZK(int socket, char* pufferNT)
{
  cout << "sendAllesZK() " << pufferNT << endl;
  sendAlles(socket,pufferNT,strlen(pufferNT));
}




void nichtRealisiert(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
	sendAllesZK(client, buf);
	sprintf(buf, SNAME);
	sendAllesZK(client, buf);
	sprintf(buf, "Content-Type: text/html\r\n");
	sendAllesZK(client, buf);
	sprintf(buf, "\r\n");
	sendAllesZK(client, buf);
	sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
	sendAllesZK(client, buf);
	sprintf(buf, "</TITLE></HEAD>\r\n");
	sendAllesZK(client, buf);
	sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
	sendAllesZK(client, buf);
	sprintf(buf, "</BODY></HTML>\r\n");
	sendAllesZK(client, buf);
}


/*arbeite die Anfrage auf einem Socket ab */
void* arbeite(void* param) //int client)
{
 long long clientLL = (long long)param;
 int client = clientLL;

 char url[255];
 char path[512];
 char buf[1024];
 int numchars;
 char method[255];
 
 size_t i, j;
 struct stat st;
 int cgi = 0;      /* becomes true if server decides this is a CGI
                    * program */
 char *query_string = NULL;

 bool erfolg;
 Lesepuffer lesepuffer(client,erfolg);

 if(!erfolg)
 {
   return NULL;
 } 

 numchars = leseZeile(lesepuffer, buf, sizeof(buf));


 cout << "request: " << buf << endl;

 i = 0; j = 0;
 while (!leerzeichen(buf[j]) && (i < sizeof(method) - 1))
 {
  method[i] = buf[j];
  i++; j++;
 }
 method[i] = '\0';

 if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))
 {
  nichtRealisiert(client);
  return NULL;
 }

 if (strcasecmp(method, "POST") == 0)
  cgi = 1;

 i = 0;
 while (leerzeichen(buf[j]) && (j < sizeof(buf)))
  j++;
 while (!leerzeichen(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf)))
 {
  url[i] = buf[j];
  i++; j++;
 }
 url[i] = '\0';

 printf("%s\n",url);

 if( !pruefeURL(url) )
 {
   printf("illegale URL\n");
   url[0] = 0;  
 }

 if (strcasecmp(method, "GET") == 0)
 {
  query_string = url;
  while ((*query_string != '?') && (*query_string != '\0'))
   query_string++;
  if (*query_string == '?')
  {
   cgi = 1;
   *query_string = '\0';
   query_string++;
  }
 }

 sprintf(path, "/home/buero/htdocs%s", url);
 if (path[strlen(path) - 1] == '/')
  strcat(path, "index.html");
 if (stat(path, &st) == -1) {
  while ( numchars > 0 )  /* read & discard kopfZeilen */
   numchars = leseZeile(lesepuffer, buf, sizeof(buf));
  not_found(client);
 }
 else
 {
  if ((st.st_mode & S_IFMT) == S_IFDIR)
   strcat(path, "/index.html");
  if ((st.st_mode & S_IXUSR) ||
      (st.st_mode & S_IXGRP) ||
      (st.st_mode & S_IXOTH)    )
   cgi = 1;
  if (!cgi)
  {
   printf("%s\n",path);
   serve_file(lesepuffer,client, path);
  }
  else
  {}
   //fuehreCGIAus(client, path, method, query_string);
 }

 close(client);

 return NULL;
}

void fehlermeldung(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, "Content-type: text/html\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, "\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    sendAllesZK(client, buf);
    sprintf(buf, "such as a POST without a Content-Length.\r\n");
    sendAllesZK(client, buf);
}


//TODO: Binaere Datei ???
void sendeDatei(int client, FILE *resource)
{
 char buf[1024];

 fgets(buf, sizeof(buf), resource);
 while (!feof(resource))
 {
  sendAllesZK(client, buf);
  fgets(buf, sizeof(buf), resource);
 }
}


void fatalerFehler(const char *sc)
{
 perror(sc);
 exit(1);
}

/* lese eine Zeile des HTTP-Protokolls ein */
int leseZeile(Lesepuffer& lesepuffer, char *buf, int size)
{
    bool erfolg;
    uint16_t ausgabeZeiger=0;
    char zeichen = lesepuffer.leseZeichen(erfolg);
    if(!erfolg)
    {
      cout << "F1" << endl;
      return -1;
    }
    do
    {
       if( zeichen == '\r' )
       {
          zeichen = lesepuffer.leseZeichen(erfolg);
          if(!erfolg || (zeichen != '\n') )
          {
            buf[size -1] = 0;
            cout << "puffer-1-1:" << buf;
            return -1;
          }
           
       }   
       else
       {
          if( ausgabeZeiger < size )
          {
             buf[ausgabeZeiger++] = zeichen;               
          }
          else
          {
            buf[size -1] = 0;
            cout << "puffer-1:" << buf;
            return -1;
          }
          zeichen = lesepuffer.leseZeichen(erfolg);
          if(!erfolg)
          {
            cout << "puffer-3:" << buf;
            return -1;
          } 
       } 
         
    }
    while(zeichen != '\n');

    if( ausgabeZeiger < size )
    {
       buf[ausgabeZeiger++] = 0;               
    }
    else
    {
       cout << "puffer-2:" << buf;
       buf[size-1] = 0;
       return -1;
    }
    //cout << "puffer:" << buf << endl;

    return ausgabeZeiger-1 ;
}

int fahreHoch(u_short *port)
{
    int acceptPort = 0;
    struct sockaddr_in name;

    acceptPort = socket(PF_INET, SOCK_STREAM, 0);
    if (acceptPort == -1)
    {
      fatalerFehler("socket");
    }
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(acceptPort, (struct sockaddr *)&name, sizeof(name)) < 0)
    {
       fatalerFehler("bind");
    }
    if (*port == 0)  
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(acceptPort, (struct sockaddr *)&name, &namelen) == -1)
         fatalerFehler("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(acceptPort, 5) < 0)
    {
     fatalerFehler("listen");
    }
    return acceptPort;
}

void kopfZeilen(int client, const char *filename)
{
 char buf[1024];
 (void)filename;  /* could use filename to determine file type */

 strcpy(buf, "HTTP/1.0 200 OK\r\n");
 sendAllesZK(client, buf);
 strcpy(buf, SNAME);
 sendAllesZK(client, buf);
 sprintf(buf, "Content-Type: text/html\r\n");
 sendAllesZK(client, buf);
 strcpy(buf, "\r\n");
 sendAllesZK(client, buf);
}

/**********************************************************************/
/* Give a client a 404 not found status message. */
/**********************************************************************/
void not_found(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, SNAME);
    sendAllesZK(client, buf);
    sprintf(buf, "Content-Type: text/html\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, "\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, "<BODY><P>The server could not find the file\r\n");
    sendAllesZK(client, buf);
    sprintf(buf, "</BODY></HTML>\r\n");
    sendAllesZK(client, buf);
}

/* Schicke eine Datei zum Webbrowser */
void serve_file(Lesepuffer& lesepuffer,int clientSocket, const char *filename)
{
 FILE *resource = NULL;
 int numchars = 1;
 char buf[1024];

 buf[0] = 'A'; buf[1] = '\0';
 while ( numchars > 0 )  /* read & discard kopfZeilen */
 {
  cout << "P0" << endl;
  numchars = leseZeile(lesepuffer, buf, sizeof(buf));
 }

 cout << "P1" << endl;

 resource = fopen(filename, "r");
 if (resource == NULL)
  not_found(clientSocket);
 else
 {
  cout << "P2" << endl;
  kopfZeilen(clientSocket, filename);
  cout << "P3" << endl;
  sendeDatei(clientSocket, resource);
  cout << "P4" << endl;
 }
 fclose(resource);
}






int main(void)
{
 int server_sock = -1;
 u_short port = 82;
 int client_sock = -1;
 struct sockaddr_in client_name;
 socklen_t client_name_len = sizeof(client_name);
 pthread_t newthread;

 server_sock = fahreHoch(&port);
 printf("httpd running on port %d\n", port);

 while (1)
 {
   client_sock = accept(server_sock,
                       (struct sockaddr *)&client_name,
                       &client_name_len);
   if (client_sock == -1)
   {
     perror("accept failed");
   }

   long long client_sockLL = client_sock;
   if (pthread_create(&newthread , NULL, arbeite, (void*) client_sockLL) != 0)
   {
      perror("pthread_create");
   }
 }

 close(server_sock);

 return(0);
}
