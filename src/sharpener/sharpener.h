#include "systemc.h"

class sharpener: sc_module {
    public:
        sc_in<int> in_red;
        sc_in<int> in_green;
        sc_in<int> in_blue;

        sc_in<bool> data_valid;
        sc_in<bool> data_ack;

        sc_out<int> out_red;
        sc_out<int> out_green;
        sc_out<int> out_blue;
        
        sc_out<bool> data_req;
        sc_out<bool> data_ready;

        sc_in_clk CLK;

        SC_CTOR(sharpener){
            SC_CTHREAD(entry, CLK.pos());
        };

        void entry();

        int sharpen_pixel_3x3kernel(int, int, int [][100], int [][3]);


};

