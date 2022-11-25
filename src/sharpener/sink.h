#include "systemc.h"

class sink: sc_module {
    public:
        sc_in<bool> data_ready;
        sc_out<bool> data_ack;

        sc_in<sc_int<8>> out_red;
        sc_in<sc_int<8>> out_green;
        sc_in<sc_int<8>> out_blue;

        sc_in_clk CLK;

        SC_CTOR(sink)
        {
            SC_CTHREAD(entry, CLK.pos());
        };

        void entry();
};