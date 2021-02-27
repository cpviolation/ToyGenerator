#ifndef TOYGEN_MEMORYMANAGER_H
#define TOYGEN_MEMORYMANAGER_H

#include <cstddef>
#include <map>
#include <thread>

#include "msgservice.h"

class IMemoryManager
{
public:
  IMemoryManager() = default;
  virtual ~IMemoryManager() {}

  virtual void* allocate(size_t) = 0;
  virtual void  free(void*) = 0;
};

template<class T>
class MemoryManager : public IMemoryManager
{
private:
  T* m_pool = nullptr;

  int m_n;
  std::map<std::thread::id,T*> m_free;
public:
  MemoryManager() = default;
  ~MemoryManager() {}

  void setN(int max)
  {
    m_n = max;
  }

  void addThread(std::thread::id thread)
  {
    m_free.insert( std::pair<std::thread::id,T*>{ thread , nullptr } );
  }

  // Assign enough memory for
  void expandPool(int max)
  {
    m_pool = (T*) ::malloc(max*sizeof(T));
    shiftOffsets();
  }

  // Offset pointer in each thread to a different chunk if the memory pool.
  void shiftOffsets()
  {
    int counter = 0;
    for (auto& p : m_free) {
      p.second = m_pool + ( ( m_n / m_free.size() ) * counter );
      counter++;
    }
  }

  inline void* allocate(size_t size)
  {
    if ( m_pool == nullptr ) expandPool( m_n );
    m_free.find( std::this_thread::get_id() )->second++;
    return m_free.find( std::this_thread::get_id() )->second;
  }

  inline void free(void* deleted)
  {
    m_free.find( std::this_thread::get_id() )->second--;
  }
};

#endif