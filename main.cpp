#include <systemc.h>

#include "nand.h"
#include "exor.h"

class write_if : virtual public sc_interface {
public:
    virtual void write(char) = 0;
    virtual void reset() = 0;
};

class read_if : virtual public sc_interface {
public:
    virtual void read(char &) = 0;
    virtual int num_available() = 0;
};

class fifo : public sc_channel, public write_if, 
             public read_if {
public:
    fifo(sc_module_name name) : sc_channel(name),
                                num_elements(0), 
                                first(0) {}

    void write(char c) {
        if (num_elements == max)
            wait(read_event);

        data[(first + num_elements) % max] = c;
        ++ num_elements;
        write_event.notify();
    }

    void read(char &c) {
        if (num_elements == 0)
            wait(write_event);

        c = data[first];
        -- num_elements;
        first = (first + 1) % max;
        read_event.notify();
    }

    void reset() { num_elements = first = 0; }

    int num_available() { return num_elements;}

private:
    enum e { max = 10 };
    char data[max];
    int num_elements, first;
    sc_event write_event, read_event;
};

//class producer : public sc_module {
SC_MODULE(producer) {
 public:
    sc_port<write_if> out;

    SC_CTOR(producer){
        SC_THREAD(main);
    }

    void main() {
        const char *str =
            "Visit www.systemc.org and see what"
            "SystemC can do for you today!\n";

        while (*str)
            out->write(*str++);
    }
};

SC_MODULE(consumer) {
 public:
    sc_port<read_if> in;

    SC_CTOR(consumer) {
        SC_THREAD(main);
    }

    void main() {
        char c;
        cout << endl << endl;

        while (true) {
            in->read(c);
            cout << c << flush;
            /*
              if (in->num_available() == 1)
              cout << "<1>" << flush;
              if (in->num_available() == 9)
              cout << "<9>" << flush;

              cout << "time used:" << sc_time_stamp() 
              << "\n";         */
        }
    }
};

//class top : public sc_module {
SC_MODULE(top) {
   public:
     fifo *fifo_inst;
     producer *prod_inst;
     consumer *cons_inst;

     //     top(sc_module_name name) : sc_module(name) {
     SC_CTOR(top) {
       fifo_inst = new fifo("Fifo1");

       prod_inst = new producer("Producer1");
       prod_inst->out(*fifo_inst);

       cons_inst = new consumer("Consumer1");
       cons_inst->in(*fifo_inst);
     }
};

int sc_main (int argc , char *argv[]) {
   top top1("Top1");
   sc_start();

   return 0;
}
