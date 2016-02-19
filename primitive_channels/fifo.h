//
//  stack.h
//  SystemCTutorial
//
//  Created by Lukas Woodtli on 16.02.16.
//
//

#ifndef _FIFO_H_
#define _FIFO_H_

#include <systemc>

#include <iostream>

#include "fifo_if.h"

using namespace std;

class fifo : public sc_prim_channel,
              public fifo_in_if,
              public fifo_out_if
{
protected:
  int size;
  char* buf;
  int free;
  int ri;
  int wi;
  int num_readable;
  int num_read;
  int num_written;

  sc_event data_read_event;
  sc_event data_written_event;

public:
  explicit fifo(int size_ = 16)
    : sc_prim_channel(sc_gen_unique_name("my_fifo"))
  {
    size = size_;
    buf = new char[size];
    reset();                  
  }
    
  ~fifo()
  {
    delete [] buf;
  }

  int num_available() const
  {
    return num_readable - num_read;
  }

  int num_free() const
  {
    return size - num_readable - num_written;
  }

  void write(char c) // blocking write
  {
    if (num_free() == 0)
    {
      wait(data_read_event); // dynamic sensitivity
    }
    num_written++;
    buf[wi] = c;
    wi = (wi + 1) % size;
    free--;
    request_update();
  }

  void reset()
  {
    free = size;
    ri = 0;
    wi = 0;
  }

  void read (char& c)
  {
    if (num_available() == 0)
    {
      wait(data_written_event);
    }
    num_read++;
    c = buf[ri];
    ri = (ri + 1) % size;
    free++;
    request_update();
  }

  char read()
  {
    char c;
    read(c);
    return c;
  }

  void update()
  {
    if (num_read > 0)
    {
      data_read_event.notify(SC_ZERO_TIME);
    }
    if (num_written > 0)
    {
      data_written_event.notify(SC_ZERO_TIME);
    }
    num_readable = size - free;
    num_read = 0;
    num_written = 0;
  }
};


#endif /* _FIFO_H_ */
