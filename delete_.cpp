#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

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

int main(){
    std::vector<Node> list;

    Node n1(0,0), n2(0,1), n3(10,10), n4(1,1);
    list.push_back(n1);
    list.push_back(n2);
    list.push_back(n3);
    list.push_back(n4);
    Node n(4, 4);
    
    if(!CheckInList(n, list)){
        std::cout << "Not Found: " << std::endl;
        list.push_back(n);
    }
    for(auto l: list){
        std::cout <<"LIST: "<<l.x<< "," << l.y << std::endl;
    }

}