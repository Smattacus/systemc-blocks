#include "systemc.h"

class sharpener: sc_module {
    public:
        sc_in<sc_int<8>> in_red;
        sc_in<sc_int<8>> in_green;
        sc_in<sc_int<8>> in_blue;

        sc_in<bool> data_valid;
        sc_in<bool> data_ack;

        sc_out<sc_int<8>> out_red;
        sc_out<sc_int<8>> out_green;
        sc_out<sc_int<8>> out_blue;
        
        sc_out<bool> data_req;
        sc_out<bool> data_ready;

        sc_in_clk CLK;

        SC_CTOR(sharpener){
            SC_CTHREAD(entry, CLK.pos());
        };

        void entry();

        sc_int<9> sharpen_pixel_3x3kernel(int, int, sc_int<9> [][100], sc_int<9> [][3]);


};

