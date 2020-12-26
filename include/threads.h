#ifndef TOYGEN_THREADS_H
#define TOYGEN_THREADS_H

#include<thread>
#include <pthread.h>
#include <vector>

class Threads 
{
public:
  template<typename FUNC, typename... IN_TYPES>
  Threads(FUNC& function, IN_TYPES... args)
  {
    m_threads.resize( m_nthreads );
    for (unsigned int i = 0; i < m_nthreads; i++) {
      m_threads.push_back( std::thread(function,args...) );
    }

    for (unsigned int i = 0; i < m_nthreads; i++) {
      m_threads[i].join();
    }
  }
  ~Threads() {};

  static void setNThreads(unsigned int n) { m_nthreads = n; }

private:
  std::atomic<bool>        m_complete;
  std::vector<std::thread> m_threads;
  static unsigned int      m_nthreads;

};

#endif