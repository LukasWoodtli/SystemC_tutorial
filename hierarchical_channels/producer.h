//
//  producer.h
//  SystemCTutorial
//
//  Created by Lukas Woodtli on 16.02.16.
//
//

#ifndef producer_h
#define producer_h


#include <systemc.h>

#include <iostream>

#include "stack_if.h"

class producer : public sc_module
{
public:
    sc_port<stack_write_if> out;
    sc_in<bool> clock;
    
    void do_writes()
    {
        int i = 0;
        char* test_string = "Hello, this will be reversed...";
        while (true)
        {
            wait(); // for clock edge
            if (out->nb_write(test_string[i]))
            {
                cout << "W " << test_string[i] << " at " << sc_time_stamp() << endl;
            }
            i = (i+1) % strlen(test_string);
        }
    }
    
    SC_CTOR(producer)
    {
        SC_THREAD(do_writes);
        sensitive << clock.pos();
    }
    
};

#endif /* producer_h */
