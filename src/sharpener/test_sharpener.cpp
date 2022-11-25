#include "systemc.h"
#include "sharpener.h"
#include "png_reader.h"

#define STRING_BUFFER_LENGTH 256

int sc_main(int args, char ** argv) {
    std::cout << "Hello world!" << endl;
    PNG_Reader test_reader;
    char fname[STRING_BUFFER_LENGTH] = "/workspaces/systemc-blocks/src/sharpener/Vd-Orig.png";
    test_reader.read_png(fname);
    std::cout << "Width: " << test_reader.get_width() << " Height = " << test_reader.get_height() << std::endl;
    std::cout << "First three rows:" << std::endl;
    std::cout << "[ " << +test_reader.row_pointers[0][0] << " " << +test_reader.row_pointers[0][1] << " " << +test_reader.row_pointers[0][2] << "]" << std::endl;
    std::cout << "[ " << +test_reader.row_pointers[1][0] << " " << +test_reader.row_pointers[1][1] << " " << +test_reader.row_pointers[1][2] << "]" << std::endl;
    std::cout << "[ " << +test_reader.row_pointers[2][0] << " " << +test_reader.row_pointers[2][1] << " " << +test_reader.row_pointers[2][2] << "]" << std::endl;
    sc_start();
    return 0;
};