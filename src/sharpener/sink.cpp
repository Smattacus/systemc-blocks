#include "sink.h"

#include "systemc.h"
#include "png_reader.h"

void sink::entry() {
    FILE *output_image;

    PNG_Reader input_reader;
    PNG_Reader reference_image;

    char ref_image_name[256] = "/workspaces/systemc-blocks/src/sharpener/Vd-Sharp_reference.png";
    char outfile[256] = "/workspaces/systemc-blocks/src/sharpener/sharpener_output.png";

    std::cout << "Loading ref image..." << endl;
    reference_image.read_png(ref_image_name);
    std::cout << "Opening output image..." << endl;
    input_reader.read_png(outfile);
    std::cout << "Output image opened..." << endl;

    int i_rows = 0;
    int j_rows = 0;

    data_ack.write(false);

    std::cout << "Sink entering while loop..." << std::endl;

    while(true)
    {
        while (!(data_ready == true)) {wait(); };
        if (i_rows >= 100) {
            std::cout << "Done reading image. Stopping simulation" << std::endl;
            break;
        }
        input_reader.row_pointers[i_rows][0] = out_red.read();
        input_reader.row_pointers[i_rows][1] = out_green.read();
        input_reader.row_pointers[i_rows][2] = out_blue.read();
        std::cout << "i = " << i_rows << "; Expected over calculated RGB:" << std::endl;
        std::cout << "R = " << +reference_image.row_pointers[i_rows][0] << " G = " << +reference_image.row_pointers[i_rows][1] << " B = " << +reference_image.row_pointers[i_rows][2] << std::endl;
        std::cout << "R = " << +input_reader.row_pointers[i_rows][0] << " G = " << +input_reader.row_pointers[i_rows][1] << " B = " << +input_reader.row_pointers[i_rows][2] << std::endl;
        data_ack.write(true);
        while (!(data_ready == false)) {wait();};
        data_ack.write(false);
        i_rows++;
    }
    std::cout << "Writing to file: " << outfile << std::endl;
    input_reader.write_png(outfile);
    std::cout << "Done filewriting!" << std::endl;
    sc_stop();
    while (true) {wait();};

}