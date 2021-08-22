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
    int x, y, parent_, index;
    Node(){};
    Node(int x_, int y_) : x(x_), y(y_) {};
    Node(int x_, int y_, Node* parent_) : x(x_), y(y_), parent(parent_) {};
};

uint width, height;
cv::Mat image;
Node start(0, 0, NULL);
Node goal(100,100, NULL); //TODO : update parent of goal node
std::vector<Node> tree;

template <typename  T>
void LogNode(T t){
    std::cout<< "[g,f,x,y,parent: " << t.g << "," << t.g << "," << t.x << "," << t.y << "," <<t.parent_ <<"]" << std::endl;
}

float Heuristic(Node n){
    return sqrt(pow(n.x - goal.x,2) + pow(n.y - goal.y,2));
}

bool boundryCheck(const Node t){
    bool check = (!(uint)image.at<uchar>(t.y, t.x)) && t.x >= 0 && t.x < width && t.y >= 0 && t.y < height;
    return check;
}
void GetChildNodes(Node t, std::vector< Node > &children){
    children.clear();
    Node n1, n2, n3, n4, n5, n6, n7, n8;
    n1.x = t.x-1;
    n1.y = t.y;
    if(boundryCheck(n1)){
        children.push_back(n1);
    }

    n2.x = t.x+1;
    n2.y = t.y;
    if(boundryCheck(n2)){
        children.push_back(n2);
    }

    n3.x = t.x;
    n3.y = t.y-1;
    if(boundryCheck(n3)){
        children.push_back(n3);
    }

    n4.x = t.x;
    n4.y = t.y+1;
    if(boundryCheck(n4)){
        children.push_back(n4);
    }

    n5.x = t.x - 1;
    n5.y = t.y - 1;
    if(boundryCheck(n5)){
        children.push_back(n5);
    }

    n6.x = t.x - 1;
    n6.y = t.y + 1;
    if(boundryCheck(n6)){
        children.push_back(n6);
    }

    n7.x = t.x + 1;
    n7.y = t.y - 1;
    if(boundryCheck(n7)){
        children.push_back(n7);
    }

    n8.x = t.x + 1;
    n8.y = t.y + 1;
    if(boundryCheck(n8)){
        children.push_back(n8);
    }
}


Node GetLeastNode(std::vector<Node> &list){
    float min = 10000000.0f;
    Node FNode;
    int index;
    for(int i=0; i<list.size(); i++){
        if(list[i].f < min){
            FNode = list[i];
            index = i;
            min = list[i].f;
        }
    }
//    list[FNode.index].f = 100000000000.0f;
    list.erase(list.begin() + index);
    return FNode;
}
float Distance(Node n1, Node n2){
    return sqrt(pow(n1.x - n2.x,2) + pow(n1.y - n2.y,2));
}
bool CheckInList(Node n1, std::vector<Node> &list){
    bool result = false;
    for(auto l: list){
        if(Distance(n1,l) == 0){
            result = true;
        }
    }
    return result;
}
void genPath(cv::Mat &img){
    Node temp_node = goal;
    while (Distance(temp_node,start) < 2 ){
        cv::circle(img, cv::Point(temp_node.x, temp_node.y), 2, 255, -1);
        temp_node = tree[temp_node.parent_];

    }
    cv::imshow("image", img);
    cv::waitKey(0);
}

std::vector<Node> list;
int main() {
//    LoadImage();
//    image = cv::imread("/Users/basavaraj/Desktop/WORKSPACE/binMap.png",0);
//    auto imageDisplay = image.clone();
//    if (!image.data){
//        std::cout << "Could not open or find the image" << std::endl;
//        return -1;
//    }
    image = cv::Mat::zeros(100,100, CV_8UC1);
    image.at<uchar>(50, 50) = 255;

    auto imageDis =  image.clone();
    width = image.size().width;
    height = image.size().height;
    std::cout << "Width: " << width << " Height: " << height << std::endl;
    start.g = 0;
    start.index = 0;
    start.f = start.g + Heuristic(start);
    list.push_back(start);
    while(!list.empty()){
        Node current_node =  GetLeastNode(list);
        if (Heuristic(current_node) <= 10) {                     /* check the distance between currnet and goal node */
            std::cout<<" Done! "<< std::endl;
            break;
        }
        std::vector< Node> children_nodes;
        GetChildNodes(current_node, children_nodes);
        imageDis.at<uchar>(current_node.y, current_node.x) = 155;
//        cv::imshow("image", imageDis);
//        cv::waitKey(1);
        for (auto n : children_nodes){
            if(n.g > current_node.g + Distance(n, current_node)){
                n.g = current_node.g + Distance(n, current_node);
                n.f = n.g + Heuristic(n);
                n.parent_ = current_node.index;
                n.index = tree.size();
                if(!CheckInList(n, list)){
                    list.push_back(n);
                    tree.push_back(n);
                }
            }
        }
    }
    genPath(imageDis);
    return 0;
}
