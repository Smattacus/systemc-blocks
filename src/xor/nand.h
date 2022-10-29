#include "systemc.h"

SC_MODULE(nand2)
{
    sc_in<bool> A, B;
    sc_out<bool> F;

    void do_nand2()
    {
        F.write( !(A.read() && B.read()));
    }

    SC_CTOR(nand2) {
        SC_METHOD(do_nand2);
        sensitive << A << B;
    }

};