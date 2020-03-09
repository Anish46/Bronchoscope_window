#include "core.h"

void window(stream_t &video_in,stream_t &video_out,
		ap_uint<11>row,ap_uint<11>col,unsigned char masking_part_length)
{
#pragma HLS INTERFACE axis register port=video_out
#pragma HLS INTERFACE axis register port=video_in

#pragma HLS INTERFACE s_axilite port=return bundle=CTL
#pragma HLS INTERFACE s_axilite port=dist1 bundle=CTL clock=axi_clk
#pragma HLS INTERFACE s_axilite port=col bundle=CTL
#pragma HLS INTERFACE s_axilite port=row bundle=CTL


interface_t pixelOut;
ap_uint<11> iRows=0,iCols=0;



                                                                                               //LOGIC PART

for (iRows=0; iRows < row; iRows++)
{
#pragma HLS LOOP_TRIPCOUNT min=400 max=1080
for (iCols=0; iCols < col; iCols++)
{
#pragma HLS LOOP_TRIPCOUNT min=400 max=1920
	#pragma HLS PIPELINE

	interface_t currentPixel = video_in.read();
 
	if((iRows<masking_part_length) &&                                                                   //considering the masking of top two parts
	   (iCols<masking_part_length-iRows || iCols>=col-masking_part_length+iRows))
	{
		pixelOut.data =0;
	}
	else if((iRows>row-masking_part_length) &&                                                          //considering the masking of bottom two parts
			(iCols<=iRows-(row-masking_part_length) || iCols>=col-iRows+(row-masking_part_length)))
	{
		pixelOut.data =0;
	}
	else                                              				     //passthrough the rest of the pixels
	{
		pixelOut.data =currentPixel.data;
	}

	pixelOut.keep = currentPixel.keep;
	pixelOut.strb = currentPixel.strb;
	pixelOut.user = currentPixel.user;
	pixelOut.last = currentPixel.last;
	pixelOut.id   = currentPixel.id;
	pixelOut.dest = currentPixel.dest;

	video_out.write(pixelOut);

	}
 }



}
