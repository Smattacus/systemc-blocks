#include "systemc.h"

#ifndef STACK_IF_H
#define STACK_IF_H

class stack_write_if : virtual public sc_interface {
    public : 
        virtual bool nb_write(char c) = 0;
        virtual void reset() = 0;
};

class stack_read_if : virtual public sc_interface {
    public :
        virtual bool nb_read(char& c) = 0;
        virtual void reset() = 0;
        virtual bool is_full() = 0;
        virtual bool not_empty() = 0;
};
#endif