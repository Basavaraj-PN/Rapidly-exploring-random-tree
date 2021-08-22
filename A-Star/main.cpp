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
    float f = 100000;
    float g = 100000;
    int x, y, parent_, parent_ind;
    Node(){};
    Node(int x_, int y_) : x(x_), y(y_) {};
    Node(int x_, int y_, Node* parent_) : x(x_), y(y_), parent(parent_) {};
};

uint width, height;
cv::Mat image;
Node start(0, 0, NULL);
Node goal(600,500, NULL); //TODO : update parent of goal node

template <typename  T>
void LogNode(T t){
    std::cout<< "[g,f,x,y: " << t.g << "," << t.g << "," << t.x << "," << t.y << "]" << std::endl;
}

float Heuristic(Node n){
    return sqrt(pow(n.x - goal.x,2) + pow(n.y - goal.y,2));
}

void LoadImage(){
    const std::string file = "/Users/basavaraj/Desktop/WORKSPACE/binMap.png";
    image = cv::imread(file,0);
    auto imageDisplay = image.clone();
    auto dis = image.clone();
    //    image = cv::Mat::zeros(10,10,CV_8UC1);
    //    image.at<uchar>(4,5) = 255;
}

std::vector<Node> list;
int main() {
    start.g = 0;
    start.parent_ind = 0;
    start.f = start.g + Heuristic(start);
    list.push_back(start);
    LogNode(start);

    return 0;
}
