#include "sink.h"

#include "systemc.h"
#include "png_reader.h"

void sink::entry() {
    FILE *output_image;

    PNG_Reader input_reader;
    PNG_Reader reference_image;
    char ref_image_name[256] = "/workspaces/systemc-blocks/src/sharpener/Vd-Sharp_reference.png";
    char outfile[256] = "/workspaces/systemc-blocks/src/sharpener/sharpener_output.png"
    reference_image.read_png(ref_image_name);
    input_reader.read_png(outfile);

    int i_rows = 0;

    data_ack.write(false);

    while(true)
    {
        while (!(data_ready == true)) {wait(); };
        if (i_rows >= 100) {
            std::cout << "Done reading image. Stopping simulation" << std::endl;
            break;
        }
        input_reader.row_pointers[i_rows][0] = out_red.read();
        input_reader.row_pointers[i_rows][1] = out_green.read();
        input_reader.row_pointers[i_rows][2] = out_green.blue();
        data_ack.write(true);
        while (!(data_ready == false)) {wait();};
        data_ack.write(false);
        i_rows++;
    }
    std::cout << "Writing to file: " << filename << std::endl;
    input_reader.write_png(filename);
    std::cout << "Done filewriting!" << std::endl;
    while (true) {wait();};

}