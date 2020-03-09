#include <stdio.h>
#include "core.h"
#include <hls_opencv.h>
#include "hls_video.h"
#define INPUT_IMAGE "test(3).jpg"
//#define INPUT_IMAGE "window.jpg"

#define OUTPUT_IMAGE "outputimage.jpg"

int main()
{
	cv::Mat src = cv::imread(INPUT_IMAGE);
	cv::Mat dst = src;
    stream_t video_in,video_out;
    cvMat2AXIvideo(src, video_in);
    oct_window(video_in,video_out);
    AXIvideo2cvMat(video_out, dst);
	cv::imwrite(OUTPUT_IMAGE, dst);
	return 0;
}
