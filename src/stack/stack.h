#include "systemc.h"
#include "stack_if.h"

class stack :
    public sc_module,
    public stack_write_if,
    public stack_read_if
{
private:
    char data[20];
    int top;
public:
    stack(sc_module_name nm) : sc_module(nm), top(0) {};

    bool nb_write(char c) {
        if (top < 20)
        {
            this->data[this->top++] = c;
            return true;
        }
        return false;
    };

    void reset() {this->top = 0;};

    bool nb_read(char& c) {
        if (top >= 0){
            c = this->data[this->top--];
            if (top < 0) {
                top = 0;
                return false;
            }
            return true;
        }
        return false;
    }

    void register_port(sc_port_base& port_, const char* if_typename_)
    {
        cout << "Binding    " << port_.name() << " to " 
             << "interface; " << if_typename_ << endl;
    }

    bool is_full() {return top == 20;};

    bool not_empty() {
        return (top != 0);
        };

};