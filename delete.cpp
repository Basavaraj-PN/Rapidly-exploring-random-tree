#include <iostream>
#include <random>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes



int main(){
    cv::Mat img = cv::imread("/home/ravishankar/RRT/binMap.png", 0);

    std::cout<<(uint)img.at<uchar>(210,346)<<std::endl;
}