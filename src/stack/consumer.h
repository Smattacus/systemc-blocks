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
        int i = 0;
        while (true)
        {
            wait();
            if (in->is_full())
            {
                cout << "we are full!" << endl;
                while (in -> nb_read(output[i++])) {};
                cout << "i = " << i << " Read '" << output << "' at " << sc_time_stamp() << endl;
                i = 0;
            }
        }
    }
    SC_CTOR(consumer)
    {
        SC_THREAD(do_reads);
        sensitive << Clock.pos();
    }
};