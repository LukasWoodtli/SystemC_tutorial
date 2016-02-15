#include <systemc>

#include <iostream>

#include "nand.h"

using namespace std;

SC_MODULE(exor) {
  sc_in<bool> A, B;
  sc_out<bool> F;

  nand n1, n2, n3, n4;

  sc_signal<bool> S1, S2, S3;

  SC_CTOR(exor) : n1("N1"), n2("N2"), n3("N3"), n4("N4") {
    
      cout << "Construction of EXOR: " << name() << endl;
    
    n1.A(A);
    n1.B(B);
    n1.F(S1);

    n2 << A << S1 << S2;

    n3(S1);
    n3(B);
    n3(S3);

    n4 << S2 << S3 << F;
  }
};


