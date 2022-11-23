#include "systemc.h"

struct source: sc_module {
    sc_in<bool> data_req;
    sc_out<bool> data_valid;
    sc_out<sc_int<8>> in_red;
    sc_out<sc_int<8>> in_green;
    sc_out<sc_int<8>> in_blue;

    sc_in_clk CLK;

    SC_CTOR(source)
    {
        SC_CTHREAD(entry, CLK.pos());
    }

    void entry();
};