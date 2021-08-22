#include<iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <random>
#include<vector>
#include<cmath>
#include<queue>
#include<map>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes
#include <opencv2/core/eigen.hpp>
class Node{
public:
    Node* parent;
    float f, g;
    int x, y;
    Node(){};
    Node(float f_, float g_) : f(f_), g(g_){};
    Node(Node* parent_, float f_, float g_) : parent(parent_), f(f_), g(g_) {};
};
uint width, height;
cv::Mat image;
Node start(NULL, 0, 0);
int main() {
    const std::string file = "/Users/basavaraj/Desktop/WORKSPACE/binMap.png";
    image = cv::imread(file,0);
    auto imageDisplay = image.clone();
    auto dis = image.clone();
//    image = cv::Mat::zeros(10,10,CV_8UC1);
//    image.at<uchar>(4,5) = 255;
    return 0;
}
