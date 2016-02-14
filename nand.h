#ifndef _NAND_H__
#define _NAND_H__

#include <systemc.h>

SC_MODULE(nand) {
  sc_in<bool> A, B;
  sc_out<bool> F;

  void do_it() {
    F.write(!(A.read() && B.read()));
  }

  SC_CTOR(nand) {
    SC_METHOD(do_it);
    sensitive << A << B;
  }

};

#endif /* _NAND_H__ */
