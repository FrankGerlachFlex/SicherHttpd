#ifndef LESEPUFFER_H
#define LESEPUFFER_H


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
            m_gueltig = antwort;
            m_leseZeiger = 0;
         }
      }
      erfolg = true;
      return m_rohPuffer[m_leseZeiger++];
   }

   ~Lesepuffer()
   {
      delete[] m_rohPuffer;
      m_rohPuffer = NULL;
   }
};

#endif
