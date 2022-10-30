#include "systemc.h"
#include "xor.h"
#include "stim.h"
#include "mon.h"

int sc_main(int args, char **argv) {
    sc_signal<bool> Asig, Bsig, Fsig;
    //Clock that has a 1ns delay on start of sim.
    sc_clock TestClk("TestClock", 10, SC_NS, 0.5, 1, SC_NS);

    stim Stimulus("Stimulus");
    mon Monitor("Monitor");

    exor2 DUT("DUT");

    Stimulus.A(Asig);
    Stimulus.B(Bsig);
    Stimulus.Clk(TestClk);

    Monitor.A(Asig);
    Monitor.B(Bsig);
    Monitor.F(Fsig);
    Monitor.clk(TestClk);

    DUT.A(Asig);
    DUT.B(Bsig);
    DUT.F(Fsig);

    sc_start();

    return 0;
};