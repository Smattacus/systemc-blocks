#include <systemc>
using namespace sc_core;

void hello_simple() {
    std::cout << "Hello world without systemc!" << std::endl;
}

struct HelloWorld: sc_module {

    SC_CTOR(HelloWorld)
    {
        SC_METHOD(hello2);
    }
    void hello2(void){
        std::cout << "Hello world in systemc!" << std::endl;
    }

};

int main(int args, char **argv) {
    hello_simple();
    HelloWorld helloworld("helloworld");

    sc_start();
}