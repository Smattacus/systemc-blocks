#include "systemc.h"
#include "sharpener.h"

void sharpener::entry(){

    sc_int<32> input_memory[100][100][24];
    sc_int<32> output_memory[100][100][24];
    int im_width = 100;
    int im_height = 100;
    unsigned int index;

    while(true)
    {
        // Read in the image
        data_req.write(false);
        data_ready.write(false);
        index = 0;
        cout << endl << "Reading in samples..." << endl;
        while (index < 10000) {
            data_req.write(true);
            do {wait();} while (data_valid == true);
            input_memory[index] = { 
                in_red.read(),
                in_green.read(),
                in_blue.read()
            };
            index++;
            data_req.write(false);
            wait();
        }
        index = 0;

        // Process the data
        sc_int<32> kernel[3][3] = {
            0, -1, 0,
            -1, 5, -1,
            0, -1, 0
        };
        //For the first iteration, we'll do a brute force
        // computation.
        sc_int<32> calc_kernel[3][3] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0
        };
        sc_int<32> sharpened = 0;
        int im1, ip1, jm1, jp1;

        // Edge treatment: "reflect" aka "half sample symmetric"
        // The reflection point is half past the boundary:
        // 1 | 2 |||| 2 | 1
        // |||| is the image boundary.
        for (int i=0; i < 100; i++) {
            for (int j=0; j < 100; j++) {
                // Edge treatment
                im1 = (i - 1 < 0) ? i : i - 1;
                ip1 = (i + 1 >= 100) ? i : i + 1;

                jm1 = (j - 1 < 0) ? j : j - 1;
                jp1 = (j + 1 >= 100) ? j : j + 1;

                // Sharpen it
                // TODO: This is wrong; do this for each of RGB.
                calc_kernel[0, 0] = input_memory[im1][jm1] * kernel[0,0];
                calc_kernel[0, 1] = input_memory[im1][j] * kernel[0,1];
                calc_kernel[0, 2] = input_memory[im1][jp1] * kernel[0,2];

                calc_kernel[1, 0] = input_memory[i][jm1] * kernel[1,0];
                calc_kernel[1, 1] = input_memory[i][j] * kernel[1,1];
                calc_kernel[1, 2] = input_memory[i][jp1] * kernel[1,2];

                calc_kernel[2, 0] = input_memory[ip1][jm1] * kernel[2,0];
                calc_kernel[2, 1] = input_memory[ip1][j] * kernel[2,1];
                calc_kernel[2, 2] = input_memory[ip1][jp1] * kernel[2,2];

                // Put the final value in memory.
                sharpened = 0;
                for (int ii = 0; ii < 9; ii++) sharpened += calc_kernel[ii];
                output_memory[i][j] = sharpened;
            }
        }


        // Write out the data.
        cout << "Writing the transformed data..." << endl;
        int i = 0;
        while ( i < 10000){
            out_red.write(output_memory[i][0:8]);
            out_green.write(output_memory[i][8:16]);
            out_blue.write(output_memory[i][16:24]);
            data_ready.write(true);
            do {wait(); } while (!(data_ack == true));
            data_ready.write(false);
            i++;
            wait();
        }
        index = 0;
        cout << "Done..." << endl;
    }

}