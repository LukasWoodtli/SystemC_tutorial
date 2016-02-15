//
//  stim.h
//  SystemCTutorial
//
//  Created by Lukas Woodtli on 15.02.16.
//
//

#ifndef stim_h
#define stim_h

#include <systemc>

#include <iostream>

using namespace std;

SC_MODULE(stim)
{
    sc_out<bool> A, B;
    sc_in<bool> Clk;
    
    void stimGen()
    {
        A.write(false);
        B.write(false);
        wait();
        A.write(false);
        B.write(true);
        wait();
        A.write(true);
        B.write(false);
        wait();
        A.write(true);
        B.write(true);
        wait();
        sc_stop();
    }
    
    SC_CTOR(stim)
    {
        cout << "Construction of stim: " << name() << endl;
        SC_THREAD(stimGen);
        sensitive << Clk.pos();
    }
};


#endif /* stim_h */
