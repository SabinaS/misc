 #include "debayer.h"
 
 #define PIXEL_MAX 65535
     
 static u16 compute_and_clamp_pixel(
         u16 pos,
         u16 neg)
 {   
     if (pos < neg)
     {   
         return 0;
     }
     else
     {
         const u16 pixel = (pos - neg) >> 3;
         if (pixel > PIXEL_MAX) { return PIXEL_MAX; }
         else { return pixel; }
     }
 }
 
 /*
  * This version handles masks with fractional negative values. In those
  * cases truncating before subtraction does not generally yield the
  * same result as truncating after subtraction.  The negative value
  * is using weights in units of 1/16ths so that the one-half portions
  * are retained.
  */
 static u16 compute_and_clamp_pixel_fractional_neg(
         u16 pos,
         u16 neg)
 {
     /*
      * The positive portion is converted to u32 prior to doubling because
      * otherwise some of the weights could yield overflow. At that point,
      * all weights are effectively 16x their actual value, so combining
      * the positive and negative portions and then shifting by four bits
      * yields the equivalent of a floor() applied to the result of the
      * full precision convolution.
      */
     const u32 pos_u32 = ((u32) pos) << 1;
     const u32 neg_u32 = (u32) neg;
     if (pos_u32 < neg_u32)
     {   
         return 0;
     }
     else
     {
         const u16 pixel = (u16) ((pos_u32 - neg_u32) >> 4);
         if (pixel > PIXEL_MAX) { return PIXEL_MAX; }
         else { return pixel; }
     }
 }   
 
 u16 debayer::interp_G_at_RRR_or_G_at_BBB(
         u32 row,
         u32 col)
 {
     /*
      * The mask to interpolate G at R or B is:
      *
      * [0  0 -1  0  0
      *  0  0  2  0  0
      * -1  2  4  2 -1
      *  0  0  2  0  0
      *  0  0 -1  0  0]/8
      */ 
     const u16 pos =
         2 * bayer_img[row-1][col] +
         2 * bayer_img[row][col-1] +
         4 * bayer_img[row][col] +
         2 * bayer_img[row][col+1] +
         2 * bayer_img[row+1][col];
     const u16 neg =
         bayer_img[row][col+2] +
         bayer_img[row-2][col] +
         bayer_img[row][col-2] +
         bayer_img[row+2][col];
         
     return compute_and_clamp_pixel(pos, neg);
 }   
 
 u16 debayer::interp_R_at_GRB_or_B_at_GBR(
         u32 row,
         u32 col)
 {
     /*
      * [0  0 0.5 0  0
      *  0 -1  0 -1  0
      * -1  4  5  4 -1
      *  0 -1  0 -1  0
      *  0  0 0.5 0  0]/8;
      */
     const u16 pos =
         ((bayer_img[row-2][col] + bayer_img[row+2][col]) >> 1) +
         4 * bayer_img[row][col-1] +
         5 * bayer_img[row][col] +
         4 * bayer_img[row][col+1];
     const u16 neg =
         bayer_img[row-1][col-1] +
         bayer_img[row-1][col+1] +
         bayer_img[row][col-2] +
         bayer_img[row][col+2] +
         bayer_img[row+1][col-1] +
         bayer_img[row+1][col+1];
         
     return compute_and_clamp_pixel(pos, neg);
 }   
 
 u16 debayer::interp_R_at_GBR_or_B_at_GRB(
         u32 row,
         u32 col)
 {
     /*
      * [0  0 -1  0  0
      *  0 -1  4 -1  0
      * 0.5 0  5  0 0.5
      *  0 -1  4 -1  0
      *  0  0 -1 0  0]/8;
      */
     const u16 pos =
         4 * bayer_img[row-1][col] +
         ((bayer_img[row][col-2] + bayer_img[row][col+2]) >> 1) +
         5 * bayer_img[row][col] +
         4 * bayer_img[row+1][col];
     const u16 neg =
         bayer_img[row-2][col] +
         bayer_img[row-1][col-1] +
         bayer_img[row-1][col+1] +
         bayer_img[row+1][col-1] +
         bayer_img[row+1][col+1] +
         bayer_img[row+2][col];
 
     return compute_and_clamp_pixel(pos, neg);
 }
 
 u16 debayer::interp_R_at_BBB_or_B_at_RRR(
         u32 row,
         u32 col)
 {
     /*
      * [0  0 -1.5 0  0
      *  0  2  0  2  0
      * -1.5 0  6  0 -1.5
      *  0  2  0  2  0
      *  0  0 -1.5 0  0]/8;
      */
     const u16 pos =
         2 * bayer_img[row-1][col-1] +
         2 * bayer_img[row-1][col+1] +
         6 * bayer_img[row][col] +
         2 * bayer_img[row+1][col-1] +
         2 * bayer_img[row+1][col+1];
     const u16 neg =
         (3 * bayer_img[row-2][col] +
          3 * bayer_img[row][col-2] +
          3 * bayer_img[row][col+2] +
          3 * bayer_img[row+2][col]);
 
     return compute_and_clamp_pixel_fractional_neg(pos, neg);
 }
 
 void debayer::wami_debayer(int rows, int cols)
 {
     /**
      * TODO
      * Implement wami_debayer() starting from previous assignments.
      * HINT: we want CtoS to know the maximum number of iterations
      * of each loop at compile time; however, since this time the
      * size of the image can change, make sure your code only runs
      * the necessary iterations.
      */
 
     int row = 0;
     int col = 0;
 
     for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].r = bayer_img[row][col];
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }//end for loop
 
     /* Green pixels */
 
     for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].g = bayer_img[row][col];
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
     for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].g = bayer_img[row][col];
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
     for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].g = interp_G_at_RRR_or_G_at_BBB(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
       //end green pixels
 
     /* Blue pixels */
 
     for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].g = interp_G_at_RRR_or_G_at_BBB(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
 
     for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].b = bayer_img[row][col];
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
     for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].b = interp_R_at_GRB_or_B_at_GBR(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
     for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].b = interp_R_at_GBR_or_B_at_GRB(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
     for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].b = interp_R_at_BBB_or_B_at_RRR(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
     //end blue pixels
 
     /* Red pixels */
 
     for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].r = interp_R_at_BBB_or_B_at_RRR(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
     for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].r = interp_R_at_GBR_or_B_at_GRB(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
 
     for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2){
         for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2){
             debayer_img[row-PAD][col-PAD].r = interp_R_at_GRB_or_B_at_GBR(
                     row, col);
             if(col+2>=size){
                 col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
             }
         }
         if(row+2>=size){
             row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
         }
     }
     //end red pixels
 
 
 }
 
  void debayer::config_debayer()
 {
     // Initialization at reset
     /* TODO */
     size.write(0);
     init_done.write(false);
     // Read configuration until done
     //wait(); //extra wait
     do{wait();} while (!conf_size.read());
     size.write(conf_size.read());
 
     // Let other threads run then do nothing
     init_done.write(true);
     //wait(); //extra wait
     do{wait(); } while (true);
 }
 
 
 void debayer::load_input()
 {
 RESET_LOAD:
     // Initialization at reset
     /* TODO */
     input_done.write(false);
     rd_request.write(false);
     rd_index.write(0);
     rd_length.write(0);
     bufdin.reset_get();
     // Wait for init_done from configuration and read image size
     //wait(); //extra wait
     do{wait(); } while (!init_done.read());
 
 LOAD_INPUT_WHILE:
     bool finished_load = false;
     while(true) {
 
         // If the entire image has been loaded wait for reset from TB
         if(finished_load){
             //wait();
             do{wait(); } while(true);
         }
         // Send DMA request
         // Notice that this implementation is still reading the entire image in one burst
         int image_size = size.read();
         rd_request.write(true);
         rd_index.write(0);
         rd_length.write(image_size*image_size);
 
         // 4-phase handshake load_input() with TB
         //wait(); //extra wait
         do{wait(); } while (!rd_grant.read() );
         rd_request.write(false);
         //wait(); //extra wait
         do{wait(); } while (rd_grant.read() );
 
         // Loop over the entire array to get the image pixels
         // Make sure CtoS knows the maximum number of iterations, but
         // do not run useless iterations!
         for (int i = 0; i< image_size; i++){
             for( int j = 0; j < image_size; j++){
                 bayer_img[i][j] = (u16) bufdin.get();
             }
         }
         // 4-phase handshake load_input() with process_debayer()
         input_done.write(true);
         //wait(); //extra wait
         do{wait(); } while(!process_start.read());
 
         input_done.write(false);
         //wait(); //extra wait
         do{wait(); } while( process_start.read());
 
         finished_load = true;
     }
 }
 
 
 
 void debayer::process_debayer()
 {
     // Initialization at reset
     process_done.write(false);
     process_start.write(false);
     // Wait for init_done from configuration and read image size
 
 DEBAYER_WHILE:
 
     bool finished_load = false;
 
     while (true) {
 
         // If the entire image has been processed wait for reset from TB
         if(finished_load){
             //wait(); //extra wait
             do{wait();} while(true);
         }
         // 4-phase handshake process_debayer() with load_input()
         //wait(); //extra wait
         do{wait(); } while(!input_done.read());
         process_start.write(true);
 
         //wait(); //extra wait
         do{wait(); } while(process_done.read() );
         process_done.write(false);
 
         // Call wami_debayer(). Notice rows is the size of the current image!
         int rows = size.read(); //getting the size of the current image
         wami_debayer(rows, rows);
 
         // 4-phase handshake process_debayer() with store_output()
 
         process_done.write(true);
         //wait(); //extra wait
         do{wait(); } while(!output_start.read());
 
         process_done.write(false);
         //wait();
         //wait();
         do{wait();} while(output_start.read());
         finished_load = true;
     }
 }
 
 void debayer::store_output()
 {
     // Initialization at reset
     /* TODO reset writes */
     wr_request.write(false);
     wr_index.write(0);
     wr_length.write(0);
 
     debayer_done.write(false);
     output_start.write(false);
     bufdout.reset_put();
 
     // Wait for init_done from configuration and read image size
     //wait(); //extra wait
     do{wait();} while(!init_done.read());
 
 STORE_OUTPUT_WHILE:
     bool finished_send = false;
     while(true) {
 
         // If the entire image has been sent to TB
         // set debayer_done and wait for reset from TB
         if(finished_send){
             debayer_done.write(true);
             //wait(); //extra wait
             do{wait();} while(true);
         }
         // 4-phase handshake store_output() with process_debayer()
         //wait(); //extra wait
         do{wait();} while(!process_done.read());
         output_start.write(true);
 
         //wait(); //extra wait
         do{wait();} while(process_done.read());
         output_start.write(false);
 
 
         // Send DMA request
         int image_size = size.read();
 
         wr_request.write(true);
         wr_index.write(0);
         wr_length.write((image_size)*(image_size));
 
         // 4-phase handshake store_output() with TB
         //wait(); //extra wait
         do{wait();} while(!wr_grant.read());
         wr_request.write(false);
 
         //wait(); //extra wait
         do{wait();} while(wr_grant.read());
         wr_request.write(true); //??
 
         // Loop over the entire array to send the output image pixels
         // Make sure CtoS knows the maximum number of iterations, but
         // do not run useless iterations!
         for(int i=0; i< ((image_size -2)*PAD); i++){
             for(int j = 0; j < ((image_size-2)*PAD); j++){
                 bufdout.put(debayer_img[i][j]);
                 wait(); //extra wait??
             }
             wait(); //extra wait??
         }
 
         finished_send = true;
     }
 }
 
 // Export the module name for CtoS
 #ifdef __CTOS__
 SC_MODULE_EXPORT(debayer)
 #endif





