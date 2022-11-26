#include "systemc.h"

class sink: sc_module {
    public:
        sc_in<bool> data_ready;
        sc_out<bool> data_ack;

        sc_in<int> out_red;
        sc_in<int> out_green;
        sc_in<int> out_blue;

        sc_in_clk CLK;

        void entry();

        SC_CTOR(sink)
        {
            SC_CTHREAD(entry, CLK.pos());
        };

};