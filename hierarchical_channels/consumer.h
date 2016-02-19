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

#include "stack_if.h"

class consumer : public sc_module
{
public:
    sc_port<stack_read_if> in;
    sc_in<bool> clock;
    
    void do_reads()
    {
        char character;
        while (true)
        {
            wait(); // for clock edge
            if (in->nb_read(character))
            {
                cout << "R " << character << " at " << sc_time_stamp() << endl;
            }
        }
    }
    
    SC_CTOR(consumer)
    {
        SC_THREAD(do_reads);
        sensitive << clock.pos();
    }
    
};

#endif /* consumer_h */
