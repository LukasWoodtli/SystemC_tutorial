#include <systemc>

#include "producer.h"
#include "consumer.h"
#include "fifo.h"

int sc_main (int argc , char *argv[]) {

    sc_clock ClkFast("ClkFast", 100, SC_NS);
    sc_clock ClkSlow("ClkSlow", 50, SC_NS);
    
    fifo Fifo1;
    
    producer P1("P1");
    P1.out(Fifo1);
    P1.clock(ClkFast);
    
    
    consumer C1("C1");
    C1.in(Fifo1);
    C1.clock(ClkSlow);
    
    sc_start(5000, SC_NS);
    
    return 0;
}
