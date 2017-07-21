#ifndef THREADVERWALTUNG
#define THREADVERWALTUNG


template<uint8_t anzThreads>
class ThreadVerwaltung
{
   Feld<pthread_t> m_threads;
   Feld<uint8_t> m_zustand;

  

public:
  ThreadVerwaltung()
  {
     m_threads.resize(anzThreads); 
     m_zustand.resize(anzThreads);
     for(uint8_t i=0; i < anzThreads; i++)
     {
        m_zustand[i] = 1;
     }
  }

  void herunterfahren()
  {
       for(uint8_t i=0; i < anzThreads; i++)
       {
          if( m_zustand[i] == 0 )
          {
             void* retVal(NULL);
             if (pthread_join(m_threads[i], &retVal) != 0)
             {
                perror("pthread_join");
             }
             else
             {
                m_zustand[i] = 1;
             }
          }                         
       }
  }

  void erzeugeThread(long long client_sockLL)
  {
       bool freeThreadFound(false);

       while( !freeThreadFound )
       {
          for(uint8_t i=0; i < anzThreads; i++)
          {
             if( m_zustand[i] == 1 )
             {
                if (pthread_create(&m_threads[i], NULL, arbeite, (void*) client_sockLL) != 0)
                {
                   perror("pthread_create");
                }
                m_zustand[i] = 0;
                freeThreadFound = true;
                break;
             }
          }
          if( !freeThreadFound )
          {
             for(uint8_t i=0; i < anzThreads; i++)
             {
                void* retVal(NULL);
                if (pthread_join(m_threads[i], &retVal) != 0)
                {
                   perror("pthread_join");
                }
                else
                {
                   m_zustand[i] = 1;
                }                         
             }
          }
       }       
  }
 
};
