#include "systemc.h"
#include "source.h"

#include "png_reader.h"

void source::entry() {
    FILE *input_image;

    data_valid.write(false);

    PNG_Reader input_reader;
    char infile[256] = "/workspaces/systemc-blocks/src/sharpener/Vd-Orig.png";
    input_reader.read_png(infile);

    int i_rows = 0;

    while(true) 
    {
        while (!(data_req == true)) {wait(); };
        if (i_rows >= input_reader.get_height()) {
            std::cout << "Input stream is done! Source will return control to the kernel." << std::endl;
            sc_stop();
            break;
        }
        in_red.write(input_reader.row_pointers[i_rows][0]);
        in_green.write(input_reader.row_pointers[i_rows][1]);
        in_red.write(input_reader.row_pointers[i_rows][2]);
        data_valid.write(true);
        while (!(data_req == true)) {wait(); };
        data_valid.write(false);
        wait();
    };
};