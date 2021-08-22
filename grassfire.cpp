//
// Created by BASAVARAJ P N on 20/08/21.
//
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

uint width, height;
std::queue< std::pair<int, int> > list;
std::pair<int, int> goal(0,0);
cv::Mat image;
bool boundryCheck(const std::pair<int, int> t){
    bool check = (!(uint)image.at<uchar>(t.second, t.first)) && t.first >= 0 && t.first < width && t.second >= 0 && t.second < height;
    return check;
}

void GetChildNodes(std::pair<int, int> &t, std::vector< std::pair<int, int> > &children){
    children.clear();
    std::pair<int, int> n1, n2, n3, n4, n5, n6, n7, n8;
    n1.first = t.first-1;
    n1.second = t.second;
    if(boundryCheck(n1)){
        children.push_back(n1);
    }

    n2.first = t.first+1;
    n2.second = t.second;
    if(boundryCheck(n2))
        children.push_back(n2);

    n3.first = t.first;
    n3.second = t.second-1;
    if(boundryCheck(n3))
        children.push_back(n3);

    n4.first = t.first;
    n4.second = t.second+1;
    if(boundryCheck(n4))
        children.push_back(n4);

    n5.first = t.first - 1;
    n5.second = t.second - 1;
    if(boundryCheck(n5))
        children.push_back(n5);

    n6.first = t.first - 1;
    n6.second = t.second + 1;
    if(boundryCheck(n6))
        children.push_back(n6);

    n7.first = t.first + 1;
    n7.second = t.second - 1;
    if(boundryCheck(n7))
        children.push_back(n7);

    n8.first = t.first + 1;
    n8.second = t.second + 1;
    if(boundryCheck(n8))
        children.push_back(n8);
}

void printChildren(std::vector<std::pair<int,int> >& children){
    for(std::pair<int,int> child : children){
        std::cout<<child.first<<','<<child.second<<std::endl;
    }
}

int maxMatrix(Eigen::MatrixXd& matrix){
    int max = -1000;
    for(int i = 0;i < width;i++){
        for(int j = 0;j < height;j++){
            if(matrix(j,i) > max && matrix(j,i) != 10000)
                max = matrix(j,i);
        }
    }

    return max;
}

void displayMatrix(Eigen::MatrixXd& matrix, cv::Mat& img){
    int maxm = maxMatrix(matrix);
    for(int i = 0;i < height;i++){
        for(int j = 0;j < width;j++){
            img.at<uchar>(i,j) = 255*matrix(i,j)/maxm;
        }
    }
    cv::imshow("image",img);
    cv::waitKey(0);
}

std::pair<int, int> findMinChild(Eigen::MatrixXd& matrix, std::vector<std::pair<int, int>> children){
    int minv = 1000000;
    std::pair<int, int> minChild;
    for(std::pair<int, int> pt : children){
        if(matrix(pt.second, pt.first) < minv){
            minv = matrix(pt.second, pt.first);
            minChild = pt;
        }
    }

    return minChild;
}

void genPath(Eigen::MatrixXd& matrix, std::pair<int, int> start, std::vector<std::pair<int,int>>& path, cv::Mat& img){
    std::pair<int, int> curr = start;
    std::vector<std::pair<int,int>> children;

    while(matrix(curr.second, curr.first) != 0){
        img.at<uchar>(curr.second, curr.first) = 155;
        path.push_back(curr);
        GetChildNodes(curr, children);;
        curr = findMinChild(matrix, children);
    }

    cv::imshow("image", img);
    cv::waitKey(0);
}

int main(){
    const std::string file = "/Users/basavaraj/Desktop/WORKSPACE/binMap.png";
    image = cv::imread(file,0);
    auto imageDisplay = image.clone();
    auto dis = image.clone();
//    image = cv::Mat::zeros(10,10,CV_8UC1);
//    image.at<uchar>(4,5) = 255;

    if (!image.data){
        std::cout << "Could not open or find the image: " << file << std::endl;
        return -1;
    }
    width = image.size().width;
    height = image.size().height;
    std::cout << "Width: " << width << " Height: " << height<< "\n------------------------------------" << std::endl;
    list.push(goal);
    Eigen::MatrixXd matrix(height,width);
    matrix.setConstant(10000);
    matrix(goal.second, goal.first) = 0;
    while(!list.empty()){
        std::vector< std::pair<int, int>> children_node;
        auto current_node = list.front();
        list.pop();
        GetChildNodes(current_node, children_node);
        for(auto child: children_node){
            if(matrix(current_node.second, current_node.first) + 1 < matrix(child.second, child.first)){
                matrix(child.second, child.first) = matrix(current_node.second, current_node.first) + 1;
                list.push(child);
            }
        }

    }
//    std::cout<<matrix<<std::endl;

//    Eigen::MatrixXd matrix2 = matrix*255/1000;
//
//    cv::Mat test_image;
//    cv::eigen2cv(matrix2, test_image);
//    cv::imshow("uchar image", test_image);
//    cv::waitKey(0);
//    displayMatrix(matrix, imageDisplay);
    std::vector<std::pair<int,int>> path;
    std::pair<int,int> start = std::make_pair(750,550);
    genPath(matrix, start, path, imageDisplay);
    return 0;
}
