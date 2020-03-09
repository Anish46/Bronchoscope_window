#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <ap_int.h>

typedef ap_axiu<24,1,1,1> interface_t;
typedef hls::stream<interface_t> stream_t;


void oct_window(stream_t &video_in,stream_t &video_out);
