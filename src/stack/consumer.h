#include "systemc.h"
#include "stack_if.h"

class consumer : public sc_module
{
    public:
    sc_port<stack_read_if> in;
    sc_in<bool> Clock;

    void do_reads()
    {
        char output[21];
        output[21] = '\0';
        for (int j=0; j < 21; j++) output[j] = ' ';
        int i = 0;
        while (true)
        {
            wait();
            if (in->nb_read(output[i++])){
                cout << "R " << output[i-1] << " at " << sc_time_stamp() << endl;
            }
            i = i % 20;
        }
    }
    SC_CTOR(consumer)
    {
        SC_THREAD(do_reads);
        sensitive << Clock.pos();
    }
};