#include "systemc"
#include "png_reader.h"
#include "sharpener.h"
#include "source.h"
#include "sink.h"

#define STRING_BUFFER_LENGTH 256

int sc_main(int args, char ** argv) {
    //Do some setup and debugging.
    std::cout << "Hello world!" << endl;
    // PNG_Reader test_reader;
    // char fname[STRING_BUFFER_LENGTH] = "/workspaces/systemc-blocks/src/sharpener/Vd-Orig.png";
    // test_reader.read_png(fname);
    // std::cout << "Width: " << test_reader.get_width() << " Height = " << test_reader.get_height() << std::endl;
    // std::cout << "First three rows:" << std::endl;
    // std::cout << "[ " << +test_reader.row_pointers[0][0] << " " << +test_reader.row_pointers[0][1] << " " << +test_reader.row_pointers[0][2] << "]" << std::endl;
    // std::cout << "[ " << +test_reader.row_pointers[1][0] << " " << +test_reader.row_pointers[1][1] << " " << +test_reader.row_pointers[1][2] << "]" << std::endl;
    // std::cout << "[ " << +test_reader.row_pointers[2][0] << " " << +test_reader.row_pointers[2][1] << " " << +test_reader.row_pointers[2][2] << "]" << std::endl;

    //Create signals
    std::cout << "Creating signals" << std::endl;
    sc_signal< sc_int<8> > input_red;
    sc_signal< sc_int<8> > input_green;
    sc_signal< sc_int<8> > input_blue;
    sc_signal< sc_int<8> > output_red;
    sc_signal< sc_int<8> > output_green;
    sc_signal< sc_int<8> > output_blue;
    sc_signal<bool> data_valid;
    sc_signal<bool> data_ack;
    sc_signal<bool> data_req;
    sc_signal<bool> data_ready;
    sc_clock clock("CLOCK", 10, SC_NS, 0.5, 0.0, SC_NS);


    // Hook everything up.
    std::cout << "Hooking up modules..." << std::endl;

    sharpener SHARPENER1("sharpener_one");
    SHARPENER1.in_red(input_red);
    SHARPENER1.in_green(input_green);
    SHARPENER1.in_blue(input_blue);
    SHARPENER1.data_valid(data_valid);
    SHARPENER1.data_ack(data_ack);
    SHARPENER1.out_red(output_red);
    SHARPENER1.out_green(output_green);
    SHARPENER1.out_blue(output_blue);
    SHARPENER1.data_req(data_req);
    SHARPENER1.data_ready(data_ready);
    SHARPENER1.CLK(clock);

    source SOURCE1("source");
    SOURCE1.data_req(data_req);
    SOURCE1.data_valid(data_valid);
    SOURCE1.in_red(input_red);
    SOURCE1.in_green(input_green);
    SOURCE1.in_blue(input_blue);
    SOURCE1.CLK(clock);

    sink SINK1("sink");
    SINK1.data_ack(data_ack);
    SINK1.data_ready(data_ready);
    SINK1.out_red(output_red);
    SINK1.out_green(output_green);
    SINK1.out_blue(output_blue);
    SINK1.CLK(clock);

    std::cout << "Start it!" << std::endl;
    sc_start();
    return 0;
};