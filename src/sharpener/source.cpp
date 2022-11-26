#include "systemc.h"
#include "source.h"

#include "png_reader.h"

void source::entry() {

    std::cout << "Beginning source" << std::endl;

    FILE *input_image;

    data_valid.write(false);

    PNG_Reader input_reader;
    char infile[256] = "/workspaces/systemc-blocks/src/sharpener/Vd-Orig.png";
    input_reader.read_png(infile);

    int i_rows = 0;
    int j_col = 0;

    std::cout << "Source entering while loop" << std::endl;

    while(true) 
    {
        while (!(data_req == true)) {wait(); };
        if (i_rows >= input_reader.get_height()) {
            std::cout << "Input stream is done! Source will return control to the kernel." << std::endl;
            break;
        }
        in_red.write(input_reader.row_pointers[i_rows][j_col++]);
        in_green.write(input_reader.row_pointers[i_rows][j_col++]);
        in_blue.write(input_reader.row_pointers[i_rows][j_col++]);
        if (j_col >= (input_reader.get_width() * 3)) {
            j_col = 0;
            i_rows++;
        }
        data_valid.write(true);
        while (!(data_req == false)) {wait(); };
        data_valid.write(false);
        wait();
    };
    while (true) {wait();};
};