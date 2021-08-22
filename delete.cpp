#include <iostream>
#include <random>
#include <vector>
#include "kdtree.h"
#include <chrono>
class Timer
{
public:
    Timer()
    {

        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        Stop();
    }
    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        auto duration = end - start;
        double ms = duration * 0.001;
        std::cout << duration << " micro second or " << ms << " mili second" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

float calDistance(KDT::MyPoint pt1, KDT::MyPoint pt2)
{
    return sqrt(pow(pt1[0] - pt2[0], 2) + pow(pt1[1] - pt2[1], 2));
}

int findNearPoint(std::vector<KDT::MyPoint> &pts, KDT::MyPoint pt)
{
    float minDist = 10000;
    int ind;
    for (int i = 0; i < pts.size(); i++)
    {
        if (calDistance(pts[i], pt) < minDist)
        {
            minDist = calDistance(pts[i], pt);
            ind = i;
        }
    }
    return ind;
}

int main()
{
    std::vector<KDT::MyPoint> pts;

    for (int i = 0; i < 2000; i++)
    {
        int x = rand() % 100;
        int y = rand() % 100;
        pts.push_back(KDT::MyPoint(x, y));
    }
    KDT::MyPoint pt(40, 40);
    KDT::KDTree<KDT::MyPoint> kdt;
    kdt.build(pts);

    {
        Timer time;
        int ind = kdt.nnSearch(pt);
    }
    {
        Timer time;
        pts.push_back(KDT::MyPoint(100, 100));
        int ind = kdt.nnSearch(pt);
        kdt.build(pts);
    }

    {
        Timer time;
        int ind2 = findNearPoint(pts, pt);
    }

    // std::cout<<ind <<"," << ind2 <<std::endl;
}