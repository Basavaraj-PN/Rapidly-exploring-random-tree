#include<iostream>
#include <random>
#include<vector>
#include<cmath>


#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> // drawing shapes

struct Node {
    int x, y;
    int parent;
    int index;

    Node(){};
    Node(uint x_, uint y_): x(x_), y(y_){};
    Node(uint x_, uint y_, int parent_) : x(x_), y(y_), parent(parent_){};

};

uint width, height;
std::vector< Node> Graph;


Node RandomPosition(){
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distrH(0, height-1);
    std::uniform_int_distribution<int> distrW(0, width-1);
    Node RandPose;
    RandPose.y = distrH(gen);
    RandPose.x = distrW(gen);
     return RandPose;
}

bool isInObstacle(const Node Xnew, const cv::Mat &image){
    return (uint)image.at<uchar>(Xnew.y,Xnew.x);
}


float CalDistance(Node n1, Node n2){
    float distance = sqrt(pow(n1.x -n2.x,2) + pow(n1.y -n2.y ,2));
    return distance;
}
Node Nearest(Node node){
    float min_dist = 100000;
    Node near;
    for(auto n: Graph){
        if(CalDistance(node, n) < min_dist){
            min_dist = CalDistance(node, n);
            near = n;

        }
    }
    return near;
}

bool CheckLink(Node Xnew, Node Nearest, cv::Mat image){
    for(float i = 0.0 ; i <=1; i = i+0.01){
        float x =  Xnew.x + i*(Nearest.x - Xnew.x);
        float y =  Xnew.y + i*(Nearest.y - Xnew.y);
        if (isInObstacle(Node(x,y), image)){
            return true;
        }
    }
    return false;
}

Node CreateChildNode(Node near, Node Xnew){
    Node child;
    float d = 20;
    float distance = CalDistance(near, Xnew);
    float ratio = d/distance;
    child.x = near.x + ratio * (Xnew.x - near.x);
    child.y = near.y + ratio * (Xnew.y - near.y);
    child.index = Graph.size() ;
    child.parent = near.index;
    return child;
}

int main()
{

    cv::Mat image = cv::imread("/home/ravishankar/RRT/binMap.png",0);
    auto imageDisplay = image.clone();
    if (!image.data){
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    width = image.size().width;
    height = image.size().height;
    std::cout << "Width: " << width << " Height: " << height << std::endl;

    int counter  = 0;
    int lim = 10000 ;
    float thresh_distance = 40;
    Node last_node;
    Node start(50, 50, -1);
    Node end(600,500, -1);
    start.index = 0;

    cv::circle(imageDisplay, cv::Point(start.x, start.y), 5, 255, -1);
    cv::circle(imageDisplay, cv::Point(end.x, end.y), 5, 255, -1);

    std::cout<<"Start Obstacle : "<<isInObstacle(start, image)<<std::endl;
    std::cout<<"End Obstacle : "<<isInObstacle(end, image)<<std::endl;

    Graph.push_back(start);

    while(counter < lim){
        Node Xnew = RandomPosition();
        if (isInObstacle(Xnew, image)){
                continue;   
        }
        Node xnear = Nearest(Xnew);
        if(!CheckLink(Xnew, xnear, image)){
            Node child = CreateChildNode(xnear, Xnew);
            cv::circle(imageDisplay, cv::Point(child.x, child.y), 3, 155, -1);
            cv::line(imageDisplay, cv::Point(child.x, child.y), cv::Point(xnear.x, xnear.y), 155, 1);
            Graph.push_back(child);
            if (CalDistance(child, end) <= thresh_distance){
                std::cout<< "Destination reached " <<std::endl;
//                last_node = child;
                end.parent = child.index;
                break;
            }
        }
        cv::imshow("image",imageDisplay);
        cv::waitKey(30);
    }
    Node temp_node = end;
    while (temp_node.parent != -1){
        cv::circle(imageDisplay, cv::Point(temp_node.x, temp_node.y), 5, 255, -1);
        temp_node = Graph[temp_node.parent];

    }

    cv::namedWindow("window");
    cv::imshow("window", image);
    cv::imshow("window", imageDisplay);
    cv::imwrite("result.jpg", image);
    cv::waitKey(0);
    return 0;
}
