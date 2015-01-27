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
	 * Implement wami_debayer() starting from previous assignments.
	 * HINT: we want CtoS to know the maximum number of iterations
	 * of each loop at compile time; however, since this time the
	 * size of the image can change, make sure your code only runs
	 * the necessary iterations.
	 */
	int row, col = 0;

    for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
            debayer_img[row-PAD][col-PAD].r = bayer_img[row][col];
            if(col+2>=size){
                col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
            }
        }
        if(row+2>=size){
            row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
        }
    }

    /* Copy top-right green pixels through directly */
    for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
            debayer_img[row-PAD][col-PAD].g = bayer_img[row][col];
            if(col+2>=size){
                col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
            }
        }
        if(row+2>=size){
            row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
        }
    }

    /* Copy bottom-left green pixels through directly */
    for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
            debayer_img[row-PAD][col-PAD].g = bayer_img[row][col];
            if(col+2>=size){
                col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
            }
        }
        if(row+2>=size){
            row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
        }
    }

    /* Copy blue pixels through directly */
    for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
            debayer_img[row-PAD][col-PAD].b = bayer_img[row][col];
            if(col+2>=size){
                col = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
            }
        }
        if(row+2>=size){
            row = WAMI_DEBAYER_IMG_NUM_COLS-PAD;
        }
    }

    /* Interpolate green pixels at red pixels */
    for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

    /* Interpolate green pixels at blue pixels */
    for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

    /* Interpolate red pixels at green pixels, red row, blue column */
    for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

    /* Interpolate blue pixels at green pixels, blue row, red column */
    for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

    /* Interpolate red pixels at green pixels, blue row, red column */
    for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

    /* Interpolate blue pixels at green pixels, red row, blue column */
    for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

    /* Interpolate red pixels at blue pixels, blue row, blue column */
    for (row = PAD+1; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD+1; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

    /* Interpolate blue pixels at red pixels, red row, red column */
    for (row = PAD; row < WAMI_DEBAYER_IMG_NUM_ROWS-PAD; row += 2)
    {
        for (col = PAD; col < WAMI_DEBAYER_IMG_NUM_COLS-PAD; col += 2)
        {
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

}


void debayer::config_debayer()
{
RESET:
	    cout << "RESET" << endl;
	
            size.write(0);
            init_done.write(false);

	
            do{wait();}while(!conf_size.read()); //wait until data available
            size.write(conf_size.read());

	
	init_done.write(true);
	do{wait();}while(true);
}



void debayer::load_input()
{
RESET_LOAD:
	
            input_done.write(false);
            rd_request.write(false);
            rd_index.write(0);
            rd_length.write(0);
            bufdin.reset_get();

	
	    do{wait();} while(!init_done.read());

LOAD_INPUT_WHILE:
            bool done = false;
	while(true) {

		
                        if(done){ //TODO change
			    do{wait();}while(true);
                        }

                        int dim = size.read();
		
                        rd_request.write(true); //phase 1 -> go high
                        
                        rd_index.write(0); //start index
                        rd_length.write(dim*dim); //size of bayer image


		
                        do{wait();}while(!rd_grant.read()); //phase 2 -> wait for ack
                        rd_request.write(false); // phase 3 -> go low
                        do{wait();}while(rd_grant.read()); //phase 4 -> wait for low

		
                        for(int i =0;i<dim;i++){
				for(int j=0;j<dim;j++){
                            		bayer_img[i][j] = (u16) bufdin.get(); // blocking
                            	}	
                        }


		
                        input_done.write(true); //1
                        do{wait();}while(!process_start.read());  //2
                        input_done.write(false); //3
                        do{wait();}while(process_start.read());  //4
                        done = true;
	}
}




void debayer::process_debayer()
{
	
            process_start.write(false);
            process_done.write(false);

	
            do{wait();}while(!init_done.read());

DEBAYER_WHILE:
            bool done = false;
	while (true) {

		
                        if(done){ //TODO change
                            do{wait();}while(true);
                        }

		
                        do{wait();}while(!input_done.read()); //1
                        process_start.write(true); //2
                        do{wait();}while(input_done.read()); //3
                        process_start.write(false);
		
                        int rows = size.read();
		wami_debayer(rows, rows);

		
                        process_done.write(true); //1
                        do{wait();}while(!output_start.read());  //2
                        process_done.write(false); //3
                        do{wait();}while(output_start.read());  //4
                        done = true;
	}
}

void debayer::store_output()
{

	
            output_start.write(false);
            debayer_done.write(false);
            bufdout.reset_put();

            wr_request.write(0);
            wr_index.write(0);
            wr_length.write(0);

	
	do{wait();} while(!init_done.read());

STORE_OUTPUT_WHILE:
            bool done = false;
	while(true) {

		
                        if(done){ //TODO change
                            debayer_done.write(true);
                            do{wait();}while(true);
                        }
		
			do{wait();} while(!process_done.read());
                        output_start.write(true); //2
			do{wait();} while(process_done.read());
                        output_start.write(false);


                        int dim = size.read();


	
                        wr_request.write(true);
                   
                        wr_index.write(0); //start index
                        wr_length.write((dim-4)*(dim-4)); //size of debayer image

		
			do{wait();} while(!wr_grant.read());
                        wr_request.write(false);
			do{wait();} while(wr_grant.read());

		

                        for(int i = 0; i < (dim- 2*PAD);i++){
                        	for(int j = 0; j < (dim- 2*PAD);j++){
                            		bufdout.put(debayer_img[i][j]);
					wait();
				}
                        }
	done = true;
	}
}


#ifdef __CTOS__
SC_MODULE_EXPORT(debayer)
#endif

