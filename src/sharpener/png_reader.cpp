#include "png.h"
#include "png_reader.h"

class PNG_Reader {
    private:
        png_infop info_ptr;
    public:
        png_bytepp row_pointers;
        void read_png(char *filename) {

            FILE *fp_image = fopen("Vd-Orig.png", "rb");
            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            png_infop info_ptr = png_create_info_struct(png_ptr); 
            png_init_io(png_ptr, fp_image);
            png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
            row_pointers = png_get_rows(png_ptr, info_ptr);
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL); // <-- destroying the info_ptr (as well).
            fclose(fp);

        };
        void write_png(char *filename) {

        }
};