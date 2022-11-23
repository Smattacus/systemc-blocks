// TODO: Make a class that handles the PNG read / write so we can
// keep a consistent level of abstraction in sink / source.
// Set it up this way:
// in main, instantiate the png_reader. Hand it to both the 
// source and sink.
// Source uses read() while the sink will use write()
#include "png.h"

class PNG_Reader {
    private:
        png_infop info_ptr;
    public:
        png_bytepp row_pointers; 
        void read_png(char *filename);
        void write_png(char * filename);
};