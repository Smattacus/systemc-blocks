#include "systemc.h"

SC_MODULE(mon) {
    sc_in<bool> A, B, F;
    sc_in<bool> clk;

    int time_elapsed;

    void monitor_changes() {

        std::cout << "T (ns)\tA\tB\tF" << std::endl;
        while (true) {
            std::cout << time_elapsed << "ns\t" << A.read() << "\t" << B.read() << "\t" << F.read() << std::endl;
            time_elapsed += 10 * SC_NS;
            wait();
        }
    }
    SC_CTOR(mon) {
        time_elapsed = 0;
        SC_THREAD(monitor_changes);
        sensitive << clk.pos();
    }
};