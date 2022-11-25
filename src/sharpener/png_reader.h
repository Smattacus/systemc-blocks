#include "png.h"
#include "png_reader_if.h"

class PNG_Reader : public PNG_Interface {
    private:
        png_infop info_ptr;
        __uint32_t width, height;
    public:
        png_bytepp row_pointers;

        __uint32_t get_width() {
            return this->width;
        };

        __uint32_t get_height() {
            return this->height;
        };

        void read_png(char *file_name) {
            FILE *fp = fopen(file_name, "rb");
            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            this->info_ptr = png_create_info_struct(png_ptr);  
            png_init_io(png_ptr, fp);
            png_read_png(png_ptr, this->info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
            this->row_pointers = png_get_rows(png_ptr, this->info_ptr);
            this->width = png_get_image_width(png_ptr, this->info_ptr);
            this->height = png_get_image_height(png_ptr, this->info_ptr);
            png_destroy_read_struct(&png_ptr, NULL, NULL); 
            fclose(fp); 
        };

        void write_png(char *filename) {
            FILE *fp = fopen(filename, "wb");
            png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            png_init_io(png_ptr, fp);
            png_set_rows(png_ptr, info_ptr, row_pointers);
            png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
            png_destroy_write_struct(&png_ptr, &info_ptr);
            fclose(fp);
        }
};