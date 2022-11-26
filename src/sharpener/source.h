#include "systemc.h"

class source: sc_module {
    public:
        sc_in<bool> data_req;
        sc_out<bool> data_valid;
        sc_out<int> in_red;
        sc_out<int> in_green;
        sc_out<int> in_blue;

        sc_in_clk CLK;

        void entry();

        SC_CTOR(source)
        {
            SC_CTHREAD(entry, CLK.pos());
        }

};