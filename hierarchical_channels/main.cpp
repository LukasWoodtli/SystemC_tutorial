#include <systemc>

#include "producer.h"
#include "consumer.h"
#include "stack.h"

int sc_main (int argc , char *argv[]) {

    sc_clock ClkFast("ClkFast", 100, SC_NS);
    sc_clock ClkSlow("ClkSlow", 50, SC_NS);
    
    stack Stack1("S1");
    
    producer P1("P1");
    P1.out(Stack1);
    P1.clock(ClkFast);
    
    
    consumer C1("C1");
    C1.in(Stack1);
    C1.clock(ClkSlow);
    
    sc_start(5000, SC_NS);
    
    return 0;
}
