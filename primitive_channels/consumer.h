//
//  consumer.h
//  SystemCTutorial
//
//  Created by Lukas Woodtli on 16.02.16.
//
//

#ifndef consumer_h
#define consumer_h


#include <systemc.h>

#include <iostream>

#include "fifo_if.h"

class consumer : public sc_module
{
public:
    sc_port<fifo_in_if> in;
    sc_in<bool> clock;
    
    void do_reads()
    {
        char character;
        while (true)
        {
            wait(); // for clock edge
            in->read(character);
        }
    }
    
    SC_CTOR(consumer)
    {
        SC_THREAD(do_reads);
        sensitive << clock.pos();
    }
    
};

#endif /* consumer_h */
