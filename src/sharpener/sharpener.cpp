#include "systemc.h"
#include "sharpener.h"

int sharpener::sharpen_pixel_3x3kernel(int i, int j, int memory[][100], int kernel[][3]) {
    /*
    Sharpens the given pixel in the memory. This is a brute force routine.
    It assumes that the kernel is 3x3.

    Edge treatment: "reflect" aka "half sample symmetric"
    The reflection point is half past the boundary:
    1 | 2 |||| 2 | 1
    |||| is the image boundary.
    */

    int calc_kernel[3][3] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    int im1 = (i - 1 < 0) ? i + 1 : i - 1;
    int ip1 = (i + 1 >= 100) ? i -1 : i + 1;

    int jm1 = (j - 1 < 0) ? j + 1 : j - 1;
    int jp1 = (j + 1 >= 100) ? j - 1 : j + 1;

    // Sharpen it
    calc_kernel[0][0] = memory[im1][jm1] * kernel[0][0];
    calc_kernel[0][1] = memory[im1][j] * kernel[0][1];
    calc_kernel[0][2] = memory[im1][jp1] * kernel[0][2];

    calc_kernel[1][ 0] = memory[i][jm1] * kernel[1][0];
    calc_kernel[1][ 1] = memory[i][j] * kernel[1][1];
    calc_kernel[1][ 2] = memory[i][jp1] * kernel[1][2];

    calc_kernel[2][ 0] = memory[ip1][jm1] * kernel[2][0];
    calc_kernel[2][ 1] = memory[ip1][j] * kernel[2][1];
    calc_kernel[2][ 2] = memory[ip1][jp1] * kernel[2][2];

    // Put the final value in memory.
    int sharpened = 0;
    for (int ii = 0; ii < 3; ii++)
        for (int jj = 0; jj < 3; jj++) 
            sharpened += calc_kernel[ii][jj];
    return sharpened;

};

void sharpener::entry() {

    std::cerr << "Inside sharpener!" << std::endl;

    int im_height = 100;
    int im_width = 300;
    auto input_memory_red = new int[100][100];
    auto input_memory_green = new int[100][100];
    auto input_memory_blue = new int[100][100];
    auto output_memory_red = new int[100][100];
    auto output_memory_green = new int[100][100];
    auto output_memory_blue = new int[100][100];
    unsigned int index_i, index_j;

    std::cout << "Sharpener Initialized!" << std::endl;


    while(true)
    {
        // Read in the image
        data_req.write(false);
        data_ready.write(false);
        index_i = 0;
        index_j = 0;
        cout << endl << "Reading in samples..." << endl;
        while (index_i < 100 && index_j < 100) {
            index_i %= 100;
            data_req.write(true);
            do {wait();} while (!(data_valid == true));
            input_memory_red[index_i][index_j] = in_red.read();
            input_memory_green[index_i][index_j] = in_green.read();
            input_memory_blue[index_i][index_j] = in_blue.read();
            index_j++;
            if (index_j == 100 && index_i == 100){
                break;
            } 
            else if (index_j == 100) {
                index_j = 0;
                index_i++;
            }
            data_req.write(false);
            wait();
        };
        index_i = 0;
        index_j = 0;
        cout << "All samples read. Sharpening..." << endl;
        //For the first iteration, we'll do a brute force
        // computation.
        int kernel[3][3] = {
            0, -1, 0,
            -1, 5, -1,
            0, -1, 0
        };
        // Process the data
        int sharpened = 0;
        for (int i=0; i < 100; i++) {
            for (int j=0; j < 100; j++) {
                output_memory_red[i][j] = this->sharpen_pixel_3x3kernel(i, j, input_memory_red, kernel);
                output_memory_green[i][j] = this->sharpen_pixel_3x3kernel(i, j, input_memory_green, kernel);
                output_memory_blue[i][j] = this->sharpen_pixel_3x3kernel(i, j, input_memory_blue, kernel);
            }
        }


        // Write out the data.
        cout << "Writing the transformed data..." << endl;
        index_i = 0;
        index_j = 0;
        while ( index_i < 100 && index_j < 100){
            index_i %= 100;
            out_red.write(output_memory_red[index_i][index_j]);
            out_green.write(output_memory_green[index_i][index_j]);
            out_blue.write(output_memory_blue[index_i][index_j]);
            data_ready.write(true);
            do {wait(); } while (!(data_ack == true));
            data_ready.write(false);
            index_j++;
            if (index_j == 100) {
                index_j = 0;
                index_i++;
            }
            wait();
        }
        index_i = 0;
        index_j = 0;
        cout << "Done..." << endl;
    }

    delete input_memory_red;
    delete input_memory_green;
    delete input_memory_blue;
    delete output_memory_red;
    delete output_memory_green;
    delete output_memory_blue;

};